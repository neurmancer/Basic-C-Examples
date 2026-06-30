/* ==================   INCLUDES   ================  */

#include <stdio.h>
#include <raylib.h>
#include <math.h>

/* =================== DEFINES   ====================  */

#define WIDTH 1200
#define HEIGHT 900 //Yup I love 4:3 

#define FPS 120

/* ========================== YAPPING  ===================== */

            /*
                    What we do today? More math fuckery!!! (Well pong too...but I need change so I started to work on this too)
                    What is Sierpinski triangle?
                        1-It's a recursive pattern that formed by an uni-triangle? is that a thing? yk...the one with 60 angles each and all side lengths are equal...that one
                        
                        Important shit to know to create this:
                            1- Start with a uni-triangle(Yeah...I'll call it that you got the idea)
                            2-Divide it to 4 uni-triangles within the first one and remove the one in the middle

                            That's it!

                            Do I know how to create it? Abso-fucking-litely not but hey...that's the charm B)

                    Thile file requires external lib: Raylib you can install it by pacman -S raylib if you are on Arch and I am pretty sure that other distros have that too
                    just try dnf,apt-get,apt,pkg if you're on Termux idk you'll get her eventually
                    and to compile: cc (or gcc) src.c -o output -lraylib (and -lm if I include math too)

                    If you've seen my other graphic projects you know how I sector things with comment blocks and use camelCase for my own fucntions to reduce confusion with
                    raylib functions (Which are all in PascalCase (as far as I've seen))


                    Never drawn a triangle in raylib before so we're head-diving into raylib header to extract some shit 

                    DrawTriangle(Vector2 v1, Vector2 v2, Vector2 v3, Color color);                                // Draw a color-filled triangle (vertex in counter-clockwise order!)

                    RLAPI void DrawTriangleLines(Vector2 v1, Vector2 v2, Vector2 v3, Color color);        // Draw triangle outline (vertex in counter-clockwise order!)
                    RLAPI void DrawTriangleFan(const Vector2 *points, int pointCount, Color color);       // Draw a triangle fan defined by points (first vertex is the center)
                    RLAPI void DrawTriangleStrip(const Vector2 *points, int pointCount, Color color);     // Draw a triangle strip defined by points

                    those three was what I've found but all of them using Vectors for points...for me this is some computational waste I need to calculate the perfect 
                    eqaul distances from a center... First Idea...with a given radius draw a circle and draw a triangle within the circle where all 3 vertices of the triangle 
                    are on the arc of the said circle...


            */

/* ========== OBJECTS  =====================  */




/* ============== FUNCTION PROTOTYPES  ================  */


/* ============== GLOBAL VARS ===================  */




int main(void)
{

    InitWindow(WIDTH, HEIGHT,"Thingyangle");
    if (!IsWindowReady()) { perror("Windows suck as always\n"); return(-1); }
    SetTargetFPS(FPS);
    
    Vector2 center = {WIDTH/2.0f,HEIGHT/2.0f};
    float radius = 289.17f;
    float angle = 0.0f;         //FUCK WHY THE FUCK I CAN'T MAKE THIS PARALLEL To screen AAAAAAAAAAAAAAA
    
    Vector2 triangleVertices[3] = { 0 };


    for (int i = 0; i < 3;i++) {
        triangleVertices[i].x = center.x + cosf(angle)*radius;
        triangleVertices[i].y = center.y - sinf(angle)*radius;
        angle += 2*PI/3;
    }
    


    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_ESCAPE)) { CloseWindow(); }
        


        BeginDrawing();
        ClearBackground(BLACK);
        DrawTriangle(triangleVertices[0],triangleVertices[1],triangleVertices[2],VIOLET); //Solved it this shit requires CCW (or positive motion between verticies) This shit broke me ngl
        EndDrawing();
    }



    CloseWindow();

    return(0);
}
