/*

                ================= YAPPING =================== 

        'Sup?...Today's fuckery is Fourier Epicycle visualizer (just finished (half-assed) the breakout clone) and 
        I need to code something stupid to gather my thoughts before diving into harder things...
        This raylib projects started to make me feel like a fraud since it's always same thing with different tones so...
        I may pause GUI things for a while to focus on learning C better...and yeah despite having a DSP fuckery subfolder
        this is gonna be a Geometry fuckery file since it's about the output (I'll be using DFT so no optimization or shit...
        Just code that resembles math with O(n^2))  I wanna code DFT from scartch (despite I have a spare one in DSP fuckery subfolder) so no FFT if you want to use FFT you can use 
        smarterFFT.c from bigNumLib and implement your optimized version of the program. 

        So...Let's get started! 

        Do I know what we're doing? Visually yeah, implementation wise no fucking clue...
        This's gonna be a quickie

        and It's late (11.40PM) and I haven't slept like in 3 days so this file gonna have way more spelling mistakes 
        Fingers taking over brain rn...

        So...here's the Tea. 
        WTF is a fourier epicycle visualizer? 
            IT draws shit on the screen using circles within circles and shit...
            That's all I know for now, There are lots of sources to check so here is the citation part:

            Wikipedia: https://en.wikipedia.org/wiki/Discrete_Fourier_transform
            Algorithm-Archive: https://www.algorithm-archive.org/contents/cooley_tukey/cooley_tukey.html (This one on FFT but you'll learn new shit either way)

            for complex.h
                man complex (or man 7 complex if your system has other complex titles) 

            but if that's a little cryptic (for me it was, to start)
            here is the jump-start: https://www.geeksforgeeks.org/c/complex-h-header-file-in-c-with-examples/
            (Future update: I hated complex.h so I am going with my hand-rolled complexNum type)

            So here is the plan:

                0- Get the DFT working 
                1- Draw Shit on the screen (radius lines, circles and other shits that's required)
                2- Be able to draw the given index thingy (vague because I still dunno how this dark sorcery shit works)
                3- No promises: but custom .jpeg/.png upload suppor to draw the shit from the said .png (Not today bruh...that's a job for tomorrow)
                4- Go question life choices

            Shit I know about what I need: 
                0- Frequency needed (which is the whole fucking point of using DFT)
                1- Amplitude is also needed. So if we vectorify (yeah I know I am concocting words) the re and im like a 2D vector the line would be the amp
                2- Phase (or offset about where the circling begins) also on the to-do list. which is the angle (im/re) or tan(theta)
    
            
            Well...I'm still confused but at least now there is random shit on screen...

*/


/* ====================== INCLUDES =================== */

#include <stddef.h>
#include <stdlib.h>     //Dynamic shit will get involved so...malloc it is 
#include <stdio.h>
#include <string.h>
#include <time.h>
//flagged headers (add -lm -lraylib as you compile)
#include <raylib.h> // To be able to see shit on screen
#include <math.h>   //To math
/* ====================== DEFINES ==================== */

#define WIDTH 1200
#define HEIGHT 900
#define TITLE "Circles, Math and Shit"

#define FPS 120 //No compile-time flags this time

#define MAX_PATH 1000    //Trail stuff
#define TIME_TWEAK 60.0f

/* ================= OBJECTS ================= */

typedef struct{
    double re;
    double im;


}complexNum;

typedef struct{

    complexNum z;   //a+bi
    double amp;
    double freq;
    double phase;
}dftData;

/* =============== FUNCTION THINGIES ============ */

int setupEnv(void);
int dft(complexNum *input, dftData *output , size_t arrLen);
int compareAmp(const void *a, const void *b);   //For stdlib qsort thing
Vector2 drawCycleThingies(Vector2 startPos, dftData *fourier, size_t N, float time);
//Changed the function: Now caller has to give input output and the arrLen themself, in case of invalid input returns -1

//For now it's caller's responsibilty to free the returned array I may change that to:
// An added output parameter to make caller more aware of the allocation process and free'ing responsbility
// One last note: Due to DFT being a 'transformation' output array length will be same as allocated arrLen.


