/*
            =========== YAPPING ========= 


    Sup? man...I really stop that but anyways...what's today's fuckery?
    More sierpinski triangle if you haven't seen my old implementation using recursion (which is O(3^n))
    this is another approach to create sierpinksi triangle using Chaos Game (you can check wikipedia: https://en.wikipedia.org/wiki/Sierpiński_triangle )

    But core idea is that:    
        1-Take three points in a plane to form a triangle.
        2-Randomly select any point inside the triangle and consider that your current position.
        3-Randomly select any one of the three vertex points.
        4-Move half the distance from your current position to the selected vertex.
        5-Plot the current position.
        6-Repeat from step 3.

    Do I know how to implement this? Fuck no... will I? Eventually...

    Probably hardest part will be the random point generation within the traingle since I really don't know how to do it...but I'll hopefully at the end of this
    program... I may use barycentric coordinates I don't want to go with a circle around the vertices of the triangle and rejection samping since it's O(fucking eternity)
    Do I know what is barycentric coordinates? Nope? Does wikipedia? Yup...will I read it? Maybe...


    and as always it's fucking 4AM since no sane person has ever tried to implement something like this at a reasonable hour... so this file is a template...for now
    and before I forget this program requires -lraylib as you compile and probably -lm for math too but I haven't even fucking include anything so IDK...

    but bright side? this method works with any triangle so I don't need to coin a term to express 'uni-triangles' like the last time     

*/


/* ======================== INCLUDES ==================== */

//libc headers 

#include <math.h>   //To math
#include <stdio.h>
#include <stdlib.h> //I'll probably use an dynamic array to keep track of the points that I have 
#include <time.h>   //to fuel entropy
//External libs
#include <raylib.h>

/* ========================= DEFINES ====================== */

//Setup 
#define WIDTH 1200.0f
#define HEIGHT 900.0f

#define TITLE "Thingyangle:Reloaded"    //Yeah that's a matrix reference

#ifndef FPS
    #define FPS 120     //I won't try to get V-sync in this one so...either implement for yourself or set your own FPS to your monitor's refresh rate
#endif

//Dyanmic shit
#define BUFFER 4096

//Colors


#define SHE_LOVES_PURPLE CLITERAL(Color){68, 0, 90, 255}
#define RED_AF CLITERAL(Color){90, 23, 0, 255}

/* ============================= OBJECTS ===================== */



/* ===================== GLOBAL VARS =========================== */

/* ===================== FUNCTION PROTOTYPES ================== */

void drawVertices(Vector2 vertices[3]);
void drawPoints(Vector2 *points,size_t size);

int setupEnv(void);

double randDouble(int min,int max);

Vector2 updatePos(Vector2 point, Vector2 vertices[3]);
Vector2 barycentricThingy(Vector2 vertices[3]);
Vector2 *realligator(Vector2 *arr, int *currentSize );

//MAIN 
int main(void)
{

    //Setup shit
    if (setupEnv()) {printf("Window did something...Ig...\n") ; return(-53); } 
    srand(time(NULL));


    Vector2 peak = (Vector2){WIDTH/2.0f, (HEIGHT/4.0f)};
    Vector2 vertices[3] = { peak,(Vector2){peak.x - (WIDTH/3.0f), peak.y + (HEIGHT/3.0f)},(Vector2){peak.x + (WIDTH/3.0f), peak.y + (HEIGHT/3.0f)} };
    
    Vector2 *points = (Vector2 *)(malloc(BUFFER*sizeof(Vector2)));
    if (points == NULL) { printf("SBRK said nope!\n"); free(points); return(-1); }
    int currentSize = 0;
    int capacity = BUFFER;

    // Start with a random point inside the triangle
    Vector2 current = barycentricThingy(vertices);

    while (!WindowShouldClose()) {
        
        if (IsKeyPressed(KEY_ESCAPE)) { break; }
        

        for (int i = 0; i < 10; i++) {
            current = updatePos(current, vertices);
            
            if (currentSize >= capacity) {
                points = realligator(points, &capacity);
                if (points == NULL || capacity == -1) {
                    printf("Failed allocation\n");
                    free(points);
                    return(-1);
                }
            }
            points[currentSize] = current;
            currentSize++;
        }


        BeginDrawing();
        ClearBackground(BLACK);
        drawVertices(vertices);
        drawPoints(points,currentSize);
        DrawText(TextFormat("Points: %d", currentSize), 10, 10, 20, SHE_LOVES_PURPLE);
        EndDrawing();
    }


    free(points);
    points = NULL;

    CloseWindow();
    return(0);
}

void drawVertices(Vector2 vertices[3])
{
    for (int i = 0; i < 3; i++) {
        DrawCircleV(vertices[i], 3.0f, SHE_LOVES_PURPLE);
    }
}

void drawPoints(Vector2 *points, size_t size)
{

    
    for (int i = 0; i < size; i++) {
        DrawPixelV(points[i], RED_AF);
    }    
}

int setupEnv(void)
{
    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_WINDOW_TRANSPARENT | FLAG_WINDOW_UNDECORATED);
    InitWindow(WIDTH, HEIGHT, TITLE);
    if(!IsWindowReady()){ return(-1); }
    
    if (FPS < 0 || FPS > 300) {
        SetTargetFPS(240);
    }
    else {
        SetTargetFPS(FPS);
    }
    return(0);
}


double randDouble(int min,int max)
{
    return(((double)rand() / RAND_MAX)*(max-min)+min);
}

Vector2 updatePos(Vector2 point, Vector2 vertices[3])
{
    Vector2 newPoint = { 0 };
    int vertex = rand() % 3;
    newPoint.x = (vertices[vertex].x + point.x)/2;
    newPoint.y = (vertices[vertex].y + point.y)/2;
    
    return(newPoint);
}

Vector2 barycentricThingy(Vector2 vertices[3])
{
    double r1 = randDouble(0, 1);
    double r2 = randDouble(0, 1);
    
    //The barycentric thing formula is P = a*A + b*B + gamma*C for each axis I guess 
    double alpha = 1.0l - sqrt(r1);
    double beta = sqrt(r1) * (1.0-r2);
    double gamma = sqrt(r1)*r2;

    Vector2 randPoint = { 0 };
    
    randPoint.x = alpha*vertices[0].x + beta*vertices[1].x + gamma*vertices[2].x;
    randPoint.y = alpha*vertices[0].y + beta*vertices[1].y + gamma*vertices[2].y;

    return(randPoint);
}


Vector2 *realligator(Vector2 *arr, int *currentSize)        //yeah that's a signature at this point
{
    if(arr == NULL)
    {
        arr = (Vector2 *)(malloc(BUFFER*sizeof(Vector2)));
        if (arr == NULL) { free(arr); return(NULL); }
        
        (*currentSize)+=BUFFER;
        return(arr);
    }
    int newSize = (*currentSize) * 2;
    Vector2 *temp = realloc(arr, newSize*sizeof(Vector2));
    if (temp == NULL) {
        (*currentSize) = -1;
        return(arr);
    }
    arr = temp;
    (*currentSize) = newSize;
    return(arr);
}