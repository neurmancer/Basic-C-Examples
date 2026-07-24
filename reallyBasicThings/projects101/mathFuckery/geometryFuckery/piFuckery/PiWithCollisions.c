
/*
        Sup? You watch 3Blue1Brown right? Yeah me too... I saw a video: https://www.youtube.com/watch?v=HEfHFsfGXjs <- This one to be specific...
        So...here we are with more Pi fuckery even tho my promise about continuing with futureShit but...Pi fuckery needs its own subfolder

        Dunno anything yet...Imma watch the video and start coding but as always that's a template for tomorrow I guess...
        
        So...here's the tea: We'll get 2 blocks, one big and one small then make the big one bully small one 
        Question is 'how?'

        Now...I am at the point of actually doing math... or physics I'd say (which is applied math) here's a video about elastic collision by Khan Academy https://www.youtube.com/watch?v=okFcjFD5umU

        and here is the formula I guess we need mass and velocity to determine the after-collision velocity I'll use 'm' for mass and 'u' for old velocity:
        v1 and v2 will be the post-collision velocities

        v1 = [(m1-m2)/(m1+m2)]*u1 + [(2*m2)/(m1+m2)]*u2
        v2 = [(2*m1)/(m1+m2)]*u1 + [(m2-m1)/(m1+m2)]*u2

        I guess that's correct 
        


*/

/* =========== INCLUDES ============== */

#include <raylib.h>     //When raylib started being the first lib I include...I realized I have become a changed man...
#include <stdio.h>

/* ================== DEFINES ================= */

//Window Init defines 

#define WIDTH 1200.0f
#define HEIGHT 900.0f

#define FPS 120

//Physics Object defines 

#define SIZE_SMALL 50.0f       //They're square so... one side is enough
#define SIZE_BIG 100.0f

#define BASE_VEL_SMALL 0.0f
#define BASE_VEL_BIG -100.00f       //Was it 1m/s in the video? should I coin a pixel to meter function...or simply growing vel won't fuck the system? Fuck... 

#define BIG_MASS 10000.0f
#define SMALL_MASS 10.0f

#define BLOCK_AMOUNT 2

#define WALL_X (WIDTH/10)

#define LINE_THICKNESS 3.5f

/* ================== STRUCTS ================= */

typedef struct{
    Vector2 pos;            //I love having everything I need in structs despite y value being fixed for both squares
    double  vx, m;        // X : POS | VX: Velocity | m: Mass (not slope lol) 
    double edgeSize;        //Again...they're square
    //Yeah since I don't plan to move on Y axis one 1 dimensional position and vel would work Ig...
}Block;

typedef struct{

    Vector2 p1;
    Vector2 p2;
}Line;

typedef struct{

    Block blocks[BLOCK_AMOUNT];
    
    Line wall;
    Line floor;     //I don't want globals in this project so setObject function gonna be a huge one and I don't wanna send every object pointer seperately

}Objects;

/* ================== GLOBALS ================= */




/* =========== FUNCTION PROTOTYPES ============ */

// Drawing functions
void drawBlocks(Block blockArr[BLOCK_AMOUNT]);
void drawWallandFloor(Line wall,Line floor);

// Game state? Physics state? 
void updateBlocks(Block blocks[BLOCK_AMOUNT],float dt);




int setUpWindow(void);

int setObjects(Objects *objects);           

/* ================== MAIN ================= */

int main(void)
{

    Block bully = { 0 };        //Big one 
    Block nerd = { 0 };         //Small one (if you can't tell duh)
    Line wall = { 0 };
    Line floor = { 0 };

    Objects objectArray = {.blocks={bully,nerd}, wall, floor};

    int setUpCheck = setObjects(&objectArray);
    if (setUpCheck){       //Set object function takes blocks[0] as big one DON'T FORGET) 
        fprintf(stderr, "This program works with only 2 squares\nCurrent amount: %d\n",setUpCheck);
        return(setUpCheck);
    }



    if (setUpWindow() == -1) {
        return(-1);
    }


    float dt = 0.0f;
    while (!WindowShouldClose()) {
        dt = GetFrameTime();

        updateBlocks(objectArray.blocks, dt);

        BeginDrawing();
        ClearBackground(BLACK);
        drawWallandFloor(objectArray.wall,objectArray.floor);
        drawBlocks(objectArray.blocks);
        DrawText("This place gonna show collision amount", (WIDTH)/3, (HEIGHT/1.50), 20, WHITE);

        EndDrawing();
    }

    CloseWindow();

    return(0);
}


int setUpWindow(void)
{
    SetConfigFlags(FLAG_MSAA_4X_HINT); 
    InitWindow(WIDTH, HEIGHT, "PI COLLIDER?");
    if (!IsWindowReady()) {
        return(-1);
    }
    SetTargetFPS(FPS);

    return(0);
}


