/*

        'Sup?...Today's fuckery is Fourier Epicycle visualizer (just finished (half-assed) the breakout clone) and 
        I need to code something stupid to gather my thoughts before diving into harder things...
        This raylib projects started to make me feel like a fraud since it's always same thing with different tones so...
        I may pause GUI things for a while to focus on learning C better...and yeah despite having a DSP fuckery subfolder
        this is gonna be a Geometry fuckery file since it's about the output (I'll be using DFT so no optimization or shit...
        Just code that resambles math with O(n^2)) 

        So...Let's get started! 

        Do I know what we're doing? Visually yeah, implementation wise no fucking clue...
        This's gonna be a quickie
*/


/* ====================== INCLUDES =================== */

#include <stdlib.h>     //Dyanmic shit will get involved so...malloc it is 
#include <complex.h>    //Yeah this time I wanna look what this does 

//flagged headers (add -lm -lraylib as you compile)
#include <raylib.h>
#include <math.h>
/* ====================== DEFINES ==================== */

#define WIDTH 1200
#define HEIGHT 900

#define FPS 120 //No compile-time flags this time

/* =============== FUNCTION THINGIES ============ */

float complex *dft(float complex *x, int arrLen);


/* ==================== MAIN ====================== */

int main(void)
{

    float complex *x = NULL;


    return(0);
}



/* ================== FUNCTION BODIES ============== */


float complex *dft(float complex *x, int arrLen)
{
    



    return(NULL);
}