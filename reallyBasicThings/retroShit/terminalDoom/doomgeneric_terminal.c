/* ========================== YAPPING ==================== */
/*
    A FUCKING TERMINAL DOOM PORT

    Yeah...the "basic examples" part of the repo name is fighting for its life.

    First lemme clear this up: DoomGeneric is the existing Doom engine.
    Monsters, maps, shooting and the actual rendering live over there in .engine/.
    This file is the terminal glue: take its pixels, spit colored characters,
    translate keyboard bytes and try not to leave your shell cursed afterwards.
    demo.wad is Freedoom's game data, not some Doom clone written in this file.

    From this folder: make fetch (only if .engine is missing), then make
    Run: ./terminal-doom -iwad demo.wad
    Add --ascii for character soup or --preview for a WAD-free gradient thingy.
    Q quits. WASD/arrows move, Space fires, E uses doors, J/L strafe.

    Linux/POSIX stuff ahead. No raylib, no window, no sound...just terminal fuckery.
    The catch: normal terminals don't tell us when you RELEASE a key, so we guess.
    More detailed explanations and limitations are in the root NOTES.md.
*/

#define _POSIX_C_SOURCE 200809L // Ask libc for the POSIX declarations before including its headers.

/*INCLUDES*/
//libc headers
#include <errno.h>  //Syscall failure details.
#include <signal.h> //Ctrl-C and friends...politely requesting our demise.
#include <stdint.h> //Fixed-width framebuffer pixels and clock counters.
#include <stdio.h>
#include <stdlib.h> //Allocation, exit and atexit.
#include <string.h>
#include <time.h> //Monotonic clock and nanosleep (POSIX parts of this header).

//Engine headers (built together through the Makefile)
#include "doomgeneric.h" //Engine framebuffer and the DG_* functions we must provide.
#include "doomkeys.h"    //Doom's key values aren't all ordinary ASCII bytes.

//Platform specific headers (Linux/POSIX)
#include <fcntl.h>     //Descriptor flags and log-file opening.
#include <poll.h>      //Wait until the terminal can swallow more output.
#include <sys/ioctl.h> //How big is this terminal thingy right now?
#include <termios.h>   //Keyboard/terminal settings, aka the part we better restore.
#include <unistd.h>    //read, write, dup, close and terminal checks.

/*DEFINES*/
//Rendering
// Cap output size; making the terminal huge shouldn't mean infinite ANSI spam.
#define MAX_COLS (160)
#define MAX_ROWS (100)

//Input
#define RELEASE_MS (180) // No new repeat for this long? Pretend the key was released.

/* GLOBAL VARS */
// The engine calls us without a user-data pointer, so the backend state lives here.
static struct termios saved_termios;
static int saved_flags = -1;
static int screen_fd = -1;
static int terminal_active;
static int ascii_mode;
static volatile sig_atomic_t stop_signal; // The signal handler only touches this flag.
static uint64_t start_ms;
static uint64_t last_frame_ms;
static uint64_t key_until[256];     // When each simulated key hold expires.
static unsigned char key_down[256]; // What we've already told the engine is held.
static int escape_state;
static uint64_t escape_started;
// Room for both RGB escape sequences + the glyph per cell, with cursor-control slack.
static char frame[MAX_COLS * MAX_ROWS * 48 + 4096];

/*FUNCTION PROTOTYPES*/
//void returns (no arguments first)
static void restoreTerminal(void);
static void checkStop(void);
void DG_Init(void);
void DG_DrawFrame(void);
static void onSignal(int number);
static void writeScreen(const char *data, size_t length);
static void pressKey(unsigned char key);
static void parseByte(unsigned char byte);
void DG_SleepMs(uint32_t ms);
void DG_SetWindowTitle(const char *title);

//Primitive returns
static uint64_t nowMs(void);
uint32_t DG_GetTicksMs(void);
int DG_GetKey(int *pressed, unsigned char *key);
static uint32_t samplePixel(int x, int y, int width, int height);

