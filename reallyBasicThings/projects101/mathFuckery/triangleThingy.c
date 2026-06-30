/* ==================   INCLUDES   ================  */

#include <stdio.h>
#include <raylib.h>


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

            */

/* ========== OBJECTS  =====================  */




/* ============== FUNCTION PROTOTYPES  ================  */


/* ============== GLOBAL VARS ===================  */




int main(void)
{

    InitWindow(WIDTH, HEIGHT,"Thingyangle");
    if (!IsWindowReady()) { perror("Windows suck as always\n"); return(-1); }
    SetTargetFPS(FPS);
    
    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_ESCAPE)) { CloseWindow(); }
        
        
        BeginDrawing();
        EndDrawing();
    }



    CloseWindow();

    return(0);
}