/*

    'Sup? This is a qucikie to get a grasp of 3D cam movement of raylib so less commentary more coding for me (this file would be 100LoC at max)

    So...I am experimenting with camera movements (2D and 3D) for next triangle fuckery...that's it!

    requires -lm for lib math even tough I haven't used it and -lraylib for raylib 
*/


#include <raylib.h>


#define WIDTH 1200
#define HEIGHT 900

#define FPS 120
#define TITLE "Experiment"

int setupEnv(void);

int main(void)
{

    //Well... 2D was fine since --------- meant x and | meant y but when z axis enters the arena...wtf happens? - x? / z and | y? (yeah I am trying to create the planes with ASCII chars)
    //Poor man's desmos...

    Vector3 pos_cam = { 10, 0, 0};
    Vector3 pos_obj = {0, 0, 0};
    Vector3 up_vec = {0, 0, 1};

    float fov_y = 90;  
    Camera3D cam = {pos_cam, pos_obj, up_vec, fov_y, CAMERA_PERSPECTIVE};
    Vector3  cube_pos = { 0 };  //let's see where the origin is first I guess...


    if (setupEnv()) { return(-53); }

    //Event loop
    while (!WindowShouldClose()) {
        //Well...rotating cube it is then...
    
        UpdateCamera(&cam, CAMERA_ORBITAL);
        BeginDrawing();
        ClearBackground(BLACK);

        BeginMode3D(cam);
        DrawCubeWiresV(cube_pos, (Vector3){2.f, 2.f, 2.f}, PURPLE);
        DrawCube(cube_pos, 2.f, 2.f, 2.f, VIOLET);

        EndMode3D();
        EndDrawing();

    }


    return(0);
}

int setupEnv(void)
{
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(WIDTH, HEIGHT, TITLE);
    if (!IsWindowReady()) { return(1); }

    SetTargetFPS(FPS);
    return(0);
}