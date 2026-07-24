
/*
        Sup? You watch 3Blue1Brown right? Yeah me too... I saw a video: https://www.youtube.com/watch?v=HEfHFsfGXjs <- This one to be specific...
        So...here we are with more Pi fuckery even tho my promise about continuing with futureShit but...Pi fuckery needs its own subfolder

        Dunno anything yet...Imma watch the video and start coding but as always that's a template for tomorrow I guess...
        
        So...here's the tea: We'll get 2 blocks, one big and one small then make the big one bully small one 
        Question is 'how?'


*/

/* =========== INCLUDES ============== */

#include <raylib.h>     //When raylib started being the first lib I include...I realized I have become a changed man...

/* ================== DEFINES ================= */

//Window Init defines 

#define WIDTH 1200.0f
#define HEIGHT 900.0f

#define FPS 120

//Physics Object defines 

#define SIZE_SMALL 50.0f       //They're square so... one side is enough
#define SIZE_BIG 100.0f

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

    Block blocks[2];
    
    Line wall;
    Line floor;     //I don't want globals in this project so setObject function gonna be a huge one and I don't wanna send every object pointer seperately

}Objects;

/* ================== GLOBALS ================= */




/* =========== FUNCTION PROTOTYPES ============ */

void setObjects(Objects *objects);           

// Drawing functions
void drawBlocks(Block blockArr[BLOCK_AMOUNT]);
void drawWallandFloor(Line wall,Line floor);


//Shit required 
int setUpWindow(void);

/* ================== MAIN ================= */

int main(void)
{

    Block bully = { 0 };        //Big one 
    Block nerd = { 0 };         //Small one (if you can't tell duh)
    Line wall = { 0 };
    Line floor = { 0 };

    Objects objectArray = {bully,nerd,wall,floor};


    setObjects(&objectArray);       //Set object function takes blocks[0] as big one DON'T FORGET




    if (setUpWindow() == -1) {
        return(-1);
    }

    while (!WindowShouldClose()) {
    
        //To-Do: Do the thing

        BeginDrawing();
        ClearBackground(BLACK);
        drawWallandFloor(objectArray.wall,objectArray.floor);
        drawBlocks(objectArray.blocks);
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


void setObjects(Objects *object)
{
    object->blocks[0].pos = (Vector2){WIDTH/3,HEIGHT/2};       //Lol I learned what the cast looking as thing is btw it's a C compound literal  
    object->blocks[0].vx = -0.5f;      //Towards left  (I lowkey really started to type like a corpo but better than forcing jokes)
    object->blocks[0].m = 100.0f;
    object->blocks[0].edgeSize = SIZE_BIG;

    float offset = SIZE_BIG-SIZE_SMALL;
    object->blocks[1].pos = (Vector2){(2*WIDTH)/3,(HEIGHT/2)+offset};
    object->blocks[1].vx = 0.0f;  
    object->blocks[1].m = 10.0f;
    object->blocks[1].edgeSize = SIZE_SMALL;

    object->wall.p1.x = WALL_X; 
    object->wall.p1.y = HEIGHT/10;

    object->wall.p2.x = WALL_X; 
    object->wall.p2.y = (HEIGHT/2)+offset+SIZE_SMALL;

    object->floor.p1.x = WALL_X;
    object->floor.p1.y = (HEIGHT/2)+offset+SIZE_SMALL;

    object->floor.p2.x = WIDTH/1.05f;
    object->floor.p2.y = (HEIGHT/2)+offset+SIZE_SMALL;

}

void drawBlocks(Block blockArr[BLOCK_AMOUNT])
{
    for (int i = 0;i < 2;i++) {
        DrawRectangle(blockArr[i].pos.x,blockArr[i].pos.y, blockArr[i].edgeSize , blockArr[i].edgeSize, WHITE);
    }
}

void drawWallandFloor(Line wall,Line floor)
{
    DrawLineEx(wall.p1,wall.p2,LINE_THICKNESS, WHITE);
    DrawLineEx(floor.p1,floor.p2,LINE_THICKNESS, WHITE);
    
}