
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
        
        I guss I found out... I mean rotation is just x' = x + r*cos(x) and y' = y + r*sin(x) right? RIGHT? I mean I can do that...but real question is:
        DO I NEED GRAVITIY simulation to drop the needles? or just nah?...Damn...

        And yeah this's gonna use raylib.h for visualization (so compile with -lraylib -lm  and have it installed in your system) but as always Imma leave this as a template
        since I Got shit to do beforehand and this is gonna be a quickie...


        Man I really can't start to work on something without defining the problem (and investigating) first in a huge comment...



*/

/* =================== INCLUDES ================ */

/* Neat headers */
#include <limits.h>

/*  Headers that requires flags */
#include <math.h>    //To math.
#include <raylib.h>  //For making my life easier

/* ==================== DEFINES ================== */

#define WIDTH 1200.0
#define HEIGHT 900.0
#define FPS 120 //I am starting to get used this 120 thing my monitor is 180Hz I should be using that but...

#define LINE_AMOUNT 10 //10's good..we have 10 fingers, we use decimal, it's 2*5 both prime
#define FONT_SIZE 35

/* ============== OBJECTS ==================== */


/* ================== GLOBALS ================= */

void piTypeWriter(void);

int main(void)
{

    InitWindow(WIDTH, HEIGHT, "PI THAT TAKES AN ETERNITY");
    if(!IsWindowReady()) { return(-1); } 
    
    SetTargetFPS(FPS);

    Vector2 rectSize = (Vector2){WIDTH/5,(WIDTH/5)*sqrtf(2.0)}; //The ususal ratio of A4 1/sqrt(2) which I CAN'T FORGET FOR SOME FUCKING REASON
    Vector2 rectPos = (Vector2){WIDTH/2-rectSize.x/2, HEIGHT/2-rectSize.y/2};
    
    float distance = rectSize.y/LINE_AMOUNT;
    float needleLength = distance/2.0f;
    
    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_ESCAPE)) { CloseWindow(); }
    
    
        BeginDrawing(); //Lol...I've done everything except math
        ClearBackground(BLACK);
        piTypeWriter();
        DrawRectangle(rectPos.x, rectPos.y, rectSize.x,rectSize.y, BEIGE); //I Guess it's centered now... 
        for (int i = 0; i < LINE_AMOUNT;i++) {
            //This is gonna be hard...actually it's easy but I am making it harder than it should be...so here it'll stay empty like that for a while
        }
        
        
        EndDrawing();
    }


    return(0);
}


void piTypeWriter(void)
{
        DrawText(TextFormat("PI : %.48lf",acos(-1.0)),  32, 10, FONT_SIZE, BEIGE);
}