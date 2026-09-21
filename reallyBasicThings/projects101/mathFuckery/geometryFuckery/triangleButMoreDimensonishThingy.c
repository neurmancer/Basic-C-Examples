/*

    'Sup? The time's finally arrived and I am leaving this template to start working on the Sierpinski Tetrahedron since I got the basics of 
    cam movement in raylib... the main question is how tf creating a more dimensional triangle  

    This one's gonna be also an recursive one...



    Well...today's not my moody day so we're only trying to get the triangle on the screen... and let the camera orbit around it I guess... well we have the thing...
    but I heard something called mash and found those and I'll be reading those before proceeding further here is the sources:

    arXiv: https://arxiv.org/abs/2504.09149,
    arXiv: https://arxiv.org/pdf/2504.09149 (THIS ONE IS A FUCKING 11 PAGES OF MATH WTF? A WHOLE ASS PDF FOR A TRINAGLE? FUUUUUUUCK THERE GOES MY SLEEP SCHEDULE)

    well...those 2 articles were unnecessary I typed 'mesh' as 'mash' and learned
    Masked Anchored SpHerical Distances for 3D Shape Representation and Generation
    by mistake...so wtf is mesh? 
*/



/* ========================= INCLUDES ==================== */

#include <stdbool.h>
#include <stdio.h>
//-lm -lraylib required to link libm and raylib
#include <raylib.h>
#include <raymath.h>    //Yup more math headers...
#include <math.h>
#include <stdlib.h>


/* ========================== DEFINES ===================== */

#define WIDTH 1200
#define HEIGHT 900

#define FPS 120
#define TITLE "Thingyangle: Revolutions"    //Yup matrix thing continues...

#define MAX_DEPTH 6 //if given more it fucks up (raylib accepts indices as shorts...it can't hold more than that...)

#define RED_AF CLITERAL(Color){53,0,13,255}
#define DA_BLUE CLITERAL(Color){1,12,122,255}
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
    float *vertices;
    unsigned short *indices;
    int vertexIndex;
    unsigned int indexIndex;     //index has index...recursion already started...

}TetrahedronMesh;   //That's gonna be a spelling nightmare for the rest of the file



/* ==================== FUNCTION PROTOTYPES ================== */
void meshThingy(TetrahedronMesh *builder, Vector3 p1,Vector3 p2,Vector3 p3);
void genRecursion(TetrahedronMesh *builder, Vector3 top, Vector3 left, Vector3 right, Vector3 back, int depth);
int setUpEnv(void);

Mesh makeTheFuckingTriangle(int depth);


/* ========================== MAIN ================= */

int main(void)
{
    
    if (setUpEnv()) { perror("Window is not emotionally ready "); return(-53); }

    int cam_modes[2] = {CAMERA_ORBITAL, CAMERA_FREE};
    int cam_mode = 0;
    unsigned int depth = 1;
    
    Mesh triangle =makeTheFuckingTriangle(depth);

    Model model = LoadModelFromMesh(triangle);  //Blind-faith to raylib tbh...

    Camera3D cam = { 0 };
    cam.position = (Vector3){0.f,0.f,50.f};
    cam.target = (Vector3){0.f,0.f,0.f};    
    cam.up = (Vector3){0.f,1.f,0.f};
    cam.fovy = 60.f;    //no more quake-ass FOV...
    cam.projection = CAMERA_PERSPECTIVE;

    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].color = DA_BLUE;
    int wires = 0;

    DisableCursor();

    while (!WindowShouldClose()) {

        if (IsKeyPressed(KEY_ESCAPE)) { break ;}
        if (IsKeyPressed(KEY_C)) { cam_mode = cam_mode ? 0 : 1;}
        if (IsKeyPressed(KEY_F)) { wires = wires ? 0 : 1;}

        if (IsKeyPressed(KEY_E))
        {
            if (depth < MAX_DEPTH)
            {
                depth++;

                UnloadModel(model);

                Mesh newMesh = makeTheFuckingTriangle(depth);
                model = LoadModelFromMesh(newMesh);

                model.materials[0].maps[MATERIAL_MAP_DIFFUSE].color = DA_BLUE;
            }
        }

        if (IsKeyPressed(KEY_Q) && depth > 0)
        {
            depth--;
            UnloadModel(model);
            Mesh newMesh = makeTheFuckingTriangle(depth);
            model = LoadModelFromMesh(newMesh);
            model.materials[0].maps[MATERIAL_MAP_DIFFUSE].color = DA_BLUE;
        }


        UpdateCamera(&cam, cam_modes[cam_mode]);
        
        BeginDrawing();
        ClearBackground(RED_AF);
        
        BeginMode3D(cam);

        DrawModel(model, (Vector3){0,0,0}, 1.0f, WHITE);
        if (wires) {
            DrawModelWires(model, (Vector3){0,0,0}, 1.f, BLACK);
        }

        EndMode3D();
        
        EndDrawing();
    }

    EnableCursor();
    UnloadModel(model); //This free()'s the arrays? 
    CloseWindow();


    return(0);
}


