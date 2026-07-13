

/*
        Sup? this file gonna be something but not today... but you know what they say, Starting means you're half way there to finish

        What retro fuckery is this? 
            This program (hopefully when finished) gonna apply a CRT (or VHS (or both with a toggle key)) filter to your current display. That's the sole purpose of this app
            So I dunno what to include what to do or not...Only thing I know is that I know nothing...nah just fucking with ya, only think I know is I need raylib to start
        I won't go over why this include,define etc. banners exists you know if you've seen my other raylib projects etc



        Lol I made a blue-blocker for now...in the future I'll add 

            -Vignette 
            - RBG mask 
            - Flickers/Hickups
            - Slight curved distortion (since yk... old monitors weren't flat)

        but current version is good to work at night so I made a tool for myself (which prbably KDE already has(good thing I use dwm))
*/





/* =============== INCLUDES ===============  */

#include <raylib.h>



/* ================= DEFINES ====================  */

#define WIDTH 1200
#define HEIGHT 900

#define FPS 120     //Does that fuck with the layer beneath? the actual screen yk...I gotta match this with monitor's refresh rate probably



int main(void)
{
    // 1. Enable the transparent window flag BEFORE InitWindow
    SetConfigFlags(FLAG_WINDOW_TRANSPARENT | FLAG_WINDOW_UNDECORATED | FLAG_WINDOW_MOUSE_PASSTHROUGH); //Digged flags for stupid shit
    SetTargetFPS(FPS);
    InitWindow(WIDTH, HEIGHT, "CRT THINGY");
    ToggleBorderlessWindowed();
    
    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_ESCAPE)) { WindowShouldClose(); }

        BeginDrawing();
        ClearBackground((Color){22, 16, 1, 2});
        EndDrawing();
    }



    return(0);
}