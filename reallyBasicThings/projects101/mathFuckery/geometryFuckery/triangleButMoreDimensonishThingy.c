/*

    'Sup? The time's finally arrived and I am leaving this template to start working on the Sierpinski Tetrahedron since I got the basics of 
    cam movement in raylib... the main question is how tf creating a more dimensional triangle  

    This one's gonna be also an recursive one...



    Well...today's not my moody day so we're only trying to get the triangle on the screen... and let the camera orbit around it I guess...
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
    int cam_modes[3] = {CAMERA_PERSPECTIVE, CAMERA_ORBITAL, CAMERA_FREE};
    size_t cam_mode_selector = 0;
    int cam_mode = cam_modes[cam_mode_selector]; 

    cam.position = (Vector3){4.f, 4.f, 4.f};
    cam.target = (Vector3){ 0 };    //it targets the origin of the plane? screen? what the fucking entity called in 3D space IDK...
    cam.up = (Vector3){0.f, 1.0f, 0.f}; //Still no clue what is up besides a rough understanding
    cam.fovy = 120.0f; //Quake-ass fov..
    cam.projection = cam_mode;

    float size = 0.5f;
    //What the fuck is the singular version of vertices? Vertex? 
    //This placement may be way off...I am trying to imagine a 3D shape on a 2D screen and it fucks with my neurons
    Vector3 vertices1 = {size, size, size};
    Vector3 vertices2 = {-size, -size, size};
    Vector3 vertices3 = {-size, size, -size};
    Vector3 vertices4 = {size, -size, -size};


    DisableCursor();

    while (!WindowShouldClose()) {

        if (IsKeyPressed(KEY_ESCAPE)) { break ;}
        if (IsKeyPressed(KEY_SPACE)) { 
            cam_mode_selector++;
            cam_mode = cam_modes[cam_mode_selector % 3];
        } 
        
        UpdateCamera(&cam, cam_mode);
        BeginDrawing();
        ClearBackground(BLACK);
        BeginMode3D(cam);
        //If I haven't fucked up this should work...
        //after compiling...I ,in fact, fucked up
        DrawGrid(50.f, 2.0f);
        DrawTriangle3D(vertices1, vertices2, vertices3, RED);
        DrawTriangle3D(vertices1, vertices3, vertices4, GREEN);
        DrawTriangle3D(vertices1, vertices4, vertices2, BLUE);
        DrawTriangle3D(vertices2, vertices4, vertices3, PURPLE);    
        //Well that's the most cursed shit I've done but funny enough if you look at it beneath the grid with correct angle it looks like CMake logo
        
        EndMode3D();
        EndDrawing();
    }

    EnableCursor();
    CloseWindow();


    return(0);
}


int setUpEnv(void)
{
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(WIDTH, HEIGHT, TITLE);
    if (!IsWindowReady()) { return(-1); }

    return(0);
}
