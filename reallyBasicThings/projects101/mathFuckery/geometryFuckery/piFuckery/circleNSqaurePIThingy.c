
/*
        Wassup? Today's PI fuckery is... yet another Monte Carlo method to estimate pi which is putting a circle in a square 

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

            0- Math related parts lol (calculaton for PI/4) That remains... 
            1- Dynamic memory allocation (Realligator came)
            2- Explicit error handling (On it's way)
*/


/* =========== INCLUDES ================== */

#include <stdio.h>  //To break Inertia 
#include <stdlib.h> //for dynamic memory shit 
#include <err.h>
#include <sys/errno.h>
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

#define FPS 180     //I fucking swear if I type 120 for FPS one more time I'll reinvent V-sync (or atleast look into raylib.h to see if it has a flag for it)


/* UI Design defines */
#define BG CLITERAL(Color){56,0,0,255}
#define ANTI_BG CLITERAL(Color){0,28,56,255} //I guess CLITERAL is a post-C99 thing but not sure yet
#define I_RAN_OUT_OF_COLOR_NAME (Color){0,56,28,255}
#define FONT_SIZE 30

//To future me: Do the thing (nah just kidding just make the color palette look beautiful for now it's just random colors...my eyes are bleeding) 

/* Actually useful defines */
#define C_RADIUS 250.0f
#define C_CENTER_X (WIDTH/2) //I do not fucking trust the gaslit text substitudes with math priority
#define C_CENTER_Y (HEIGHT/2)

#define BUFFER 1024 //Yeah I love working with a page of bytes even it means nothing 4096 is a neat number
#define POINTS_PER_SECOND 180.0f

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

/*I have a custom return hierarchy... void, int, other basic types, custom types, and pointer returns just below the type itself like int and (int *)*/
void drawShapes(Shapes shapes);
void drawThePoints(Vector2 *pointArr,size_t size);
void displayPI(void);
void displayEstimatedPI(float estPI);

int initEnv(void);
int isInCircle(Vector2 point,Ring targetCirc);
float estimatePI(DropCounter dropCount);


Shapes setShapes(Vector2 pos,float radius);

Vector2 getRandPoint(Vector2 pos, float radius);
Vector2 *realligator(Vector2 *arr,int *currentSize );

int main(void)
{

    //General Init/Set up 
    int retVal = 0;
    int currentArrSize = BUFFER;

    printf("This printf here because I want to shut cc warnings\n");
    //Yeah I made the entropy level platform dependent lmfao...even before using it 
    #ifdef WINDOWS_SUX
        srand(time(NULL));
    #else
        srand(time(NULL)^getpid());
    #endif
    
    Vector2 *points = (Vector2 *)(malloc(sizeof(Vector2)*currentArrSize));
    if (points == NULL) {
        retVal = (-1);
        goto clean;
    }
    
    //Future me problem : Make this shit full screen
    if (initEnv()) {retVal = (-13); goto clean; } //That's way cleaner lmfao why I didn't think of that before
    
    Vector2 startPos = (Vector2){C_CENTER_X, C_CENTER_Y};
    
    Shapes shapes = setShapes(startPos,C_RADIUS);

    //That's gonna be dynamic 

   
    DropCounter drops = { 0 };
    float estimatedPI = 0.0f;

    // 4*(in circle) / Total 

    float pointAccumulator = 0.0f;
    int iter = 0;
    //Game loop
    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_ESCAPE)) { CloseWindow(); }

        pointAccumulator += GetFrameTime() * POINTS_PER_SECOND;
        int pointsToAdd = (int)pointAccumulator;
        pointAccumulator -= pointsToAdd;

        for (int i = 0; i < pointsToAdd; ++i) {
                if (iter >= currentArrSize) {
                    points = realligator(points,&currentArrSize);
                    if (currentArrSize == -1) {
                        retVal = (-1);
                        goto clean;
                    }

            }

            points[iter] = getRandPoint(startPos,C_RADIUS);
            ++drops.totalPoints;
            if (isInCircle(points[iter], shapes.ring)) {
                ++drops.inCirclePoints;
            }
            ++iter;
        }

        estimatedPI = estimatePI(drops);

        //Draw loop 
        BeginDrawing();
        ClearBackground(BG);
        displayPI();
        displayEstimatedPI(estimatedPI);
        drawShapes(shapes);
        drawThePoints(points,iter);
        EndDrawing();
    }


