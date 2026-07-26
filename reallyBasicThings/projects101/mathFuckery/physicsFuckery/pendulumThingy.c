/*
            =============== USUAL NEURO YAPPING =====================

            sup? I really stop saying sup everytime I open vim but anyways... What's today's fuckery? A pendulum pendlum? how tf u spell it. 
            A ball attached to a string it is... Do I Know anything? nope at least implementation wise ofc I do fucking know what a ball and string is 
            This is here as a template (btw I never delete that line even after finishing the project lulz)


            The OG grahpical app gang gonna be here probably -lraylib, -lm (tho...I really make a Makefile for this type shit but not now)


            My original idea is using a frictionless pivot and letting the ball go crazy like a crackhead on meth 
            rope p1 will be a constant on the pivot, p2 will follow the ball's center or center-radius haven't decided yet...

            Here's its wiki page: https://en.wikipedia.org/wiki/Pendulum and maybe I may add a pendulum angle to sin wave visualizer at the end

*/


/* ==================== INCLUDES =========================== */

//Standard Libs
#include <stdio.h>

//External libs 
#include <raylib.h> 



/* ======================== DEFINES ======================== */

//Initilize 
#define WIDTH 1200.0f
#define HEIGHT 900.0f

#define TITLE "String and Ball Thingy"

//Overridible
#ifndef FPS
  #define FPS 120
#endif 

#ifndef VSYNC
  #define VSYNC 0
#endif

//Object props
#define B_RADIUS 15.0f 
#define PIVOT_RADIUS 5.0f

/* ===================== OBJECTS =============== */

typedef struct{
  
  float radius;
  
  Vector2 center;
  Color color;

}Ball; //raylib does not have a circle struct so I'll make my own

typedef struct{

  Vector2 p1; //Point 1 
  Vector2 p2; //Point 2 

  float thickness;
  Color color;

}Line;  //Neither has it a Line


typedef struct{
  
  Ball ball;
  Line string;    //C doesn't have a native 'string' type rawr xD (yeah I just typed rawr xD unironically)

}Pendulum;


/* ============== GLOBAL VARS ==================== */



//For some fucking reason my tabs aren't what they used to be in this file
/* =================== FUNCTION PROTOTYPES ============= */

int setupEnv(void);


int main(void)
{

  if (setupEnv()) {
    printf("Blame raylib bruh\n");
    return(-53);
  }
  const Ball pivot = {PIVOT_RADIUS, (Vector2){WIDTH/2,HEIGHT/4}, VIOLET};

  Pendulum pendulum = {.ball.color=WHITE, .ball.radius=B_RADIUS}; 
  pendulum.ball.center = (Vector2){2*(WIDTH/3),(HEIGHT/2)};
  


  while (!WindowShouldClose()) {
    if (IsKeyPressed(KEY_ESCAPE)) { break; }
  
    //Drawing shit
    BeginDrawing();
    ClearBackground(BLACK);
    DrawCircleV(pivot.center, pivot.radius, pivot.color);
    EndDrawing();
  
  }


  CloseWindow();
  
  return(0);
}



int setupEnv(void)
{
  if (VSYNC) {
    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT);
  } else {
    SetConfigFlags(FLAG_MSAA_4X_HINT);
  }

  InitWindow(WIDTH, HEIGHT, TITLE);
  if (!IsWindowReady()) {
    return(-1);
  }

  if (!VSYNC) {
      if (FPS > 300 || FPS < 0) {
        SetTargetFPS(300);
      }
      else {
        SetTargetFPS(FPS);
      }
  }

  return(0);
}











