/*
    'Sup? This file where I declare that this is the season finale of this repo...For a long time and end of journey
    for me too... Next season will include the shells, bootloaders and vim clones I guess...(I hope it will) also
    I might finish ramanujan fuckery before dipping tho..

    Anyways what's today's CLI math fuckery?...well you know the ASCII donut right? it is the fuckery of today
    I remembered it's existence while fucking with raylib 3D cams and remembered this video: https://www.youtube.com/watch?v=sW9npZVpiMI&t=1s

    then found the original (I guess) donut.c creator's explanations... : https://www.a1k0n.net/2011/07/20/donut-math.html
    There are a few iterations of the donut.c since 2006 until 2021...They explain the math quite well so I'll be just following it 
    while impleneting a few different things too if I can without fucking the original concept...


    first idae is ditching the lib math since the original code (well an iteration of the original one does that so...why wouldn't I?)

    I already implemented the cos and sin approximations using taylor series (cos_and_sinThingy.c) so I'll just copy-paste it here...

    I won't be explaining the math the author of the blog and creator of the project is way better than me go check the blog posts

*/

#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <signal.h>
#include <time.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>


#ifndef DBL_MAX
    #define DBL_MAX __DBL_MAX__  
#endif

//Math defines
#define PI (3.14159265358979323846)
#define TWO_PI (2.0 * PI)
#define HALF_PI (0.5 * PI)

//Chill defines
#define DEFAULT_WIDTH 80
#define DEFAULT_HEIGHT 24

//Visual defines
#define COLOR_STEP 0.02  //Radians per frame; increase for faster color cycling.
#define RESET_COLOR "\033[0m"
#define HOME "\033[H"
#define WIPE "\033[J"
#define HIDE_CURSOR "\033[?25l"
#define SHOW_CURSOR "\033[?25h"



#define R1 1.0f     //Radiis? Radiuses? wtf is the plural of radius but anyways those r's are radiusS 
#define R2 2.0f
#define K2 5.0f     //This is for the distance of the donut from the observer

static double reduce_angle(double x){
    if (x != x) { return(x); } 
    if (x > DBL_MAX || x < -DBL_MAX) { return(x - x); } 
    if (x >= -PI && x <= PI) { return(x); }

    double magnitude = x < 0.0 ? -x : x;
    double period = TWO_PI;

    while (period <= magnitude / 2.0) { period *= 2.0; }
    
    while (period >= TWO_PI) {
        if (magnitude >= period) { magnitude -= period; }
        period *= 0.5;
    }

    if (magnitude > PI) { magnitude -= TWO_PI; }
    
    return(x < 0.0 ? -magnitude : magnitude);
}

double taylor_sin(double x){
    if (x == 0.0) { return(x); } //FYM negative zero tho (I'll leave this one)?

    x = reduce_angle(x);

    if (x > HALF_PI) { x = PI - x; }
    else if (x < -HALF_PI) { x = -PI - x; }

    double x_squared = x*x;
    double term = x;
    double sum = term;

    for (int n = 1; n <= 10; n++) {
        term *= -x_squared / ((2.0*n) * (2.0*n + 1.0));
        sum += term;
    }
    
    return(sum);
}

double taylor_cos(double x){
    x = reduce_angle(x);
    double sign = 1.0;
    if (x > HALF_PI) { x = PI - x; sign = -1.0; }
    else if (x < -HALF_PI) { x = -PI - x; sign = -1.0; }

    double x_squared = x*x;
    double term = 1.0;
    double sum = term;

    for (int n = 1; n <= 10; n++) {
        term *= -x_squared / ((2.0*n - 1.0) * (2.0*n));
        sum += term;
    }
    return(sign * sum);
}



const char DOPE_CHARS[] = " .:-=+*#@";  //I literally copied the same symbols from the code...


typedef struct{
    double rotation[2];
    double color_phase;
    double *depth_buf;
    char *buf;
    size_t buffer_size;
    int width, height;

}RenderData;

/* Handlers only set flags: allocation, ioctl and stdio belong in the main loop. */
static volatile sig_atomic_t quit = 0;
static volatile sig_atomic_t resize_requested = 1;

static void handle_signal(int sig);
static int resize_renderer(RenderData *renderer);

void creat_frame(RenderData *renderer);

void draw_shit(const RenderData *renderer);


int main(void)
{
    int ret_value = 0;
    setvbuf(stdout, NULL, _IONBF, 0);
    RenderData renderer = { 0 };
    struct sigaction action = { 0 };
    action.sa_handler = handle_signal;
    sigemptyset(&action.sa_mask);
    action.sa_flags = SA_RESTART;

    if (sigaction(SIGINT, &action, NULL) == -1 ||
        sigaction(SIGWINCH, &action, NULL) == -1) {
        perror("sigaction");
        return(-13);
    }

    renderer.rotation[0] += 0.9L;
    renderer.rotation[1] += 0.9L;  

    printf(HIDE_CURSOR); //Hide the cursor until cleanup.

    while (!quit) {
        if (resize_requested) {
            resize_requested = 0;
            ret_value = resize_renderer(&renderer);
            if (ret_value != 0) { break; }
        }

        creat_frame(&renderer);
        if (quit) { break; }
        if (resize_requested) { continue; }
        draw_shit(&renderer);

        renderer.rotation[0] += 0.1L;
        renderer.rotation[1] += 0.05L;  //Fine-tuned by my ass
        renderer.color_phase += COLOR_STEP;
        if (renderer.color_phase >= TWO_PI) { renderer.color_phase -= TWO_PI; }

        const struct timespec delay = { .tv_sec = 0, .tv_nsec = 12000000 };
        nanosleep(&delay, NULL);
        
    }
    printf(RESET_COLOR HOME WIPE SHOW_CURSOR);
    free(renderer.depth_buf);
    free(renderer.buf);
    return(ret_value);
}

