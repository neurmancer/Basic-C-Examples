
/*
        Sup? you 'member my second best idea to approixmate pi in dftThingy.c? Today we're doing that visually for no reason despite having fuck ton of things in futureShit.md
        Yeah that's a muse-driven one...

        So for the people who don't know what's buffon's needle:
        It is a classic geometric probability experiment used to estimate the value of PI by dropping a needle onto a sheet of lined paper but I'll cheese my way a little
        with a 'presumption' 


        And that's how I am gonna remember some math...since right now I don't know how to rotate a fixed size line to 'simulate' random needle drops on the 'paper' 
        probably I'll use cos and sin as always but question is: In which cursed ways?
        
        And yeah this's gonna use raylib.h for visualization (so compile with -lraylib and have it installed in your system) but as always Imma leave this as a template
        since I Got shit to do beforehand and this is gonna be a quickie...
*/

/* =================== INCLUDES ================ */

#include <raylib.h>



/* ==================== DEFINES ================== */

#define WIDTH 1200
#define HEIGHT 900 


/* ============== OBJECTS ==================== */


/* ================== GLOBALS ================= */


int main(void)
{

    InitWindow(WIDTH, HEIGHT, "PI THAT TAKES AN ETERNITY");
    

    while (!WindowShouldClose()) {
        
        if (IsKeyPressed(KEY_ESCAPE)) { CloseWindow(); }
    
    
        BeginDrawing();
        ClearBackground(BLACK);
        EndDrawing();
   
    }


    return(0);
}