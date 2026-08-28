/*
            =============== YAPPING =====================

            'Sup? Yk...the deal I got shit to mark as done in futureShit.md... so here we are starting to code it....
            
            First, I changed my rig setup (DWM to Hyprland to try) and raylib is currently bitching about it 
                -Solved it via changing my raylib pack to raylib-wayland 
            Second, This is a template for now I'll try to finish this in a few days if not in a few hours

            So...the technical part: 

            What are we doing? Breakout clone, but question is 'how' since I have no clue how to do...

            Shit to do: 

            1- Well...code everything
            2- Paddle movment
            3- Brick offsets and drawing shit
            4- Collision detection (Hardest part, it seems)
                Since raylib's collision just answers the 'did collision happen' and I need the 'which' part more so AABB collision it is...
                Checking balls position for each brick is another pain in the ass so we'll optimize that shit 


            5- Ball movement and shit


            This is a template for now 
*/


/* ================== INCLUDES ===================== */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

#define BRICK_ROWS 6
#define BRICK_COLUMNS 12

//Colors (using the same colors from gravityThingy.c)

#define SKY_BLUE        CLITERAL(Color){  79, 195, 247, 255 }  // #4FC3F7
#define AZURE           CLITERAL(Color){  41, 182, 246, 255 }  // #29B6F6
#define ELECTRIC_CYAN   CLITERAL(Color){   0, 229, 255, 255 }  // #00E5FF
#define TURQUOISE       CLITERAL(Color){  38, 198, 218, 255 }  // #26C6DA
#define NEON_GREEN      CLITERAL(Color){   0, 230, 118, 255 }  // #00E676
#define EMERALD         CLITERAL(Color){ 102, 187, 106, 255 }  // #66BB6A
#define LIME_GREEN      CLITERAL(Color){ 156, 204, 101, 255 }  // #9CCC65
#define YELLOW_GREEN    CLITERAL(Color){ 212, 225,  87, 255 }  // #D4E157
#define BRIGHT_YELLOW   CLITERAL(Color){ 255, 235,  59, 255 }  // #FFEB3B
#define GOLDY            CLITERAL(Color){ 255, 213,  79, 255 }  // #FFD54F
#define AMBER           CLITERAL(Color){ 255, 183,  77, 255 }  // #FFB74D
#define ORANGEY          CLITERAL(Color){ 255, 152,   0, 255 }  // #FF9800
#define CORAL           CLITERAL(Color){ 255, 112,  67, 255 }  // #FF7043
#define DEEP_ORANGE     CLITERAL(Color){ 244,  81,  30, 255 }  // #F4511E
#define REDISH             CLITERAL(Color){ 239,  83,  80, 255 }  // #EF5350
#define MAGENTA_DUH         CLITERAL(Color){ 233,  30,  99, 255 }  // #E91E63
#define PINKY            CLITERAL(Color){ 240,  98, 146, 255 }  // #F06292
#define HOT_PINK        CLITERAL(Color){ 236,  64, 122, 255 }  // #EC407A
#define SHE_LOVES_PURPLE          CLITERAL(Color){ 171,  71, 188, 255 }  // #AB47BC
#define SO_DO_I          CLITERAL(Color){ 126,  87, 194, 255 }  // #7E57C2
#define INDIGO          CLITERAL(Color){  92, 107, 192, 255 }  // #5C6BC0
#define BLUE_GRAY       CLITERAL(Color){ 144, 164, 174, 255 }  // #90A4AE
#define SILVER          CLITERAL(Color){ 207, 216, 220, 255 }  // #CFD8DC
#define RED_AF          CLITERAL(Color){  41,   3,   0, 255 }  // #290300

#define COLOR_ARR_SIZE 24

static const float BRICK_LENGTH = WIDTH/14; //That's gonna be used as left-right offset too  
static const float BRICK_HEIGHT = HEIGHT/32;    //That might differ
static const float Y_OFFSET = HEIGHT/10;
static const float X_OFFSET = BRICK_LENGTH/8;
//Why static? 'cuz scope thingy is a bitch...(not like I use multiple files but what if I Do?)

/* =================== OBJECTS ========================= */

typedef struct{

    Vector2 pos;
    Vector2 size;

    Color color;

    int isDestroyed;
    int powerUp;

}Brick;

typedef struct{

    Vector2 pos;
    Vector2 vel;
    Vector2 accel;  //For future power-ups

    float radius;

    Color color;
}Ball;

typedef struct{

    Vector2 pos;
    Vector2 speed;
    Vector2 size;
    Color color;

}Paddle;

typedef struct{
    int remainingLives;
    int score;

}GameState;


typedef struct{

    //I ain't gonna optimize padding for a fucking breakout clone 
    Paddle paddle;
    Ball ball;

    Brick bricks[BRICK_ROWS][BRICK_COLUMNS];

    GameState gameState;
}Objects;

typedef struct{

    //I'll try to make this configurable 'cuz why not but not now...

    Vector2 paddleSize;    
    float paddleSpeed;

    Color paddleColor; 

    Vector2 ballVel;
    Vector2 ballAccel;

    float ballRadius;
    Color ballColor;
   
    int scorePerBrick;
    int playerLives;
}Config;