int setObjects(Objects *object)
{
    if (BLOCK_AMOUNT != 2) {
        return(BLOCK_AMOUNT);
    }
    
    object->blocks[0].pos = (Vector2){2*WIDTH/3,HEIGHT/2};       //Lol I learned what the cast looking ass thing is btw it's a C compound literal  
    object->blocks[0].vx = BASE_VEL_BIG;      //Towards left  (I lowkey really started to type like a corpo but better than forcing jokes)
    object->blocks[0].m = BIG_MASS;
    object->blocks[0].edgeSize = SIZE_BIG;

    float offset = SIZE_BIG-SIZE_SMALL;
    object->blocks[1].pos = (Vector2){(WIDTH)/3,(HEIGHT/2)+offset};
    object->blocks[1].vx = BASE_VEL_SMALL;  
    object->blocks[1].m = SMALL_MASS;
    object->blocks[1].edgeSize = SIZE_SMALL;

    object->wall.p1.x = WALL_X; 
    object->wall.p1.y = HEIGHT/10;

    object->wall.p2.x = WALL_X; 
    object->wall.p2.y = (HEIGHT/2)+offset+SIZE_SMALL;

    object->floor.p1.x = WALL_X;
    object->floor.p1.y = (HEIGHT/2)+offset+SIZE_SMALL;

    object->floor.p2.x = WIDTH;
    object->floor.p2.y = (HEIGHT/2)+offset+SIZE_SMALL;

    return(0);
}

void drawBlocks(Block blockArr[BLOCK_AMOUNT])
{
    for (int i = 0;i < BLOCK_AMOUNT;i++) {
        DrawRectangle(blockArr[i].pos.x,blockArr[i].pos.y, blockArr[i].edgeSize , blockArr[i].edgeSize, WHITE);
    }
}

void drawWallandFloor(Line wall,Line floor)
{
    DrawLineEx(wall.p1,wall.p2,LINE_THICKNESS, WHITE);
    DrawLineEx(floor.p1,floor.p2,LINE_THICKNESS, WHITE);
    
}

void updateBlocks(Block *blocks, float dt)
{
    //Again... blocks[0] is big, blocks[1] is small one... and BLOCK_AMOUNT instead of hard-coding for not writing on top random addresses
    //Pos update
    for(int i = 0; i < BLOCK_AMOUNT; i++) {
        blocks[i].pos.x += blocks[i].vx * dt; 
    }
    //This might be unncessary verbose but for legibility, might change...might leave like that dunno
    Rectangle bigOne = (Rectangle){blocks[0].pos.x, blocks[0].pos.y, blocks[0].edgeSize, blocks[0].edgeSize};
    Rectangle smallOne = (Rectangle){blocks[1].pos.x, blocks[1].pos.y, blocks[1].edgeSize, blocks[1].edgeSize};
    
    //To make the equation easier I'll format the things with the said v1,v2, u1,u2, and m1,m2 values

    //New velocities
    double v1 = 0.0;
    double v2 = 0.0;

    //Old velocities
    double u1 = blocks[0].vx;
    double u2 = blocks[1].vx;

    double m1 = blocks[0].m;
    double m2 = blocks[1].m;


    /*
            v1 = [(m1-m2)/(m1+m2)]*u1 + [(2*m2)/(m1+m2)]*u2
            v2 = [(2*m1)/(m1+m2)]*u1 + [(m2-m1)/(m1+m2)]*u2

            for reference
    */

    //Raylib's built-in rectangle-rectangle collision detection 
    if(CheckCollisionRecs(bigOne, smallOne))
    {        
        //Velocity of big one?
        v1 = ((m1-m2)/(m1+m2))*u1 + (2*m2)/(m1+m2)*u2;

        //New Velocity of small one?
        v2 = ((2*m1)/(m1+m2))*u1 + (m2-m1)/(m1+m2)*u2;
        
        blocks[0].vx = v1;
        blocks[1].vx = v2;

        //Dev Blog: Somewhat worked for a few seconds then nerd left the screen like a crackhead on an an 'cid trip 
        // Ideas to prevent : 
        // 1- hardcode if past wall pos.x = wall 
        // 2- Calculate multiple steps of simulation but give output for the last point of the blocks (Seperate calculation and visualization I guess)
        // 3- Abonden the project lol
        // 4- Before all that...go eat smthg.

    }

    //Wall collisions
    for (int i = 0;i < BLOCK_AMOUNT;i++) {
        if (blocks[i].pos.x <= WALL_X || blocks[i].pos.x+blocks[i].edgeSize >= WIDTH) {

            blocks[i].vx = (-blocks[i].vx); //Yeah I burned by the =- operator...never again
        }

    }
}