/*MAIN*/
int main(int argc, char **argv)
{
    int ret_value = 0;
    int log_fd = -1;
    int preview = 0;
    int output_argc = 1;

    //Arguments
    // Eat our own options and compact argv in place. Doom gets the remaining arguments.
    for(int i = 1; i < argc; ++i)
    {
        if(!strcmp(argv[i], "--ascii"))
            ascii_mode = 1;
        else if(!strcmp(argv[i], "--preview"))
            preview = 1;
        else if(!strcmp(argv[i], "--help"))
        {
            puts("Usage: terminal-doom [--ascii] -iwad /path/to/game.wad\n"
                 "       terminal-doom [--ascii] --preview\n"
                 "WASD/arrows: move/turn; J/L: strafe; Space: fire; E: use\n"
                 "R: run; 1-7: weapons; Tab: map; Enter: confirm; Esc: menu; Q: quit\n"
                 "Engine output goes to terminal-doom.log in the current directory.");
            goto cleanUp;
        }
        else
            argv[output_argc++] = argv[i];
    }
    argv[output_argc] = NULL;
    const char *term = getenv("TERM");
    if(!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO) || (term && !strcmp(term, "dumb")))
    {
        fputs("An interactive ANSI terminal is required. Use --help for usage.\n", stderr);
        ret_value = 13;
        goto cleanUp;
    }

    //Terminal setup
    // Snapshot the terminal BEFORE fucking with it; dup preserves a way to draw later.
    if(tcgetattr(STDIN_FILENO, &saved_termios) < 0 || (saved_flags = fcntl(STDIN_FILENO, F_GETFL)) < 0 ||
       (screen_fd = dup(STDOUT_FILENO)) < 0)
    {
        perror("terminal access");
        ret_value = 1;
        goto cleanUp;
    }
    if(atexit(restoreTerminal) != 0)
    {
        ret_value = 1;
        goto cleanUp;
    }
    struct sigaction action = {0};
    action.sa_handler = onSignal;
    sigemptyset(&action.sa_mask);
    if(sigaction(SIGINT, &action, NULL) < 0 || sigaction(SIGTERM, &action, NULL) < 0 ||
       sigaction(SIGHUP, &action, NULL) < 0 || sigaction(SIGPIPE, &action, NULL) < 0)
    {
        ret_value = 1;
        goto cleanUp;
    }

    //Output redirection and buffer handling
    // Engine yapping goes to a log. Our saved screen_fd keeps pointing at the terminal.
    // Otherwise engine printf calls would casually stomp over the monsters.
    log_fd = open("terminal-doom.log", O_WRONLY | O_CREAT | O_TRUNC, 0600);
    if(log_fd < 0)
    {
        perror("terminal-doom.log");
        ret_value = 1;
        goto cleanUp;
    }
    fflush(stdout);
    if(dup2(log_fd, STDOUT_FILENO) < 0 || dup2(log_fd, STDERR_FILENO) < 0)
    {
        ret_value = 1;
        goto cleanUp;
    }
    close(log_fd);
    
    log_fd = -1;
    
    setvbuf(stdout, NULL, _IOLBF, 0);
    
    start_ms = nowMs();

    //Preview allocation and loop
    if(preview)
    {
        // Fake framebuffer for checking colors/input without loading game data.
        // This gradient isn't Doom, obviously. Same display path tho.
        DG_ScreenBuffer = (pixel_t *)calloc(DOOMGENERIC_RESX * DOOMGENERIC_RESY, sizeof(pixel_t));
    
        if(DG_ScreenBuffer == NULL)
        {
            ret_value = 1;
            goto cleanUp;
        }
    
        DG_Init();
    
        for(int y = 0; y < DOOMGENERIC_RESY; ++y)
    
        for(int x = 0; x < DOOMGENERIC_RESX; ++x)
                DG_ScreenBuffer[y * DOOMGENERIC_RESX + x] = ((uint32_t)(x * 255 / DOOMGENERIC_RESX) << 16) |
                                                            ((uint32_t)(y * 255 / DOOMGENERIC_RESY) << 8) |
                                                            96;
        while(1)
        {
            int pressed;
            unsigned char key;
    
            while(DG_GetKey(&pressed, &key))
            {
                printf("key %u %s\n", key, pressed ? "down" : "up");
            }
            DG_DrawFrame();
        }
    }

    //Gameplay
    // Let the actual engine take the wheel. It calls our DG_* hooks as needed.
    doomgeneric_Create(output_argc, argv);
    while(1)
    {
        checkStop();
        doomgeneric_Tick();
    }