/* ================ (Hopefully Not) GLOBALS ================ */



/* ================= FUNCTION PROTOTYPES ==================== */

void drawObjects(Objects *objs);
void setObjects(Objects *objs, Config *cfg);
void updateObjects(Objects *objs);

int setupEnv(void);
Color randColor(void);


/* ============ MAIN ============= */

int main(void)
{

    printf("C'mon I have to start with a printf right\n");
    srand(time(NULL));

    if(setupEnv()) { printf("We fucked\n"); return(-53); }


    Objects objs = { 0 };
    
    Config cfg = {
        .paddleSize = (Vector2){WIDTH/5, HEIGHT/50},
        .paddleSpeed = 3,   //Pixel/dT
        .paddleColor = WHITE,

        .ballRadius = WIDTH/60,
        .ballVel = (Vector2){1,0},
        .ballAccel = (Vector2){ 0 },
        .ballColor = WHITE,
    
        .playerLives = 3,
        .scorePerBrick = 100,
    };
    printf("Og debug tool\n");
    setObjects(&objs, &cfg);
    printf("Test\n");

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_ESCAPE)) { break;}
        if(IsKeyDown(KEY_A)) { objs.paddle.pos.x -= objs.paddle.speed.x; }  //Those are placeholders for tomorrow
        if(IsKeyDown(KEY_D)) { objs.paddle.pos.x += objs.paddle.speed.x; }

        BeginDrawing();
        ClearBackground(BLACK);
        drawObjects(&objs);
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
    if (!IsWindowReady()) { return(-1); }

    if ((FPS < 0 || FPS > 300) && !VSYNC) { SetTargetFPS(120); }
    else { SetTargetFPS(FPS); }


    return(0);
}

Color randColor(void)
{
    static const Color COLOR_PALETTE[COLOR_ARR_SIZE] = {
    SKY_BLUE,
    AZURE,
    ELECTRIC_CYAN,
    TURQUOISE,
    NEON_GREEN,
    EMERALD,
    LIME_GREEN,
    YELLOW_GREEN,
    BRIGHT_YELLOW,
    GOLDY,
    AMBER,
    ORANGEY,
    CORAL,
    DEEP_ORANGE,
    REDISH,
    MAGENTA_DUH,
    PINKY,
    HOT_PINK,
    SHE_LOVES_PURPLE,
    SO_DO_I,
    INDIGO,
    BLUE_GRAY,
    SILVER,
    RED_AF
    };

    return(COLOR_PALETTE[rand()%COLOR_ARR_SIZE]);
}


void setObjects(Objects *objs, Config *cfg)
{
    
    //Paddle Shit
    objs->paddle.size = cfg->paddleSize;
    objs->paddle.pos = (Vector2){((WIDTH-objs->paddle.size.x)/2), 24*HEIGHT/25 };
    objs->paddle.speed.x = cfg->paddleSpeed;
    objs->paddle.speed.y = 0;

    objs->paddle.color = cfg->paddleColor;

    //Ball shit
    objs->ball.radius = cfg->ballRadius;
    objs->ball.pos.x = objs->paddle.pos.x + (objs->paddle.size.x/2);
    objs->ball.pos.y = objs->paddle.pos.y - objs->ball.radius;
    objs->ball.vel = cfg->ballVel;
    objs->ball.accel = cfg->ballAccel;
    objs->ball.color = cfg->ballColor;

    objs->gameState = (GameState){cfg->playerLives, 0};
    
    for (size_t i = 0;i < BRICK_COLUMNS; i++) {
        for (size_t j = 0; j < BRICK_ROWS; j++) {
            objs->bricks[j][i].pos = (Vector2){(i+1)*BRICK_LENGTH + X_OFFSET, (j*BRICK_HEIGHT)+Y_OFFSET};
            objs->bricks[j][i].size = (Vector2){BRICK_LENGTH, BRICK_HEIGHT};
            objs->bricks[j][i].color = randColor();
            objs->bricks[j][i].powerUp = -1;
            objs->bricks[j][i].isDestroyed = 0;
        }
    }
    //I guess every fucking thing is settled but I HIGHLY DOUBT THAT THIS IS THE FUCKING RIGHT WAY
    return;
}


void drawObjects(Objects *objs)
{

    for (size_t i = 0; i < BRICK_COLUMNS; i++) {
        for (size_t j = 0; j < BRICK_ROWS; j++) {
            if (objs->bricks[j][i].isDestroyed) {
                continue;
            }
            DrawRectangleV(objs->bricks[j][i].pos, objs->bricks[j][i].size, objs->bricks[j][i].color);
            DrawRectangleLinesEx(
            (Rectangle){objs->bricks[j][i].pos.x,objs->bricks[j][i].pos.y, objs->bricks[j][i].size.x, objs->bricks[j][i].size.y}, 
            3.5f, 
            BLACK);
        }
    }
    DrawRectangleV(objs->paddle.pos, objs->paddle.size, objs->paddle.color);
    DrawCircleV(objs->ball.pos, objs->ball.radius , objs->ball.color);

}