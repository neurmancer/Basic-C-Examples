
/*
        Sup? You watch 3 Blue 1 Brown right? Yeah me too... I saw a video: https://www.youtube.com/watch?v=HEfHFsfGXjs <- This one to be specific...
        So...here we are with more Pi fuckery even tho my promise about continuing with futureShit but...Pi fuckery needs its own subfolder

        Dunno anything yet...Imma watch the video and start coding but as always that's a template for tomorrow I guess...
        
        So...here's the tea: We'll get 2 blocks, one big and one small then make the big one bully small one 
        Question is 'how?'


            Yk? let's leave it like that for a while...I've burnt out again
*/

/* =========== INCLUDES ============== */

#include <raylib.h>     //When raylib started being the first lib I include...I realized I have become a changed man...


/* ================== DEFINES ================= */

//Window Init defines 

#define WIDTH 1200.0f
#define HEIGHT 900.0f

#define FPS 120

//Physics Object defines 

#define SIZE_SMALL 130.0f       //They're square so... one side is enough
#define SIZE_BIG 250.0f



/* ================== STRUCTS ================= */

typedef struct{
    Vector2 pos;
    double  vx, m;        // X : POS | VX: Velocity | m: Mass (not slope lol) 
    double edgeSize;        //Again...they're square
    //Yeah since I don't plan to move on Y axis one 1 dimensional position and vel would work Ig...
}Block;


/* ================== GLOBALS ================= */




/* =========== FUNCTION PROTOTYPES ============ */

void setBlocks(Block *bigOne, Block *lessBigOne);           
void drawBlocks(Block blockArr[2]);

int setUpWindow(void);

/* ================== MAIN ================= */

int main(void)
{

    Block bully = { 0 };        //Big one 
    Block nerd = { 0 };         //Small one (if you can't tell duh)
    
    setBlocks(&bully, &nerd);


    Block blocks[] = {bully,nerd};
    
    


    if (setUpWindow() == -1) {
        return(-1);
    }

    while (!WindowShouldClose()) {
    
        //To-Do: Do the thing

        BeginDrawing();
        ClearBackground(BLACK);
        drawBlocks(blocks);
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


void setBlocks(Block *bigOne, Block *lessBigOne)
{
    bigOne->pos = (Vector2){WIDTH/3,HEIGHT/4};       //Lol I learned what the cast looking as thing is btw it's a C compound literal  
    bigOne->vx = -0.5f;      //Towards left  (I lowkey really started to type like a corpo but better than forcing jokes)
    bigOne->m = 100.0f;
    bigOne->edgeSize = SIZE_BIG;

    float offset = SIZE_BIG-SIZE_SMALL;
    lessBigOne->pos = (Vector2){(2*WIDTH)/3,(HEIGHT/4)+offset};
    lessBigOne->vx = 0.0f;  
    lessBigOne->m = 10.0f;
    lessBigOne->edgeSize = SIZE_SMALL;
}

void drawBlocks(Block blockArr[2])
{
    for (int i = 0;i < 2;i++) {
        DrawRectangle(blockArr[i].pos.x,blockArr[i].pos.y, blockArr[i].edgeSize , blockArr[i].edgeSize, WHITE);
    }
}
