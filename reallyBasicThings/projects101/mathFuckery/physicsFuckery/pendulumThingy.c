/*
            =============== USUAL NEURO YAPPING =====================

            sup? I really stop saying sup everytime I open vim but anyways... What's today's fuckery? A pendulum pendlum? how tf u spell it. 
            A ball attached to a string it is... Do I Know anything? nope at least implementation wise ofc I do fucking know what a ball and string is 
            This is here as a template (btw I never delete that line even after finishing the project lulz)


            The OG grahpical app gang gonna be here probably -lraylib, -lm (tho...I really make a Makefile for this type shit but not now)


            My original idea is using a frictionless pivot and letting the ball go crazy like a crackhead on meth 
            rope p1 will be a constant on the pivot, p2 will follow the ball's center or center-radius haven't decided yet...

            Here's its wiki page: https://en.wikipedia.org/wiki/Pendulum and maybe I may add a pendulum angle to sin wave visualizer at the end

            and I don't fucking need kinetic to potential energy transformations for this right? Like wtf? or do I 

            I guess I'll go with Euler method (Shoutout to all of my dead nerds...thx for writing those down)
            it's roughly acceleartion = -1* gravity/Length or rope * sin(theta) 
*/


/* ==================== INCLUDES =========================== */

//Standard Libs
#include <stdio.h>

//External libs 
#include <raylib.h> 
#include <math.h>



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
#define B_RADIUS 60.0f 
#define PIVOT_RADIUS 15.0f

#define LINE_THICKNESS 5.20f
#define LINE_LENGTH 400.0f

//Physics 

#ifndef G 
  #define G 50.0f
#endif

//UI Choices 
#define NEAT_RED CLITERAL(Color){58,4,7,255}
#define I_HATE_OLIVES CLITERAL(Color){34,58,4,255}
#define CYANISH CLITERAL(Color){4,58,55,255}
#define SMOKE_ON_THE_WATER CLITERAL(Color){24,4,58,255} //'Cuz it's Deep Purple



/* ===================== OBJECTS =============== */

typedef struct{
  
  float radius;
  
  Vector2 center;
  Color color;

}Ball; //raylib does not have a circle struct so I'll make my own

typedef struct{

  Vector2 p1; //Point 1 
  Vector2 p2; //Point 2 

  float length;
  float thickness;
  Color color;

}Line;  //Neither has it a Line


typedef struct{
  
  Ball ball;
  Line string;    //C doesn't have a native 'string' type rawr xD (yeah I just typed rawr xD unironically)

}Pendulum;

typedef struct{
  
  float angle;
  
  float  angularAccel;  //acceleration 
  float angularVel;    //Velocity 

}Physics;
/* ============== GLOBAL VARS ==================== */


typedef struct{
  Pendulum pend;
  Ball pivot;
  Physics engine; 
}Objects ;




//For some fucking reason my tabs aren't what they used to be in this file
/* =================== FUNCTION PROTOTYPES ============= */

void drawObjects(Objects *obj);
void updatePendulum(Objects *obj, float dt);


int setupEnv(void);


int main(void)
{

  if (setupEnv()) {
    printf("Blame raylib bruh\n");
    return(-53);
  }
  const Ball pivot = {PIVOT_RADIUS, (Vector2){WIDTH/2,HEIGHT/4}, CYANISH};

  Pendulum pendulum = {
    .ball.color= NEAT_RED,
    .ball.radius= B_RADIUS,
    .string.color= I_HATE_OLIVES,
  }; 

  pendulum.string.p1 = pivot.center;
  pendulum.string.thickness = LINE_THICKNESS;

  //------------Testing era------------//

  Physics engine = { 0 }; 
  Objects obj = {pendulum, pivot, engine};
  obj.engine.angle = PI/3;
  obj.pend.string.length = LINE_LENGTH;

  obj.pend.ball.center = obj.pend.string.p2;


  //------------Testing era------------//

  float dT = 0.0f;
  Font defaultFont = GetFontDefault();
  while (!WindowShouldClose()) {
    if (IsKeyPressed(KEY_ESCAPE)) { break; }
  
    dT = GetFrameTime();
    for (int i = 0;i < 10; i++) {
      updatePendulum(&obj, dT/10);
  
    }
    
    //Drawing shit
    BeginDrawing();
    ClearBackground(SMOKE_ON_THE_WATER);
    DrawTextEx(defaultFont, "My Projects are getting worse everyday", (Vector2){20,20}, 25.0f, 2.0f, GRAY);
    drawObjects(&obj);
    EndDrawing();

  }


  CloseWindow();
  
  return(0);
}


//Rendering objects
void drawObjects(Objects *obj)
{
  //Line
  DrawLineEx(obj->pend.string.p1,obj->pend.string.p2,obj->pend.string.thickness,obj->pend.string.color);
  //Pivot
  DrawCircleV(obj->pivot.center, obj->pivot.radius, obj->pivot.color);
  DrawCircleV(obj->pend.ball.center,obj->pend.ball.radius,obj->pend.ball.color);
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



//Physics bitch!

void updatePendulum(Objects *obj,float dt)
{
  if (obj->pend.string.length <= 0) { return; /*Fuck you mean negative length?*/ }

  obj->engine.angularAccel = -(G / obj->pend.string.length)*sinf(obj->engine.angle);
  obj->engine.angularVel += obj->engine.angularAccel*dt; 
  obj->engine.angle += obj->engine.angularVel*dt;

  obj->pend.string.p2.x = sinf(obj->engine.angle) * obj->pend.string.length + obj->pend.string.p1.x;
  obj->pend.string.p2.y = cosf(obj->engine.angle) * obj->pend.string.length + obj->pend.string.p1.y;

  obj->pend.ball.center = obj->pend.string.p2;

}







