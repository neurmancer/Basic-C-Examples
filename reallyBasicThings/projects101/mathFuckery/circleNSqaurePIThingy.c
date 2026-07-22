
/*
        Wassup? Today's PI fuckery is... yet another Monter Carlo method to estimate pi which is putting a circle in a square 

        It's 4AM...I won't even question why I am doing this, this time but here is the Important Shit to Know:
        0- We need a circle (or just ring) with radius of r
        1- And put it in the middle of square with 2r long sides 
        2- Then  we draw random points on the given area (square)
        3-Then we do some math which I forgot at the moment... it was something like... all points/the ones in the circle or shit...
        and bruh I swear this is the last one before I get into track with futureShit.md probably starting with cat clone (which I'll call kitty) and byte interpreter ig...
        And yeah If I add another pi estimation method in any time I'll make a subfolder called PI fuckery 
 
        Atp you know how I structure raylib projects... It's like a mental boilerplate

        this file also requires -lraylib as you compile

        I probably need to hold previous points generated to display them...so DYANMIC MEMORY SHIT IT IS

        Under construction parts:

            0- Math related parts lol (calculaton for PI/4) 
            1- Dynamic memory allocation (Realligator coming)
            2- Explicit error handling
*/


/* =========== INCLUDES ================== */

#include <stdio.h>  //To break Inertia 
#include <stdlib.h> //for dynamic memory shit 
#include <time.h>   //For random seeding...lmfao I really started to write corpo-like
#include <raylib.h> //For graphics
    
    //For getpid in case of Unix 
#ifdef __unix__
    #include <unistd.h>
#elif __WIN32
    #define WINDOWS_SUX 1
#endif


/* =============== DEFINES ================ */

/* Graphical defines */
#define WIDTH 1200.0f
#define HEIGHT 900.0f

#define FPS 120     //I fucking swear if I type 120 for FPS one more time I'll reinvent V-sync (or atleast look into raylib.h to see if it has a flag for it)

/* UI Design defines */
#define BG CLITERAL(Color){56,0,0,255}
#define ANTI_BG CLITERAL(Color){0,56,56,255} //I guess CLITERAL is a post-C99 thing but not sure yet
#define FONT_SIZE 30

//To future me: Do the thing (nah just kidding just make the color palette look beautiful for now it's just random colors...my eyes are bleeding) 

/* Actually useful defines */
#define C_RADIUS 250.0f
#define C_CENTER_X (WIDTH/2) //I do not fucking trust the gaslit text substitudes with math priority
#define C_CENTER_Y (HEIGHT/2)

#define BUFFER 4096


/* =========== OBJECTS ============= */

typedef struct{
    Vector2 pos;
    float radius;
    //This is a made up one...not originiated from raylib
}Ring;



typedef struct{
    Rectangle rect;
    Ring ring;
}Shapes;


typedef struct{
    int totalPoints;
    int inCirclePoints;
}DropCounter;

/* =========== FUNCTION PROTOTYPES ============ */

/*I have a custom return hierarchy... void, int, other basic types, custom types, and pointer returns*/
void drawShapes(Shapes shapes);
void displayPI(void);

int initEnv(void);

Shapes setShapes(Vector2 pos,float radius);
Vector2 getRandPoint(Vector2 pos, float radius);

int main(void)
{
    //Yeah I made the entropy level platform dependent lmfao...even before using it 
    #ifdef WINDOWS_SUX
        srand(time(NULL));
    #else
        srand(time(NULL)^getpid());
    #endif
    
    
    //Future me problem : Make this shit full screen
    if (initEnv()) {return(-1); } //That's why cleaner lmfao why I didn't think of that before
    
    Vector2 startPos = (Vector2){C_CENTER_X, C_CENTER_Y};
    
    Shapes shapes = setShapes(startPos,C_RADIUS);

    //That's gonna be dynamic 
    Vector2 points[100000] =  { 0 };
    for (int i = 0;i < 100000;i++) {
        points[i] = getRandPoint(startPos,C_RADIUS);
    }
    
    DropCounter drops = { 0 };

/* ======== Debug field ======== */


//    goto debug;


/* __________________________*/

    int iter = 0;
    //Game loop
    while (!WindowShouldClose() && iter < 100000) {
        
        if (IsKeyPressed(KEY_ESCAPE)) { CloseWindow(); }



        //Draw loop 
        BeginDrawing();
        ClearBackground(BG);
        displayPI();
        drawShapes(shapes);
        //That's gonna be in a function
        for (int i = 0;i < iter;i++) {
            DrawPixelV(points[i],PURPLE);
        }
        EndDrawing();
        iter++;
    
    }


debug :     //Honest take goto for debugging feels so easy to use... Poor Man's gdb


    return(0);
}


void drawShapes(Shapes shapes)
{
        //Rect and contrast
        DrawRectangleV((Vector2){shapes.rect.x, shapes.rect.y}, (Vector2){shapes.rect.width, shapes.rect.height}, ANTI_BG);
        DrawRectangleLines(shapes.rect.x, shapes.rect.y, shapes.rect.width, shapes.rect.height,BLACK); //Contrast is cool shit ngl
        
        //Circ and contrast
        DrawCircle(shapes.ring.pos.x,shapes.ring.pos.y,shapes.ring.radius,BEIGE);
        DrawCircleLines(shapes.ring.pos.x,shapes.ring.pos.y,shapes.ring.radius,BLACK);
}

void displayPI(void)
{
        DrawText(TextFormat("PI : %.22lf",PI),  32, 10, FONT_SIZE, BEIGE); //Using PI or M_PI is me admiting defeat...
}



int initEnv(void)
{
    //Config flags
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    
    //init win
    InitWindow(WIDTH, HEIGHT,"PI but with Circles");
    if (!IsWindowReady()) { TraceLog(LOG_ERROR,"Something happened?\n"); return(-1); }
    SetTargetFPS(FPS);

    return(0);
}

Shapes setShapes(Vector2 pos,float radius)
{
    //Yeah I love naming shit with the first four letter of the word
    Shapes rectNcirc = { 0 };
    Ring circ = {pos,radius};
    Vector2 posRect = {pos.x-radius,pos.y-radius};
    Vector2 sizeRect = {(radius*2), (radius*2)}; //Square wrapping around the ring I Could've done the PI/4 version but that is visually more pleasing to me  
    Rectangle rect = {posRect.x, posRect.y,sizeRect.x, sizeRect.y};         //I know x,y is not the best term for width and height but we're rolling with raylib's Vector2
    //If I create a graphical API I'll consider renaming it with width and height lmfao
    
    rectNcirc.ring = circ;
    rectNcirc.rect = rect;
    
    return(rectNcirc);
}


Vector2 getRandPoint(Vector2 pos, float radius)
{
    Vector2 randPoint = { 0 };
    Vector2 leftCorner = { pos.x-radius, pos.y-radius};
    
    randPoint.x = ((float) rand() / RAND_MAX)*2*radius;
    randPoint.y = ((float) rand() / RAND_MAX)*2*radius;

    randPoint.x += leftCorner.x;  
    randPoint.y += leftCorner.y;

    return(randPoint);
}
