/*

    'Sup? The time's finally arrived and I am leaving this template to start working on the Sierpinski Tetrahedron since I got the basics of 
    cam movement in raylib... the main question is how tf creating a more dimensional triangle  

    This one's gonna be also an recursive one...



    Well...today's not my moody day so we're only trying to get the triangle on the screen... and let the camera orbit around it I guess... well we have the thing...
    but I heard something called mash and found those and I'll be reading those before proceeding further here is the sources:

    arXiv: https://arxiv.org/abs/2504.09149,
    arXiv: https://arxiv.org/pdf/2504.09149 (THIS ONE IS A FUCKING 11 PAGES OF MATH WTF? A WHOLE ASS PDF FOR A TRINAGLE? FUUUUUUUCK THERE GOES MY SLEEP SCHEDULE)
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
/*
    So..wtf is a tetrahedron? A triangular prism?

    Wikipedia says:

    In geometry, a tetrahedron (pl.: tetrahedra or tetrahedrons), also known as a triangular pyramid, (aren't all pyramids 'triangular?' anyways? have you seen a rectangluar pyramid?)
    is a polyhedron composed of four triangular faces, six straight edges, and four vertices. 
    The tetrahedron is the simplest of all the ordinary convex polyhedra.[1]

    A tetrahedron. The tetrahedron is the three-dimensional case of the more general concept of a Euclidean simplex, and may thus also be called a 3-simplex.

    The tetrahedron is one kind of pyramid, which is a polyhedron with a flat polygon base and triangular faces connecting the base to a common point.
    In the case of a tetrahedron, the base is a triangle (any of the four faces can be considered the base), 
    so a tetrahedron is also known as a "triangular pyramid".
        
    Like all convex polyhedra (yeah silly me for not knowing general convex polyhedra structure...WTF IS IT?), a tetrahedron can be folded from a single sheet of paper. It has two such nets.


*/


typedef struct{
    Vector3 v1;
    Vector3 v2;
    Vector3 v3;
    Vector3 v4;
    
}Tetrahedron;   //That's gonna be a spelling nightmare for the rest of the file



/* ==================== FUNCTION PROTOTYPES ================== */
int setUpEnv(void);


/* ========================== MAIN ================= */

int main(void)
{
    if (setUpEnv()) { perror("Window is not emotionally ready "); return(-53); }


    Camera3D cam = { 0 };
    int cam_modes[2] = {CAMERA_ORBITAL, CAMERA_FREE};
    size_t cam_mode_selector = 0;
    int cam_mode = cam_modes[cam_mode_selector]; 

    cam.position = (Vector3){4.f, 4.f, 4.f};
    cam.target = (Vector3){ 0 };    //it targets the origin of the plane? screen? what the fucking entity called in 3D space IDK...
    cam.up = (Vector3){0.f, 1.0f, 0.f}; //Still no clue what is up besides a rough understanding
    cam.fovy = 120.0f; //Quake-ass fov.. (and what happens if I give it 360? Does it look like as if it's on an event horizon of a Black Hole?)
    cam.projection = CAMERA_PERSPECTIVE;

    float size = 0.5f;
    //What the fuck is the singular version of vertices? Vertex? 
    //This placement may be way off...I am trying to imagine a 3D shape on a 2D screen and it fucks with my neurons
    Vector3 vertices1 = {size, size, size};
    Vector3 vertices2 = {-size, -size, size};
    Vector3 vertices3 = {-size, size, -size};
    Vector3 vertices4 = {size, -size, -size};
    Tetrahedron t = {vertices1, vertices2,  vertices3, vertices4};


    DisableCursor();

    while (!WindowShouldClose()) {

        if (IsKeyPressed(KEY_ESCAPE)) { break ;}
        if (IsKeyPressed(KEY_SPACE)) { 
            cam_mode_selector++;
            cam_mode = cam_modes[cam_mode_selector % 2];
        } 

        UpdateCamera(&cam, cam_mode);
        BeginDrawing();
        ClearBackground(BLACK);
        BeginMode3D(cam);
        //If I haven't fucked up this should work...
        //after compiling...I ,in fact, fucked up
        DrawGrid(50.f, 2.0f);
        DrawTriangle3D(t.v1, t.v2, t.v3, RED);
        DrawTriangle3D(t.v1, t.v3, t.v4, GREEN);
        DrawTriangle3D(t.v1, t.v4, t.v2, BLUE);
        DrawTriangle3D(t.v2, t.v4, t.v3, PURPLE);    
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