static void handle_signal(int sig)
{
    if (sig == SIGINT) { quit = 1; }
    else if (sig == SIGWINCH) { resize_requested = 1; }
}

static int resize_renderer(RenderData *renderer)
{
    struct winsize window = { 0 };
    int width = renderer->width ? renderer->width : DEFAULT_WIDTH;
    int height = renderer->height ? renderer->height : DEFAULT_HEIGHT;

    //Keep the last usable size (or 80x24 at startup) if no size is available.
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &window) != -1 &&
        window.ws_col > 0 && window.ws_row > 0) {
        width = window.ws_col;
        height = window.ws_row;
    }
    if (width == renderer->width && height == renderer->height) { return(0); }

    if ((size_t)width > SIZE_MAX / (size_t)height / sizeof(double)) {
        fprintf(stderr, "Terminal dimensions are too large\n");
        return(-689);
    }
    size_t buffer_size = (size_t)width * (size_t)height;
    double *depth_buf = malloc(buffer_size * sizeof(*depth_buf));
    char *buf = malloc(buffer_size);
    if (depth_buf == NULL || buf == NULL) {
        fprintf(stderr, "Could not allocate terminal buffers\n");
        free(depth_buf);
        free(buf);
        return(-1);
    }

    free(renderer->depth_buf);
    free(renderer->buf);
    renderer->depth_buf = depth_buf;
    renderer->buf = buf;
    renderer->buffer_size = buffer_size;
    renderer->width = width;
    renderer->height = height;
    printf(HOME WIPE);
    return(0);
}

void creat_frame(RenderData *renderer)
{
    for (size_t i = 0; i < renderer->buffer_size; i++) {
        renderer->buf[i] = ' ';
    }

    memset(renderer->depth_buf, 0, renderer->buffer_size*sizeof(double));

    //Keep the original character aspect ratio while fitting either dimension.
    double scale_x = (double)renderer->width / DEFAULT_WIDTH;
    double scale_y = (double)renderer->height / DEFAULT_HEIGHT;
    double scale = scale_x < scale_y ? scale_x : scale_y;

    double sin_first = taylor_sin(renderer->rotation[0]);
    double cos_first = taylor_cos(renderer->rotation[0]); 
    
    double sin_second = taylor_sin(renderer->rotation[1]);
    double cos_second = taylor_cos(renderer->rotation[1]);

    for (double theta = 0; theta < TWO_PI; theta+=0.07) {
        //The nested loops always fucks with my imagination...
        for (double phi = 0; phi < TWO_PI; phi += 0.01) {
            double sin_phi = taylor_sin(phi);
            double cos_phi = taylor_cos(phi);

            double sin_theta = taylor_sin(theta);
            double cos_theta = taylor_cos(theta);
            
            double circ_x = R2 + R1 * cos_theta;
            double circ_y = R1 * sin_theta;
            
            double x = circ_x * (cos_second * cos_phi + sin_first * sin_second * sin_phi) - circ_y * cos_first * sin_second;
            double y = circ_x * (sin_second * cos_phi - sin_first * cos_second * sin_phi) + circ_y * cos_first * cos_second;

            double z = K2 + cos_first * circ_x * sin_phi + circ_y * sin_first;  //The z-axis is where my brain leaves...

            double flip_z = 1.0L / z;

            int xp = (int)((double)renderer->width/2 + 30 * scale * flip_z * x);
            int yp = (int)((double)renderer->height/2 - 15 * scale * flip_z * y);

            float lux = 0.7f * sin_phi * cos_theta * sin_second - 0.2f * cos_phi * cos_theta * cos_second;
            int lux_idx = (int)((lux + 1.0f) * 4);
            
            if (lux_idx < 0){ lux_idx = 0; }
            if (lux_idx > 8){ lux_idx = 8; }

            if (yp >= 0 && yp < renderer->height && xp >= 0 && xp < renderer->width) {
                size_t position = (size_t)yp * (size_t)renderer->width + (size_t)xp;
                if (flip_z > renderer->depth_buf[position]) {
                    renderer->depth_buf[position] = flip_z;
                    renderer->buf[position] = DOPE_CHARS[lux_idx];
                }
            }
        }   
    }
}

void draw_shit(const RenderData *renderer)
{
    int r = (int)(taylor_sin(renderer->color_phase) * 127 + 128);
    int g = (int)(taylor_sin(renderer->color_phase + 2) * 127 + 128);
    int b = (int)(taylor_sin(renderer->color_phase + 4) * 127 + 128);

    //Set the foreground once for the whole frame.
    printf("\033[38;2;%d;%d;%dm", r, g, b);
    for (int i = 0; i < renderer->height; i++) {
        if (quit || resize_requested) { break; }
        printf("\033[%d;1H", i + 1);
        fwrite(&renderer->buf[(size_t)i * (size_t)renderer->width], 1, (size_t)renderer->width, stdout);
    }
}