/* ==================== MAIN ====================== */

int main(void)
{
    if (setupEnv()) { return(-53); }

    srand(time(NULL));  //To randomize the values

    int width = GetScreenWidth();
    int height = GetScreenHeight();
    if (!width || !height) {
        width = WIDTH;
        height = HEIGHT;    
    }

    complexNum *input = NULL;
    dftData *output = NULL;
    

    //Fuck...well...now what?
    //C'mon...draw the things please
    //Well...Let's do the thing when we don't know what to do(nope I am not talking about cussing...Add shit and see if it works)
    const size_t N = 100;
    input = (complexNum *)malloc(N*sizeof(complexNum));
    output = (dftData *)malloc(N*sizeof(dftData));
    if (input == NULL || output == NULL) { printf("SBRK SAID NOPE!\n"); return(-1); }

    for (size_t i = 0; i < N; i++) {
        input[i] = (complexNum){rand() % 500, rand() % 500};
    }

    double mean_re = 0.0, mean_im = 0.0;
    for (size_t i = 0; i < N; i++) {
        mean_re += input[i].re;
        mean_im += input[i].im;
    }
    
    mean_re /= N;
    mean_im /= N;

    for (size_t i = 0; i < N; i++) {
        input[i].re -= mean_re;
        input[i].im -= mean_im;
    }
    
    dft(input, output, N);    

    qsort(output, N, sizeof(dftData), compareAmp);

    float time = 0.0f;
    const float TWO_PI = 2.0f * PI; //Yeah I am THIS lazy


    Vector2 path[MAX_PATH];
    int pathLen = 0;

    //Finally I'm able to draw Shit shit on screen...now I gotta be able to draw ANY shit I want on the screen...

    while (!WindowShouldClose()) {
        
        if (IsKeyPressed(KEY_ESCAPE)) { break; }
        
        BeginDrawing();
        ClearBackground(BLACK);
        Vector2 tip = drawCycleThingies((Vector2){(float) width/2.0f, (float) height/2.0f}, output, N, time);
        // Add tip to the path
        if (pathLen < MAX_PATH) {
            path[pathLen++] = tip;
        } else {
            for (int i = 0; i < MAX_PATH-1; i++) path[i] = path[i+1];
            path[MAX_PATH-1] = tip;
        }

        if (pathLen > 1) {
            for (int i = 1; i < pathLen; i++) {
                DrawLineV(path[i-1], path[i], WHITE);
            }
        }
        time += TWO_PI / (float) (N * TIME_TWEAK);
        if (time > TWO_PI) {
            time = 0.0f;
            pathLen = 0;
        }
        EndDrawing();
    }



    //Free shit right here
    CloseWindow();
    return(0);
}



/* ================== FUNCTION BODIES ============== */

int setupEnv(void)
{
    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_WINDOW_UNDECORATED | FLAG_WINDOW_ALWAYS_RUN);  
    InitWindow(WIDTH, HEIGHT, TITLE);

    

    if (!IsWindowReady()) { return(-1); }
    
    ToggleBorderlessWindowed();
    SetTargetFPS(FPS);
    
    return(0);
}


int compareAmp(const void *a, const void *b)
{
    const dftData *da = (const dftData *)a;
    const dftData *db = (const dftData *)b;

    // Descending order (biggest amplitude first)
    if (da->amp < db->amp){ return(1); }
    if (da->amp > db->amp){ return(-1); }
    return(0);
}