cleanUp:
    if(log_fd >= 0)
    {
        close(log_fd);
        log_fd = -1;
    }
    restoreTerminal();
    return(ret_value);
}

/*
    Memory Accountant:
    Preview: one calloc for DG_ScreenBuffer, kept for the whole process lifetime.
    Gameplay: DoomGeneric allocates/owns that buffer and its other engine memory.
    The OS reclaims the preview buffer on exit; no per-frame heap allocations here.
    Descriptors and terminal state have explicit cleanup (including atexit paths).
*/

/*FUNCTION BODIES*/
/* CLOCK AND CLEANUP (the boring shit that keeps everything usable) */
static uint64_t nowMs(void)
{
    // Monotonic time doesn't jump because somebody changed the system clock.
    struct timespec ts;
    if(clock_gettime(CLOCK_MONOTONIC, &ts) != 0){ exit(1); }
    
    return((uint64_t)ts.tv_sec * 1000 + (uint64_t)ts.tv_nsec / 1000000);
}

static void restoreTerminal(void)
{
    // atexit calls this on ordinary exits. SIGKILL doesn't give a shit about atexit.
    if(terminal_active)
    {
        const char reset[] =
            "\033[0m\033[?25h\033[?1049l"; // Colors off, cursor back, leave alternate screen.
        tcsetattr(STDIN_FILENO, TCSANOW, &saved_termios);
        fcntl(STDIN_FILENO, F_SETFL, saved_flags);
        (void)write(screen_fd, reset, sizeof(reset) - 1);
        terminal_active = 0;
    }
    
    if(screen_fd >= 0)
    {
        close(screen_fd);
        screen_fd = -1;
    }
}

static void onSignal(int number)
{
    // No printf/free/terminal surgery inside the handler. Leave that to normal code.
    stop_signal = number;
}

static void checkStop(void)
{
    if(stop_signal){ exit(128 + stop_signal); }
}

static void writeScreen(const char *data, size_t length)
{
    // write() can send only SOME bytes. Advance by what actually went through.
    while(length)
    {
        checkStop();
        ssize_t count = write(screen_fd, data, length);
        if(count < 0 && errno == EINTR){ continue; }
        if(count < 0 && (errno == EAGAIN || errno == EWOULDBLOCK))
        {
            // stdin/stdout can share file flags; nonblocking input can affect output too.
            // Terminal is full, not dead. Wait a bit and check the exit flag again.
            struct pollfd output = {screen_fd, POLLOUT, 0};
            if(poll(&output, 1, 50) < 0 && errno != EINTR) { exit(1); }
            continue;
        }
        if(count <= 0){ exit(1); }
        data += count;
        length -= (size_t)count;
    }
}

/* DOOMGENERIC'S PLATFORM HOOKS */
void DG_Init(void)
{
    // Stop waiting for Enter and stop echoing movement keys over the fucking game.
    // This isn't fully raw mode: ISIG stays enabled so Ctrl-C still works.
    struct termios raw = saved_termios;
    
    raw.c_lflag &= (tcflag_t) ~(ICANON | ECHO | IEXTEN);
    raw.c_iflag &= (tcflag_t) ~(IXON | ICRNL | INLCR | IGNCR);
    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 0;
    raw.c_cc[VSUSP] = _POSIX_VDISABLE; // No Ctrl-Z until proper suspend/resume handling exists.
    
    terminal_active = 1;
    
    if(tcsetattr(STDIN_FILENO, TCSANOW, &raw) < 0 ||
       fcntl(STDIN_FILENO, F_SETFL, saved_flags | O_NONBLOCK) < 0)
    {
        perror("terminal setup");
        exit(1);
    }
    
    const char init[] = "\033[?1049h\033[?25l\033[2J"; // Alternate screen, hide cursor, clear.
    
    writeScreen(init, sizeof(init) - 1);
}

