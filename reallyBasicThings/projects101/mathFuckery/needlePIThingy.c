
/*
        Sup? you 'member my second best idea to approixmate pi in dftThingy.c? Today we're doing that visually for no reason despite having fuck ton of things in futureShit.md
        Yeah that's a muse-driven one...

        So for the people who don't know what's buffon's needle:
        It is a classic geometric probability experiment used to estimate the value of PI by dropping a needle onto a sheet of lined paper but I'll cheese my way a little
        with a 'presumption' which is assuming the P = (2L)/(π·2L) (we're taking D = 2L) so we can simply do P = 1/π or 1/P = π. But this is a **SPECIAL CASE**
        I know and I'm simplifying it 

        Here's a good demonstration, explanation and a SIMULATION by University of Illinois Urbana-Champaign : https://mste.illinois.edu/activity/buffon/
        and for the people saying 'Neuro you ain't citing your resources properly' I do know... I am just showing you a way I am like a pointer just holding address 
        you gotta check the address for the information and how many times you've seen any citation in source code besides mine in a learning repo?Lulz

        And that's how I am gonna remember some math...since right now I don't know how to rotate a fixed size line to 'simulate' random needle drops on the 'paper' 
        probably I'll use cos and sin as always but question is: In which cursed ways?
        
        And yeah this's gonna use raylib.h for visualization (so compile with -lraylib and have it installed in your system) but as always Imma leave this as a template
        since I Got shit to do beforehand and this is gonna be a quickie...
*/

/* =================== INCLUDES ================ */

#include <math.h>
#include <raylib.h>



/* ==================== DEFINES ================== */

#define WIDTH 1200.0
#define HEIGHT 900.0
#define FPS 120 //I am starting to get used this 120 thing my monitor is 180Hz I should be using that but...

/* ============== OBJECTS ==================== */


/* ================== GLOBALS ================= */


int main(void)
{

    InitWindow(WIDTH, HEIGHT, "PI THAT TAKES AN ETERNITY");
    if(!IsWindowReady()) { return(-1); } 
    
    SetTargetFPS(FPS);

    Vector2 rectSize = (Vector2){WIDTH/5,(WIDTH/5)*sqrtf(2.0)}; //The ususal ratio of A4 1/sqrt(2) which I CAN'T FORGET FOR SOME FUCKING REASON
    Vector2 rectPos = (Vector2){WIDTH/2-rectSize.x/2, HEIGHT/2-rectSize.y/2};

    while (!WindowShouldClose()) {
        
        if (IsKeyPressed(KEY_ESCAPE)) { CloseWindow(); }
    
    
        BeginDrawing();
        ClearBackground(BLACK);
        DrawRectangle(rectPos.x, rectPos.y, rectSize.x,rectSize.y, BEIGE); //I Guess it's centered now... 
        //Note to future Neuro assing the abomination to a var (you know which abomination...besides don't do it in loop you'll recalculate it, if you do so)
        EndDrawing();
    }


    return(0);
}