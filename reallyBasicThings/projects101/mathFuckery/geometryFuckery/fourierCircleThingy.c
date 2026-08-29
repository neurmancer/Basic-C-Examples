/*

        'Sup?...Today's fuckery is Fourier Epicycle visualizer (just finished (half-assed) the breakout clone) and 
        I need to code something stupid to gather my thoughts before diving into harder things...
        This raylib projects started to make me feel like a fraud since it's always same thing with different tones so...
        I may pause GUI things for a while to focus on learning C better...and yeah despite having a DSP fuckery subfolder
        this is gonna be a Geometry fuckery file since it's about the output (I'll be using DFT so no optimization or shit...
        Just code that resembles math with O(n^2)) 

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
*/


/* ====================== INCLUDES =================== */

#include <stdlib.h>     //Dynamic shit will get involved so...malloc it is 
#include <complex.h>    //Yeah this time I wanna look at what this does 

//flagged headers (add -lm -lraylib as you compile)
#include <raylib.h> // To be able to see shit on screen
#include <math.h>   //To math
/* ====================== DEFINES ==================== */

#define WIDTH 1200
#define HEIGHT 900
#define TITLE "Circles, Math and Shit"

#define FPS 120 //No compile-time flags this time

/* =============== FUNCTION THINGIES ============ */

int setupEnv(void);

float complex *dft(float complex *x, size_t arrLen);
//For now it's caller's responsibilty to free the returned array I may change that to:
// An added output parameter to make caller more aware of the allocation process and free'ing responsbility
// One last note: Due to DFT being a 'transformation' output array length will be same as allocated arrLen.


/* ==================== MAIN ====================== */

int main(void)
{
    if (setupEnv()) { return(-53); }

    int width = GetScreenWidth();
    int height = GetScreenHeight();
    if (!width || !height) {
        width = WIDTH;
        height = HEIGHT;    
    }

    float complex *x = NULL;

    while (!WindowShouldClose()) {
        
        if (IsKeyPressed(KEY_ESCAPE)) { break; }
        
        BeginDrawing();
        ClearBackground(BLACK);
        EndDrawing();
    }



    //Free shit right here
    CloseWindow();
    return(0);
}



/* ================== FUNCTION BODIES ============== */

int setupEnv(void)
{
    
    InitWindow(WIDTH, HEIGHT, TITLE);

    if (!IsWindowReady()) { return(-1); }
    
    ToggleBorderlessWindowed();
    SetTargetFPS(FPS);
    
    return(0);
}

float complex *dft(float complex *x, size_t arrLen)
{

    //Mathing happens here


    return(NULL);
}