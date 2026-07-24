/*
    Sup? You know the tea if you've seen any other file...welcome to yet another Physics fuckery conjured by my sleep-deprivation 
    What are we building today? UNIVERSE! nah...not there yet but I thought about using random hardware noise for cosmic background radiation tho
    I am not gonna lie... 
    but today's physics fuckery is N-Body simulation from a Wiki article recommended to me here's the link for nerds -> https://en.wikipedia.org/wiki/N-body_simulatio

    This is gonna be the last 'simulation' before I dive back into CLI tools or low-level stuff for a while I guess
    This project requires -lraylib as you compile since I am using raylib duh and I'll curb the profanity in this file...sometimes I get hyped and code
    Sometimes I just code to shut voices, world, that's one of the Category 2 projects...
    Yk when you build something to prove yourself that you are not an imposter 
    

    Side track: The wikipedia page has Dark matter simulation too...so no promises for now...unless?
*/

/* ============ INCLUDES ============ */

#include <raylib.h>


/*=============== DEFINES ============== */

#define WIDTH 1200
#define HEIGHT 900

#ifndef VSYNC 
    #define VSYNC 0 //If you want VSYNC type -DVSYNC=1 as you compile
#endif

#ifndef FPS
    #define FPS 120     //This time I'll make it configurable as you compile: usage: -DFPS=FPS_YOU_WANT (Hard capped at 300fps and 0 for no limit)
#endif

/*================= OBJECTS =============== */

/* ============= GLOBALS ============= */


/* ============= FUNCTION PROTOTYPES ============= */

int setupEnv(void);

/* ============= MAIN ============= */


int main(void)
{

    if (setupEnv()) {
        return(-1); //Change error codes as you go
    }

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_ESCAPE)) { CloseWindow(); }
    
        //Drawing
        BeginDrawing();
        ClearBackground(BLACK);
        DrawFPS(10, 10);    
        EndDrawing();

    }

    return(0);
}



int setupEnv(void)
{
    if (VSYNC) {
        SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT);
    }
    else {
        SetConfigFlags(FLAG_MSAA_4X_HINT);
    }

    InitWindow(WIDTH, HEIGHT, "Fancy Balls Attracting Each Other");
    if (!IsWindowReady()) {
        return(-1);
    }
    //V-sync handles fps in case of being 1 
    if (!VSYNC) {

        if (FPS > 300 || FPS < 0) {
            int fps = 300;
            SetTargetFPS(fps);
        }
        else { SetTargetFPS(FPS); }
    }

    return(0);
}