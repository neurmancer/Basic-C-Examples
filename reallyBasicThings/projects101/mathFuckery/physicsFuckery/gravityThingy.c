/*
    Sup? You know the tea if you've seen any other file...welcome to yet another Physics fuckery conjured by my sleep-deprivation 
    What are we building today? UNIVERSE! nah...not there yet but I thought about using random hardware noise for cosmic background radiation tho
    I am not gonna lie... 
    but today's physics fuckery is N-Body simulation 
    (For those not in the know: this is simulating the gravitational interaction of N particles (stars, planets, dark matter) 
    where every particle attracts every other particle.) from a Wiki article recommended to me here's the link for nerds -> https://en.wikipedia.org/wiki/N-body_simulation

    This is gonna be the last 'simulation' before I dive back into CLI tools or low-level stuff for a while I guess
    This project requires -lraylib as you compile since I am using raylib duh and I'll curb the profanity in this file...sometimes I get hyped and code
    Sometimes I just code to shut voices, world, that's one of the Category 2 projects...
    Yk when you build something to prove yourself that you are not an imposter 
    

    Side track: The wikipedia page has Dark matter simulation too...so no promises for now...unless?

        Limitations: I'll be using Newtonian mechanics so...accuracy is an unknown to me 'till I finish and evaluate accuracy 
        and probably calculation efficiency will be O(n^2) at least for my initial draft  
*/

/* ============ INCLUDES ============ */

#include <raylib.h>
#include <stdlib.h>
#include <time.h>

/*=============== DEFINES ============== */

#define WIDTH 1200
#define HEIGHT 900

#define COLOR_ARR_SIZE 24

#ifndef VSYNC 
    #define VSYNC 0 //If you want VSYNC type -DVSYNC=1 as you compile
#endif

#ifndef FPS
    #define FPS 120     //This time I'll make it configurable as you compile: usage: -DFPS=FPS_YOU_WANT (Hard capped at 300fps and 0 for no limit)
#endif

/*================= OBJECTS =============== */

/*

===== REFERENCE =====
typedef struct Vector2 {
    float x;                // Vector x component
    float y;                // Vector y component
} Vector2;

raylib uses float so I need accuracy source: raylib.h
*/
typedef struct{
    double x,y; //
}Vector2d;

typedef struct{

    double r;       //Radius
    double mass;
    int status;     // activity status of the body
    
    Color color;    

    Vector2d force;
    
    //Seperated by derivatives (force is not a derivate if any of this)
    Vector2d position;
    Vector2d velocity;
    Vector2d accel;
    
}Particle;   //Consider renaming it body if needed?


typedef struct{
    double minRadius;
    double maxRadius;
    
    double dt;  // Δtime
    double initVelocity;

}Config;


/* ============= GLOBALS ============= */


/* ============= FUNCTION PROTOTYPES ============= */

void generateParticle(Particle *particle, Config *config);    //I wanna call it particle instead of body regardless of the terminology
void setParticles(Particle *particle, int particleAmount, Config *config);

int setupEnv(void);     //Raylib Window manager wrapper 

double randDouble(double min, double max);


Color randColor();

/* ============= MAIN ============= */


int main(void)
{
    srand(time(NULL));

    if (setupEnv()) {
        return(-1); //Change error codes as you go
    }

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_ESCAPE)) { CloseWindow(); }
    
        //Drawing
        BeginDrawing();
        ClearBackground(BLACK);
        DrawFPS(10, 10);    
        EndDrawing();

    }

    return(0);
}


/* ============ FUNCTION BODIES ============ */

void generateParticle(Particle *particle, Config *config)
{
    
    particle->r = randDouble(config->minRadius, config->maxRadius);
    particle->color = randColor();
    particle->mass = randDouble((particle->r*particle->r),(particle->r*particle->r)*15);        //Density between m/(r^2) - m/[(r^2)*15]
    
    particle->position.x = randDouble(0, WIDTH);
    particle->position.y = randDouble(0, HEIGHT);
    
    particle->velocity.x = randDouble(-(config->initVelocity),config->initVelocity); // Minus at the beginning since screen index goes down as the number gets bigger
    particle->velocity.y = randDouble(-(config->initVelocity),config->initVelocity);
    
    particle->accel.x = 0.0;
    particle->accel.y = 0.0;

    particle->force.x = 0.0;
    particle->force.y = 0.0;

    particle->status = 1;
    
}


void setParticles(Particle *particle, int particleAmount, Config *config)
{
    for (int i = 0;i < particleAmount; i++) {
        generateParticle(&particle[i],config);
    }

}


int setupEnv(void)
{
    if (VSYNC) {
        SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT);
    }
    else {
        SetConfigFlags(FLAG_MSAA_4X_HINT);
    }

    InitWindow(WIDTH, HEIGHT, "Fancy Balls Attracting Each Other");
    if (!IsWindowReady()) {
        return(-1);
    }
    //V-sync handles fps in case of being 1 
    if (!VSYNC) {

        if (FPS > 300 || FPS < 0) {
            int fps = 300;
            SetTargetFPS(fps);
        }
        else { SetTargetFPS(FPS); }
    }

    return(0);
}

double randDouble(double min, double max)
{
    double value = (((double)rand() / RAND_MAX)*(max-min))+min;
     
    return(value);
}



Color randColor(void)
{
    Color colors[COLOR_ARR_SIZE] = { 0 };
    return(colors[rand()%COLOR_ARR_SIZE]);
}