int setUpEnv(void)
{
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(WIDTH, HEIGHT, TITLE);
    if (!IsWindowReady()) { return(-1); }

    SetTargetFPS(FPS);
    return(0);
}



void meshThingy(TetrahedronMesh *builder, Vector3 p1,Vector3 p2,Vector3 p3)
{
    int v = builder->vertexIndex;

    //1st corner? vertex? well...my English gave up on jargon at this point...
    builder->vertices[v] = p1.x;
    builder->vertices[v+1] = p1.y;
    builder->vertices[v+2] = p1.z;

    //2nd of the same thing
    builder->vertices[v+3] = p2.x;
    builder->vertices[v+4] = p2.y;
    builder->vertices[v+5] = p2.z;

    //3rd one
    builder->vertices[v+6] = p3.x;
    builder->vertices[v+7] = p3.y;
    builder->vertices[v+8] = p3.z;

    int idx = builder->indexIndex;
    int vOffset = v / 3;

    //and here comes the math connecting math...
     
    builder->indices[idx] = vOffset;
    builder->indices[idx+1] = vOffset+1;
    builder->indices[idx+2] = vOffset+2;

    builder->vertexIndex += 9;
    builder->indexIndex += 3;
    //That should work...
}


Mesh makeTheFuckingTriangle(int depth)
{
    Mesh mesh = { 0 };
    int totalTriangles = 4*(int)pow(4,depth);   //Why no pow(4, depth+1) and 4* pow(4,depth)? 'cuz I love wasting cpu cycles

    mesh.triangleCount = totalTriangles;
    mesh.vertexCount = totalTriangles * 3;

    mesh.vertices = (float *)malloc(mesh.vertexCount*3*sizeof(float));
    if (mesh.vertices == NULL) { return((Mesh){ 0 }); }
    mesh.indices = (unsigned short*)malloc(mesh.vertexCount * sizeof(unsigned short));
    if (mesh.indices == NULL) {
        free(mesh.vertices);
        return((Mesh){ 0 });
    }


    
    float s = 15.f;

    Vector3 top   = { 0.0f,  s,  0.0f };
    Vector3 left  = {-s, -s/2.0f,  s * 0.866f};   
    Vector3 right = { s, -s/2.0f,  s * 0.866f};
    Vector3 back  = { 0.0f, -s/2.0f, -s * 1.732f}; 
    
    TetrahedronMesh tMesh = {mesh.vertices, mesh.indices, 0, 0};

    genRecursion(&tMesh, top, left, right, back, depth);

    UploadMesh(&mesh, false);       //Wtf dynamic upload?

    return(mesh);
}



void genRecursion(TetrahedronMesh *builder, Vector3 top, Vector3 left, Vector3 right, Vector3 back, int depth)
{

    if (depth == 0) {
        //First depth(thx...mr obvious)
        meshThingy(builder, top, left, right);
        meshThingy(builder, top, right, back);
        meshThingy(builder, top, back, left);
        meshThingy(builder, left, back, right);
        //This should be correct...
        return;
    }

    Vector3 mTopLeft = Vector3Scale(Vector3Add(top, left),0.5);
    Vector3 mTopRight = Vector3Scale(Vector3Add(top, right),0.5);
    Vector3 mTopBack = Vector3Scale(Vector3Add(top, back),0.5);
    Vector3 mLeftRight = Vector3Scale(Vector3Add(left, right),0.5);
    Vector3 mRightBack =Vector3Scale(Vector3Add(right, back),0.5);
    Vector3 mBackLeft = Vector3Scale(Vector3Add(back, left),0.5);

    //Now...this should work?
    genRecursion(builder, top, mTopLeft, mTopRight, mTopBack, depth - 1);
    genRecursion(builder, mTopLeft, left, mLeftRight, mBackLeft, depth - 1);
    genRecursion(builder, mTopRight, mLeftRight, right, mRightBack, depth - 1);
    genRecursion(builder, mTopBack, mBackLeft, mRightBack, back, depth - 1);
}
