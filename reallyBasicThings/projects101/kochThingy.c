/*  Includes    */

#include <raylib.h>
#include <stdio.h>

/*  Defines     */
#define WIDTH 600.0f
#define HEIGHT 400.0f
#define FPS 60


/*              Sup? You know the tea...Got bored, thought something now I must implement...The usual fuck around and find out thing        

                This is here as a template for now...



*/


int main(void)
{

    InitWindow(WIDTH, HEIGHT, "Koch Thingy");
    if (!IsWindowReady()) {perror("Something bad occured\n"); return(-1);}
    SetTargetFPS(FPS);

    while (!WindowShouldClose()) {
        
        if(IsKeyPressed(KEY_ESCAPE)){CloseWindow();}



        BeginDrawing();
        ClearBackground(BLACK);
        DrawRectangle(5, 5, 1, 1, RED); //This is a totally unrelated test 
        EndDrawing();
    }

    





    return(0);
}