void DG_SleepMs(uint32_t ms)
{
    // nanosleep uses seconds + nanoseconds. On interruption it gives us time remaining.
    struct timespec delay = {ms / 1000, (long)(ms % 1000) * 1000000L};
    while(nanosleep(&delay, &delay) < 0 && errno == EINTR){ checkStop(); }
    checkStop();
}

uint32_t DG_GetTicksMs(void)
{
    checkStop();
    return((uint32_t)(nowMs() - start_ms));
}

void DG_SetWindowTitle(const char *title)
{
    // Required hook, optional behavior. The shell can keep its title, whatever.
    (void)title;
}

/* KEYBOARD BYTE SOUP */
static void pressKey(unsigned char key) { key_until[key] = nowMs() + RELEASE_MS; }

static void parseByte(unsigned char byte)
{
    // Arrow keys arrive as multiple bytes, usually ESC [ A/B/C/D, sometimes ESC O ...
    // State 0 = ordinary input, 1 = got ESC, 2 = inside the rest of the sequence.
    // Keep state across reads 'cuz one read doesn't magically equal one keypress.
    if(escape_state == 1)
    {
        if(byte == '[' || byte == 'O')
        {
            escape_state = 2;
            return;
        }
        pressKey(KEY_ESCAPE);
        escape_state = 0;
    }
    else if(escape_state == 2)
    {
        // 0x40..0x7e marks a final sequence byte. Ignore endings we don't recognize.
        if(byte >= 0x40 && byte <= 0x7e)
        {
            if(byte == 'A'){ pressKey(KEY_UPARROW); }
            if(byte == 'B'){ pressKey(KEY_DOWNARROW); }
            if(byte == 'C'){ pressKey(KEY_RIGHTARROW); }
            if(byte == 'D'){ pressKey(KEY_LEFTARROW); }
            
            escape_state = 0;
        }
        return;
    }
    if(byte == 27)
    {
        escape_state = 1;
        escape_started = nowMs();
        return;
    }
    if(byte >= 'A' && byte <= 'Z') { byte += 'a' - 'A'; }
    switch(byte)
    {
        case 'q':
            exit(0);
        case 'w':
            byte = KEY_UPARROW;
            break;
        case 's':
            byte = KEY_DOWNARROW;
            break;
        case 'a':
            byte = KEY_LEFTARROW;
            break;
        case 'd':
            byte = KEY_RIGHTARROW;
            break;
        case 'j':
            byte = KEY_STRAFE_L;
            break;
        case 'l':
            byte = KEY_STRAFE_R;
            break;
        case 'e':
            byte = KEY_USE;
            break;
        case ' ':
            byte = KEY_FIRE;
            break;
        case 'r':
            byte = KEY_RSHIFT;
            break;
        case '\n':
            byte = KEY_ENTER;
            break;
        default:
            break;
    }
    pressKey(byte);
}

int DG_GetKey(int *pressed, unsigned char *key)
{
    unsigned char bytes[128];
    
    checkStop();
    if(escape_state && nowMs() - escape_started >= 40)
    {
        if(escape_state == 1){ pressKey(KEY_ESCAPE); }
        escape_state = 0;
    }
    for(int batch = 0; batch < 8; ++batch)
    { // Bound each call's reading work.
        ssize_t count = read(STDIN_FILENO, bytes, sizeof(bytes));
        if(count < 0)
        {
            if(errno == EINTR)
                continue;
            if(errno == EAGAIN || errno == EWOULDBLOCK)
                break;
            exit(1);
        }
        if(!count)
            break;
        for(ssize_t i = 0; i < count; ++i)
            parseByte(bytes[i]);
    }
    uint64_t now = nowMs();
    
    for(int i = 0; i < 256; ++i)
    {
        int wanted = key_until[i] > now;
    
        if(wanted != key_down[i])
        {
            key_down[i] = (unsigned char)wanted;
            *pressed = wanted;
            *key = (unsigned char)i;
            return(1);
        }
    }
    return(0);
}

