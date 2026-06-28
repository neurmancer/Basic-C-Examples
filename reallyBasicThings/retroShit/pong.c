/*  ======== INCLUDES ============   */

#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>


/*  =========== DEFINES ==========  */

#define WIDTH 1200
#define HEIGHT 900 //Still 4:3 like a CRT monitor...I mean we're building a pong duh...

/*  =========== OBJECTS ============ */

typedef struct{
    float width;
    float height;

    Vector2 position;
    
    float speed; //I may add power ups depending on the flowstate so speed may differ

    int score;  //Shoud I keep score in players? dunno that's my first time making a game lmfao
    
    Color color; //Yeah I wanna be that extra
}player;


typedef struct{

    float radius;
    
    Vector2 position;

    float speed;

    Color color;
}ball;



#define FPS 60 

    /*
        Sup? This is a template for a pong game and my first attempt to build a 'game' if you don't consider dopplerThingy.c
        asa a game(which you shouldn't tho) anyways what the fuck is pong for the Gen Alpha

        Pong is a game that...nah just kidding if you learn C ofc you know pong so here is the template
        
        Draw 2 rectangles for players 
        draw a ball as..yk...ball
        make the rects movable (probably W/S for p1 and UP/DOWN for p2 but I don't know if raylib supports polyinput at meantime)
        And make the ball bounce lol

            Important Shit to Know:
                1- I am using the same separation such as === X === where x is the section name like I've used in all the other raylib projects 
                2- I don't know how bots work in these games so either it'll be a hack or worst pong player ever UnU
                3- And it's 00.48 at night so I won't question how
                4- And fyi despite being against AI usage in coding process I am using Codex just to try(not to write code but pushing commits for me and creating directory)
                but you can be sure that all the code will be written by me (by a carbon-based creature (against common belief I am not a bot)) 
                and yeah I felt need to justify my usage of AI since it has a bad reputation (for me at least) 
    */



int main(void)
{

    InitWindow(WIDTH,HEIGHT,"Pong Duh...?");
    if (!IsWindowReady()) { perror("Window may not be ready but Linux is B;) \n"); return(-13); }
    SetTargetFPS(FPS);

    ball pongBall = { 0 };
    
    pongBall.position = (Vector2){WIDTH/2.0f,HEIGHT/2.0f}; //It requires casting for some reason that I couldn't grasp
    pongBall.radius = 3.0f;
    pongBall.speed = 2.5f;
    pongBall.color = (Color){53,13,0,255};


    ClearBackground(BLACK); //I wonder if that works without BeginDraw() or not yup it does work


    while (!WindowShouldClose()) {
        
        if (IsKeyPressed(KEY_ESCAPE)) { CloseWindow(); }



        BeginDrawing();
        ClearBackground(BLACK);
        DrawCircleV(pongBall.position,pongBall.radius, pongBall.color);
        EndDrawing();
        pongBall.position.x += pongBall.speed;
        pongBall.position.y += pongBall.speed/2;        //Yup it yeets itself now
    }

    return(0);
}