/*

        =============== YAPPING ==================

        'Sup? What's today's fuckery? Atari breakout clone duh...I hate working with game logics but here we are...

        So here is the plan...

          1- make shit appear on the screen
          2- Make shit move
          3- make shit move with passion 
        

        6 rows, 12 columns of bricks 
*/



/* ================== INCLUDES ================ */

#include <stdio.h> 
#include <raylib.h>



/* ================= DEFINES ================ */

#define WIDTH 1200
#define HEIGHT 900  //4:3 

#define TITLE "BREAKOUT IG..."

#ifndef FPS
  #define FPS 120 
#endif 

#ifndef VSYNC 
  #define VSYNC 0
#endif 


//Game shit
#define BRICK_COUNT 72


/* ============= OBJECTS ================ */


typedef struct{
  
  Vector2 pos;
  Vector2 size;

  Color color;

  int powerUp;
}Brick;


typedef struct{
  
  Vector2 pos;
  Vector2 vel; 
  Vector2 accel;

  Color color;
}Ball;

typedef struct{
  
  Vector2 pos;
  Vector2 vel;

  Color color;

}Paddle;


/* ================= FUNCTION PROTOTYPES =================== */

void fillBricks(Brick *brick, int brickAmount);

int setup(void);



int main(void)
{
  if(setup()){
    perror("Window got fucked up\n");
    return(-1);
  }

  Brick bricks[BRICK_COUNT]; 


  while(!WindowShouldClose())
  {
  
    if (IsKeyPressed(KEY_ESCAPE)) { break; }




    BeginDrawing();
    ClearBackground(BLACK);
    EndDrawing();
  
  }


  return(0);
}



void fillBricks(Brick *bricks, int brickAmount)
{
  






}

int setup(void)
{


  if (VSYNC)
  {
    SetConfigFlags(FLAG_VSYNC_HINT);
  }
  

  InitWindow(WIDTH, HEIGHT, TITLE);
  
  if (!VSYNC && FPS >= 0 && FPS <= 300) {
    SetTargetFPS(FPS);
  }
  else{
    SetTargetFPS(120);
  }

  if(!IsWindowReady()){ return(-53); }

  return(0);
}
