/*

        ==========================  YAPPING:RELOADED ===================== 

    So...here is the deal...WTF is DFT formula (besides looking like an ancient scroll)
    I realized that I never explained the formula in my DSP fuckery sub-folder since I hadn't grasped it yet myself but I feel confident to summarize it now...
    So here is the formula:

        X[k] = Σ (from n=0 to N-1) x[n] * exp(-i * 2 * π * k * n / N)

        X[k] is the frequency domain 
        x[n] is the time domain 
        but those terms are for nerds so you only need to remember captial X = output, lowercase x = input. 
        The 'Σ' (capital sigma) symbol is just a fancy way math nerds are using to say a 'for loop' starting from [n to N-1] both included 

    So... first things first the capital X and lowercase x are two different arrays. k and n are index and exp() is basically e^x (euler's number thing 2.71828...goes on)
    so the exp() looks like = e^(-2πkni / N) all numbers on the numerator are multiplied i is sqrt(-1) which stands for imaginary unit
    And we're working on complex numbers which can be represented as z (complex num) = a+bi. a is the sane number part of the complex number often refered as re(z) 
    and bi is the delusional part often refered as im(z) 
    but working on that is unpleasant so we'll convert that to trigonometry 
    which turns into re(z) = cos(2πkn / N) and im(z) = -sin(2πkn / N) for each x[n]
    The trigonometric conversion comes from Taylor Series proof but I won't get into that in here 'cuz this already feels like a math class.
    and if you don't wanna get trigo to be involved you can use cexp() from complex.h but that's not my cup of tea
    
    One last thing: Fourier Transform 'under math conditions' is an integration which has dx (an infinitesimally small change on x) but since we are using 
    computers and this shit is real life and infinity is basically  math nerds' wet dream I mean fuck you mean numbers between 0-1 is as infinite as 0-well...infinity?..we use discrete fourier transform 

    The minus symbol is required for forward Fourier Transform (if you forget you'll get inverse fourier transform) 
    Yeah I could've said 'Minus sign is requires to convert time domain to frequency domain and positive means frequency domain to time domain which is inverse fourier transform' 
    but the shit is - = input->output and + = output -> input  

    So math class is over we can continue with DFT lol...


    Lol now imagine what if I were to use FFT...the explanation would be:

    -   WTF is Fourier Transform
    -   Why FFT is fast AF O(n*log(n))
    -   What is bit-reversal
    -   Why I chose iterate/recurse 
    -   What is Bluestein algorithm and chirp-z (since we need to handle non-radix2 input and native cooley-turkey is incapable of that)
*/

int dft(complexNum *input, dftData *output , size_t arrLen)
{

    #define DFT_COS (cos(2.0*M_PI * (double)i * (double)j / (double)arrLen))
    #define DFT_SIN (sin(2.0*M_PI * (double)i * (double)j / (double)arrLen))

    //To make my shit easier  besides don't touch those or they'll fuck you
    //Those defines are text substitudes so if you don't get what that implies DO NOT TOUCH (fucking gaslit texts)

    //Mathing happens here
    if (input == NULL || output == (void *)0) { return(-1); } //You weren't expecting (void *)0 right? Yeah neither did I...
    if (arrLen == 0) { return(-1); }

    for (size_t i = 0; i < arrLen; i++) {
        complexNum temp = { 0 };      

        for (size_t j = 0; j < arrLen; j++) {
            //This shit is what makes DFT O(n^2)
            temp.re += input[j].re * DFT_COS + input[j].im * DFT_SIN;
            temp.im += input[j].im * DFT_COS - input[j].re * DFT_SIN;   
        }
        //Normalizing the output 
        temp.re /= arrLen;
        temp.im /= arrLen;  //Yeah yeah...this 'belongs' to inverse-FT fuck you I need a normalized size for this
        
        output[i].freq = i;
        output[i].amp = sqrt((temp.re*temp.re)+(temp.im*temp.im));  //Pythogaras theorem ykr?
        output[i].phase = atan2(temp.im, temp.re);  //I trust math.h with this one but it's basically atan(m), m = slope
        output[i].z = temp;
    }
    #undef DFT_COS
    #undef DFT_SIN
    return(0);
}


Vector2 drawCycleThingies(Vector2 startPos, dftData *fourier, size_t N, float time)
{
    Vector2 pos = startPos;

    for (size_t i = 0; i < N; i++) {
        Vector2 lastPos = pos;

        float freq = fourier[i].freq;
        float amp = fourier[i].amp;
        float phs = fourier[i].phase;

        pos.x += amp*cosf(freq * time + phs);
        pos.y += amp*sinf(freq * time + phs);
        
        DrawCircleLinesV(lastPos, amp, Fade(WHITE, 0.3f));
        DrawLineV(lastPos, pos, WHITE);
        //All black&white like a 3B1B video (Thx for existing Mr.Sanderson)

    }
    return(pos);
}