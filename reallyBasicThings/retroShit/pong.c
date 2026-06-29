/*  ======== INCLUDES ============   */

#include <stdio.h>
#include <raylib.h>


    /*
        Sup? This is a template for a pong game and my first attempt to build a 'game' if you don't consider dopplerThingy.c
        asa a game(which you shouldn't tho) anyways what the fuck is pong for the Gen Alpha

        Pong is a game that...nah just kidding if you learn C, ofc you do know what pong is, so here is the template

        Draw 2 rectangles for players 
        draw a ball as..yk...ball
        make the rects movable (probably W/S for p1 and UP/DOWN for p2 but I don't know if raylib supports polyinput at meantime)(it does take multiple input at the same time)
        And make the ball bounce lol

            Important Shit to Know:
                1- I am using the same separation such as === X === where x is the section name like I've used in all the other raylib projects 
                2- I don't know how bots work in these games so either it'll be a hack or worst pong player ever UnU
                3- And it's 00.48AM at night so I won't question how


        Man...I wanted to finish this quick but my dignity keeps me on this instead of side-tracking to the triangle thingy or kernel module (I was going to read this...)
        And yeah as a grown-ass man I am using pinterest to get aesthetic ideas for the 'game' 


        Color Ideas 
            1- A classic pong yk...black background whilte paddles (those are called paddle right?)
            2- Electric Purple & Night for a cyberpunkish apperance
            3- Blaze&Void maybe...
            Fuck it Imma add all of them... with a switch option
*/










/*  =========== DEFINES ==========  */

#define WIDTH 1200
#define HEIGHT 900 //Still 4:3 like a CRT monitor...I mean we're building a pong duh...

#define FPS 60

#define PADDLE_SIZE (Vector2) {WIDTH/5,HEIGHT/30}
#define SPEED 1.5f


/*  ========== COLORS ===========  */




/*Since this is a game I gotta make design choices right... let me get a RGB wheel to reference*/



/*  =========== OBJECTS ============ */

typedef struct{

    Vector2 size;
    Vector2 position;
    
    float speed; //I may add power ups depending on the flowstate so speed may differ

    int score;  //Shoud I keep score in players? dunno that's my first time making a game lmfao
    
    Color color; //Yeah I wanna be that extra
}player;


typedef struct{

    float radius;
    
    Vector2 position; //Pos X , pos Y

    float vX; //Pong doesn't have fucking friction right?
    float vY; //Velocity on X,Y


    Color color; //Color...because I am this extra lol
}ball;






int main(void)
{

    InitWindow(WIDTH,HEIGHT,"Pong Duh...?");
    if (!IsWindowReady()) { perror("Window may not be ready but Linux is B;) \n"); return(-13); }
    SetTargetFPS(FPS);

    ball pongBall = { 0 };
    
    pongBall.position = (Vector2){WIDTH/2.0f,HEIGHT/2.0f}; //It requires casting for some reason that I couldn't grasp
    pongBall.radius = 3.0f;
    pongBall.vX = 2.5f;
    pongBall.vY = 1.5;
    pongBall.color = (Color){53,13,0,255};

    player p1 = { 0 };
    p1.size = (Vector2) {WIDTH/120.0f,HEIGHT/15.0f};
    p1.position = (Vector2) {WIDTH/16.0f,HEIGHT/2.0f} ;
    p1.color = WHITE;
    p1.speed = 1.5f;

    player p2 = { 0 };

    p2.size = (Vector2) {WIDTH/120.0f,HEIGHT/15.0f};
    p2.position = (Vector2) {15.0f*(WIDTH)/16.0f,HEIGHT/2.0f} ;
    p2.color = WHITE;
    p2.speed = 3.1f;




    while (!WindowShouldClose()) {
        
        if (IsKeyPressed(KEY_ESCAPE)) { CloseWindow(); } //Raylib does handle that itself for ESC but I love what I'm working with...
        if (IsKeyDown(KEY_W)) { p1.position.y -= p1.speed;}
        if (IsKeyDown(KEY_S)) { p1.position.y += p1.speed;}
        //Frame-rate dependent. tbh 2 people playing on the same rig wouldn't cause any problem but I'll fix it for sake of fixing it anyways
        if (IsKeyDown(KEY_UP)) { p2.position.y -= p2.speed;}
        if (IsKeyDown(KEY_DOWN)) { p2.position.y += p2.speed;}  //It does work at the same time on the same keyboard lol YIPPIE!
        



        BeginDrawing();
        ClearBackground(BLACK);
        DrawCircleV(pongBall.position,pongBall.radius, pongBall.color);
        DrawRectangleV(p1.position,p1.size,p1.color);
        DrawRectangleV(p2.position,p2.size,p2.color);
        EndDrawing();
        pongBall.position.x += pongBall.vX;
        pongBall.position.y += pongBall.vY;        //Yup it yeets itself now
    }

    return(0);
}