clean :     //Honest take goto for debugging feels so easy to use... Poor Man's gdb

    free(points);
    points = NULL; //Or should I type (void *)0 lmfao
    CloseWindow();

    switch (retVal)
    {
        case -1:
            err(ENOMEM,"You ran out of RAM bruh");
            break;
        case -13:
            perror("Window got fucked up\n");
            break;
        default:
            break;
    }
    
    return(retVal);
}

/*
    Allocated data by far: 1
    Frees:1 

    Yeah I am a memory accountant I guess...
*/


void drawShapes(Shapes shapes)
{
        //Rect and contrast
        DrawRectangleV((Vector2){shapes.rect.x, shapes.rect.y}, (Vector2){shapes.rect.width, shapes.rect.height}, ANTI_BG);
        DrawRectangleLines(shapes.rect.x, shapes.rect.y, shapes.rect.width, shapes.rect.height,BLACK); //Contrast is cool shit ngl
        
        //Circ and contrast
        DrawCircle(shapes.ring.pos.x,shapes.ring.pos.y,shapes.ring.radius,ANTI_BG);
        DrawCircleLines(shapes.ring.pos.x,shapes.ring.pos.y,shapes.ring.radius,BLACK);
}

void displayPI(void)
{
        DrawText(TextFormat("PI : %.22lf",PI),  32, 10, FONT_SIZE, I_RAN_OUT_OF_COLOR_NAME); //Using PI or M_PI is me admiting defeat...
}

void displayEstimatedPI(float estPI)
{
        DrawText(TextFormat("PI : %.15f",estPI),  32, 40, FONT_SIZE, I_RAN_OUT_OF_COLOR_NAME); 
}

void drawThePoints(Vector2 *pointArr,size_t size)    //Lmfao I wanted to be fancy with size_t 
{   
    int i = 0;
    while (i < size) {
        DrawPixelV(pointArr[i],I_RAN_OUT_OF_COLOR_NAME);
        ++i;
    }
} 


int initEnv(void)
{
    //Config flags
    SetConfigFlags(FLAG_MSAA_4X_HINT);    
    //Bruh fuck V-sync we YOLO
    
    //init win
    InitWindow(WIDTH, HEIGHT,"PI but with Circles");
    if (!IsWindowReady()) { TraceLog(LOG_ERROR,"Something happened?\n"); return(-1); }
    SetTargetFPS(FPS);
    return(0);
}


int isInCircle(Vector2 point,Ring targetCirc)
{
    float relativeX = point.x - targetCirc.pos.x;
    float relativeY = point.y - targetCirc.pos.y;
    float distanceSquared = (relativeX * relativeX) + (relativeY * relativeY);
    float radiusSquared = targetCirc.radius * targetCirc.radius;

    if (distanceSquared <= radiusSquared) {
        return(1);
    }
    return(0);
}

float estimatePI(DropCounter dropCount)
{
    if (dropCount.totalPoints == 0) {
        return(0.0f);
    }

    float estimatedPI = 4.0f*((float) dropCount.inCirclePoints / dropCount.totalPoints);

    return(estimatedPI);
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

Vector2 *realligator(Vector2 *arr,int *currentSize)
{
    if (arr == NULL) {
        arr = (Vector2 *)(malloc(sizeof(Vector2)*BUFFER));
        if (arr == NULL) { *currentSize = -1; return(NULL); }
    
        return(arr);
    }

    size_t newSize = sizeof(Vector2)*((*currentSize)+BUFFER);
    Vector2 *temp = (Vector2 *)(realloc(arr,newSize));

    if (temp == NULL) { *currentSize = -1; return(arr); }
    arr = temp;
    
    (*currentSize)+=BUFFER;
    return(arr);
}
