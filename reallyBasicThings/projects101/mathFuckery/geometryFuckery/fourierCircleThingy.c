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
                3- No promises: but custom .jpeg/.png upload suppor to draw the shit from the said .png
                4- Go question life choices

            Shit I know about what I need: 
                0- Frequency needed (which is the whole fucking point of using DFT)
                1- Amplitude is also needed. So if we vectorify (yeah I know I am concocting words) the re and im like a 2D vector the line would be the amp
                2- Phase (or offset about where the circling begins) also on the to-do list. which is the angle (im/re) or tan(theta)
    */


/* ====================== INCLUDES =================== */

#include <stdlib.h>     //Dynamic shit will get involved so...malloc it is 

//flagged headers (add -lm -lraylib as you compile)
#include <raylib.h> // To be able to see shit on screen
#include <math.h>   //To math
/* ====================== DEFINES ==================== */

#define WIDTH 1200
#define HEIGHT 900
#define TITLE "Circles, Math and Shit"

#define FPS 120 //No compile-time flags this time

#define DFT_COS (cos(2.0*M_PI * (double)i * (double)j / (double)arrLen))
#define DFT_SIN (sin(2.0*M_PI * (double)i * (double)j / (double)arrLen))
//To make my shit easier  besides don't touch those or they'll haunt yo
//Those defines are text substitudes so if you don't get what that implies DO NOT TOUCH (fucking gaslit texts)

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

//Changed the function: Now caller has to give input output and the arrLen themself, in case of invalid input returns -1

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

    complexNum *input = NULL;
    dftData *output = NULL;
    

    //Well...now what?

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
    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_WINDOW_UNDECORATED | FLAG_WINDOW_ALWAYS_RUN);  
    InitWindow(WIDTH, HEIGHT, TITLE);

    if (!IsWindowReady()) { return(-1); }
    
    ToggleBorderlessWindowed();
    SetTargetFPS(FPS);
    
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
    computers and this shit is real life and infinity is basically  math nerds' wet dream..we use discrete fourier transform 

    The minus symbol is required for forward Fourier Transform (if you forget you'll get inverse fourier transform) 

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

    return(0);
}