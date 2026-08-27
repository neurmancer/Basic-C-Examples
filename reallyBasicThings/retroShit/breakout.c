/*
            =============== YAPPING =====================

            'Sup? Yk...the deal I got shit to mark as done in futureShit.md... so here we are starting to code it....
            
            First, I changed my rig setup (DWM to Hyprland to try) and raylib is currently bitching about it 
            Second, This is a template for now I'll try to finish this in a few days if not in a few hours

            So...the technical part: 

            What are we doing? Breakout clone, but question is 'how' since I have no clue how to do...

            Shit to do: 

            1- Well...code everything
            2- Paddle movment
            3- Brick offsets and drawing shit
            4- Collision detection (Hardest part, it seems)
            5- Ball movement and shit


            This is a template for now 
*/


/* ================== INCLUDES ===================== */

#include <stdio.h>
//External Headers 
#include <raylib.h>

/* ===================== DEFINES ====================== */


//Window shit

#define WIDTH 1200.0f
#define HEIGHT 900.0f

#define TITLE "Breakout Duh..."

#ifndef FPS 
    #define FPS 120
#endif 

#ifndef VSYNC
    #define VSYNC 0
#endif 

//Game thingies

#define BRICK_ROWS 4
#define BRICK_COLUMNS 14


static const float BRICK_LENGTH = WIDTH/16;
static const float BRICK_HEIGHT = HEIGHT/32;
//Why static? 'cuz scope thingy is a bitch...(not like I use multiple files but what if I Do?)

/* =================== OBJECTS ========================= */

typedef struct{

    Vector2 pos;
    Vector2 size;

    Color color;
    int powerUp;
}Brick;

typedef struct{

    Vector2 pos;
    float radius;

    Color color;
}Ball;

typedef struct{

    Vector2 pos;
    Vector2 vel;
    Vector2 accel;

    Vector2 size;
    Color color;

}Paddle;

typedef struct{

    //I ain't gonna optimize padding for a fucking breakout clone 
    Paddle paddle;
    Ball ball;

    Brick bricks[BRICK_ROWS][BRICK_COLUMNS];

}Objects;

typedef struct{

    //I'll try to make this configurable 'cuz why not but not now...
    

}Config;

/* ================ (Hopefully Not) GLOBALS ================ */



/* ================= FUNCTION PROTOTYPES ==================== */


int setupEnv(void);


/* ============ MAIN ============= */

int main(void)
{

    printf("C'mon I have to start with a printf right\n");
    if(setupEnv()) { printf("We fucked\n"); return(-53); }

    Brick bricks[BRICK_ROWS][BRICK_COLUMNS] = { 0 };

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_ESCAPE)) { break;}

        BeginDrawing();
        ClearBackground(BLACK);
        EndDrawing();
    }
    


    CloseWindow();
    return(0);
}



/* ============ FUNCTION BODIES ================ */

int setupEnv(void)
{
 
    if (VSYNC) {
        SetConfigFlags(FLAG_VSYNC_HINT);    
    }

    InitWindow(WIDTH, HEIGHT, TITLE);

    if ((FPS < 0 || FPS > 300) && !VSYNC) { SetTargetFPS(120); }
    else { SetTargetFPS(FPS); }

    if (!IsWindowReady()) { return(-1); }

    return(0);
}