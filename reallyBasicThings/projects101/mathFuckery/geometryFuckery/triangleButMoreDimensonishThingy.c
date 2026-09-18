/*

    'Sup? The time's finally arrived and I am leaving this template to start working on the Sierpinski Tetrahedron since I got the basics of 
    cam movement in raylib... the main question is how tf creating a more dimensional triangle  

    This one's gonna be also an recursive one...


*/



/* ========================= INCLUDES ==================== */

#include <stdio.h>
//-lm -lraylib required to link libm and raylib
#include <raylib.h>
#include <math.h>


/* ========================== DEFINES ===================== */

#define WIDTH 1200
#define HEIGHT 900

#define FPS 120
#define TITLE "Thingyangle: Revolutions"    //Yup matrix thing continues...


/* ============================ OBJECTS ====================== */



/* ==================== FUNCTION PROTOTYPES ================== */
int setUpEnv(void);


/* ========================== MAIN ================= */

int main(void)
{
    if (setUpEnv()) { perror("Window is not emotionally ready "); return(-53); }


    Camera3D cam = { 0 };
    
    
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        EndDrawing();
    }


    return(0);
}


int setUpEnv(void)
{
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(WIDTH, HEIGHT, TITLE);
    if (!IsWindowReady()) { return(-1); }

    return(0);
}