/* PIXELS -> TERMINAL SORCERY */
static uint32_t samplePixel(int x, int y, int width, int height)
{
    // Nearest-neighbor scaling: map an output sample back into the engine's image.
    // A 2D image is still one flat array: row * row_width + column.
    int sx = x * DOOMGENERIC_RESX / width;
    int sy = y * DOOMGENERIC_RESY / height;
    
    return(DG_ScreenBuffer[sy * DOOMGENERIC_RESX + sx]);
}

void DG_DrawFrame(void)
{
    // Roughly 30 display frames/sec. Doom still manages its own simulation clock.
    uint64_t now = nowMs();
    if(last_frame_ms && now - last_frame_ms < 33) { DG_SleepMs((uint32_t)(33 - (now - last_frame_ms))); }
    
    last_frame_ms = nowMs();
    
    struct winsize size;
    
    if(ioctl(screen_fd, TIOCGWINSZ, &size) < 0 || !size.ws_col || !size.ws_row) { return; }
    
    int cols = size.ws_col > MAX_COLS ? MAX_COLS : size.ws_col;
    int rows = size.ws_row > MAX_ROWS ? MAX_ROWS : size.ws_row;
    
    int height = rows - 1; // Save a row for controls so we don't scroll the picture away.
    int width = cols;
    
    if(height < 1 || width < 2) { return; }
    // Cells are assumed twice as tall as wide: 8/3 in cells gives roughly my beloved 4/3 on screen.
    if(width > height * 8 / 3) { width = height * 8 / 3; }
    else { height = width * 3 / 8; }
    
    if(height < 1) { height = 1; }
    
    size_t used = (size_t)snprintf(frame, sizeof(frame), "\033[H");
    
    for(int y = 0; y < rows - 1; ++y)
    {
        used += (size_t)snprintf(frame + used, sizeof(frame) - used, "\033[%d;1H\033[0m", y + 1);
        if(y < height)
        {
            for(int x = 0; x < width; ++x)
            {
                uint32_t top = samplePixel(x, 2 * y, width, height * 2);
                uint32_t bottom = samplePixel(x, 2 * y + 1, width, height * 2);
                if(ascii_mode)
                {
                    // Six chnnels totla, max 6*255 = 1530. Squash brightness into ten glyphs.
                    // Simple averagish mapping not fancy perceptual color science.
                    unsigned value = 0;
                    for(int shift = 0; shift < 24; shift += 8)
                        value += ((top >> shift) & 255) + ((bottom >> shift) & 255);
                    frame[used++] = " .:-=+*#%@"[value * 9 / 1530];
                }
                else
                {
                    // 38;2 sets RGB foreground, 48;2 background. Octal bytes encode UTF-8 U+2580.
                    // Shift + mask peels R/G/B out of the engine's packed pixel value.
                    used += (size_t)snprintf(frame + used, sizeof(frame) - used,
                                             "\033[38;2;%u;%u;%um\033[48;2;%u;%u;%um\342\226\200",
                                             (top >> 16) & 255, (top >> 8) & 255, top & 255,
                                             (bottom >> 16) & 255, (bottom >> 8) & 255, bottom & 255);
                }
            }
        }
        // Reset colors before clearing leftovers, especially after a resize.
        used += (size_t)snprintf(frame + used, sizeof(frame) - used, "\033[0m\033[K");
    }
    const char *status = "WASD/arrows move | J/L strafe | Space fire | E use | Esc menu | Q quit";
    used += (size_t)snprintf(frame + used, sizeof(frame) - used, "\033[%d;1H%.*s\033[K", rows, cols - 1, status);
    writeScreen(frame, used);
}
