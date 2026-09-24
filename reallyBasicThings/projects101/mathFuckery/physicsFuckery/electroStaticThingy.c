/*

                            ================ YAPPING =====================

    'sup? In today's episode of how to make Coulomb roll in his grave we're doing electrostatic particle sim... you remember the n body sim right? this is inspired by that idea too...
    We're simply doing the same thing for 'subatomic particles' the last one was all particles attract all particles this one gonna be 
    opposing forces attract each other for initial draft we'll see how it goes... 


*/


/* ========================= INCLUDES =================== */

#include <stdio.h>
#include <sys/random.h>
#include <raylib.h>

/* ======================== DEFINES ==================== */

#define WIDTH 1200
#define HEIGHT 900
#define TITLE "Fancy very small balls attracting some of them"


#ifndef FPS 
#   define FPS 120
#endif //FPS


/* ========================== OBJECTS ==================== */


/* =========================== FUNCTION PROTS =============== */

int setupEnv(void);
int rng(int *holder,int min, int max);


/* ====================== MAIN ==================== */


int main(void)
{

    int entropy = 0;

    if( rng(&entropy, 0, 100) == -13){ perror("RNGSUS said Nope!"); return(-1); }
    if (setupEnv()) { perror("Raylib...bruh..."); return(-53); }


    while (!WindowShouldClose()) {
        if(IsKeyPressed(KEY_ESCAPE)){ break; }


        BeginDrawing();
        EndDrawing();
    }


    printf("Rand Int: %d\n",entropy);

    CloseWindow();
    return(0);
}


/* =================== FUNCTION BODIES =============0*/

int setupEnv(void)
{
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(WIDTH, HEIGHT, TITLE);
    if (!IsWindowReady()) { return(-1);}
    
    SetTargetFPS(FPS);
    
    return(0);
}

int rng(int *holder, int min, int max)
{
    if (getrandom(holder, sizeof((*holder)), 0) < 0) { return(-13); }
    if (*holder < 0) { *holder = (~(*holder))+1; }

    *holder = (*holder) % (max-min) + min;

    return(0);
}