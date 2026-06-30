/*  ======== INCLUDES ============   */

#include <math.h>
#include <stdint.h>
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


        Before I overcomplicate shit I gotta define what is pong in its core to myself
            1- Two paddles hitting to the ball (duh...)
            2- Should the ball change angles based on the which side of the paddles (and how far from center of the paddle) or should angle changes happen when it hits the shorter sides
            3- And collision detection (all three sides for paddles? does raylib have something like that?We'll see...)
            4- Keeping score when the ball hits one of the walls behind 
            5-Maybe a game screen to start the game


        AND I'll use the most cursed way to print score on the screen raylib requires string and I keep score as int so here is the idea: score+48 is the char version of score lmfao (and before we get random chars we finish the game at 5)



        Here is the yoinking from rcore.c part starts...

            
            bool CheckCollisionCircleLine(Vector2 center, float radius, Vector2 p1, Vector2 p2); I'll probaby need this instead of 
            
            bool CheckCollisionCircleRec(Vector2 center, float radius, Rectangle rec); //since this one will give me whether ball collides with paddle or not and the other one I can look for each edge seperatly 


*/










/*  =========== DEFINES ==========  */

#define WIDTH 1200
#define HEIGHT 900 //Still 4:3 like a CRT monitor...I mean we're building a pong duh...

#define FPS 60

#define PADDLE_SIZE (Vector2) {WIDTH/120.0f,HEIGHT/15.0f}
#define PADDLE_SPEED 120.0f


/*  ========== COLORS ===========  */

/*  Backgrounds */

#define PURPLSIH_BG (Color){50,20,45,127}
#define VIOLET_BG (Color){12,10,62,255}

/* Paddles & ball*/

#define NEON_LINE (Color){158,255,31,255}
#define CRIMSON (Color){153,0,51,255}


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


/*  ======= FUNCTION PROTOTYPES ===== */

void CheckEdges(player *p,int height);


typedef struct{

    Color bgColor;
    Color objectColor;
}Theme;



/* =========== GLOBAL VARS ============  */

//In radians 

double angle = (2*PI); //Or Zero degrees 



int main(void)
{

    InitWindow(WIDTH,HEIGHT,"Pong Duh...?");
    if (!IsWindowReady()) { perror("Window may not be ready but Linux is B;) \n"); return(-13); }
    SetTargetFPS(FPS);

    Theme classic = {BLACK,WHITE};
    Theme inverted = {WHITE,BLACK};
    Theme neonLime = {PURPLSIH_BG,NEON_LINE};
    Theme retroWavish = {VIOLET_BG,CRIMSON};

    Theme themes[] = {classic,inverted,neonLime,retroWavish};
    ball pongBall = { 0 };
        
    player p1 = { 0 };    
    player p2 = { 0 };

    player players[] = {p1,p2};


    for (int i = 0;i < sizeof(players)/sizeof(players[0]);i++) {
        players[i].size = PADDLE_SIZE;
        players[i].speed = PADDLE_SPEED;
        players[i].score = 0;

    }
    
    players[0].position = (Vector2) {WIDTH/18.0f,HEIGHT/2.0f} ;
    players[1].position = (Vector2) {17*WIDTH/18.0f,HEIGHT/2.0f} ;

    pongBall.position = (Vector2){WIDTH/2.0f,HEIGHT/2.0f}; //It requires casting for some reason that I couldn't grasp
    pongBall.radius = 3.0f;
    pongBall.vX = 125.0f;
    pongBall.vY = 75.0;

  
  
    unsigned int themeChanger = 0;
    int themeSize = sizeof(themes)/sizeof(themes[0]);
    
    Theme selectedTheme = themes[themeChanger];
    
    players[0].color = selectedTheme.objectColor;
    players[1].color = selectedTheme.objectColor;
    pongBall.color = selectedTheme.objectColor;



    while (!WindowShouldClose()) {

        float dt = GetFrameTime();

        //Logic and shit

        /* Dunno what to call this part */
        if (IsKeyPressed(KEY_ESCAPE)) { CloseWindow(); } //Raylib does handle that itself for ESC but I love what I'm working with...
        if (IsKeyPressed(KEY_TAB)) {
            selectedTheme = themes[themeChanger % themeSize];
            players[0].color = selectedTheme.objectColor;
            players[1].color = selectedTheme.objectColor;
            pongBall.color = selectedTheme.objectColor;
            themeChanger++;
        }

            /* ======= CONTROLS ========== */
        if (IsKeyDown(KEY_W)) { players[0].position.y -= players[0].speed*dt; }
        if (IsKeyDown(KEY_S)) { players[0].position.y += players[0].speed*dt; }
        
        if (IsKeyDown(KEY_UP)) { players[1].position.y -= players[1].speed*dt;}
        if (IsKeyDown(KEY_DOWN)) { players[1].position.y += players[1].speed*dt;}  //It does work at the same time on the same keyboard lol YIPPIE!



        for (int i = 0;i < sizeof(players)/sizeof(players[0]);i++) {
            CheckEdges(&players[i],HEIGHT);
        }


        pongBall.position.x += pongBall.vX*dt*cosf(angle+PI);        //Basic Trigo babyyyyyyyy (and probably all I need )
        pongBall.position.y += pongBall.vY*dt*sinf(angle+PI);        //Yup it yeets itself now


        //Drawing

        BeginDrawing();
        ClearBackground(selectedTheme.bgColor);
        for (int i = 0;i < sizeof(players)/sizeof(players[0]);i++)
        {
            DrawRectangleV(players[i].position,players[i].size,players[i].color);
        }
        
        DrawCircleV(pongBall.position,pongBall.radius, pongBall.color);
        EndDrawing();

    }

    return(0);
}

void CheckEdges(player *p,int height)
{
    if (p->position.y <= 0) {
        p->position.y = 0;
    }


    if (p->position.y+p->size.y >= height) {
        p->position.y = height-p->size.y;
    }

}