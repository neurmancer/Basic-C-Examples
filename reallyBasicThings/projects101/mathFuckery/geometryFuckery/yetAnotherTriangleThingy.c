/*
            =========== YAPPING ========= 


    Sup? man...I really stop that but anyways...what's today's fuckery?
    More sierpinski triangle if you haven't seen my old implementation using recursion (which is O(3^n))
    this is another approach to create sierpinksi triangle using Chaos Game (you can check wikipedia: https://en.wikipedia.org/wiki/Sierpiński_triangle )

    But core idea is that:    
        1-Take three points in a plane to form a triangle.
        2-Randomly select any point inside the triangle and consider that your current position.
        3-Randomly select any one of the three vertex points.
        4-Move half the distance from your current position to the selected vertex.
        5-Plot the current position.
        6-Repeat from step 3.

    Do I know how to implement this? Fuck no... will I? Eventually...

    Probably hardest part will be the random point generation within the traingle since I really don't know how to do it...but I'll hopefully at the end of this
    program... I may use barycentric coordinates I don't want to go with a circle around the vertices of the triangle and rejection samping since it's O(fucking eternity)
    Do I know what is barycentric coordinates? Nope? Does wikipedia? Yup...will I read it? Maybe...


    and as always it's fucking 4AM since no sane person has ever tried to implement something like this at a reasonable hour... so this file is a template...for now
    and before I forget this program requires -lraylib as you compile and probably -lm for math too but I haven't even fucking include anything so IDK...

    but bright side? this method works with any triangle so I don't need to coin a term to express 'uni-triangles' like the last time     

*/


/* ======================== INCLUDES ==================== */

//libc headers 
#include <stdio.h>
#include <stdlib.h> //I'll probably use an dynamic array to keep track of the points that I have 

//External libs
#include <raylib.h>

/* ========================= DEFINES ====================== */

//Setup 
#define WIDTH 1200.0f
#define HEIGHT 900.0f

#define TITLE "Thingyangle:Reloaded"    //Yeah that's a matrix reference

#ifndef FPS
    #define FPS 120     //I won't try to get V-sync in this one so...either implement for yourself or set your own FPS to your monitor's refresh rate
#endif



/* ============================= OBJECTS ===================== */



/* ===================== GLOBAL VARS =========================== */

/* ===================== FUNCTION PROTOTYPES ================== */

void drawVertices(Vector2 vertices[3]);
int setupEnv(void);



//MAIN 


int main(void)
{

    //Setup shit
    if (setupEnv()) {printf("Window did something...Ig...\n") ; return(-53); } 

    Vector2 peak = (Vector2){WIDTH/2.0f, (HEIGHT/3.0f)};
    Vector2 vertices[3] = { peak,(Vector2){peak.x - (WIDTH/3.0f), peak.y + (HEIGHT/3.0f)},(Vector2){peak.x + (WIDTH/3.0f), peak.y + (HEIGHT/3.0f)} };


    while (!WindowShouldClose()) {
        
        if (IsKeyPressed(KEY_ESCAPE)) { break; }
        

        //I'll call it a day right now...but at least let me draw a fucking traingle or something...
        BeginDrawing();
        ClearBackground(BLACK);
        drawVertices(vertices);

        EndDrawing();
    }


    CloseWindow();

    return(0);
}

void drawVertices(Vector2 vertices[3])
{
    for (int i = 0; i < 3; i++) {
        DrawCircleV(vertices[i], 3.0f, RED);
    }
}

int setupEnv(void)
{
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(WIDTH, HEIGHT, TITLE);
    if(!IsWindowReady()){ return(-1); }
    
    if (FPS < 0 || FPS > 300) {
        SetTargetFPS(240);
    }
    else {
        SetTargetFPS(FPS);
    }

    return(0);
}