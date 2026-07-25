/*
    Sup? You know the tea if you've seen any other file...welcome to yet another Physics fuckery conjured by my sleep-deprivation 
    What are we building today? UNIVERSE! nah...not there yet but I thought about using random hardware noise for cosmic background radiation tho
    I am not gonna lie... 
    but today's physics fuckery is N-Body simulation 
    (For those not in the know: this is simulating the gravitational interaction of N particles (stars, planets, dark matter) 
    where every particle attracts every other particle.) from a Wiki article recommended to me here's the link for nerds -> https://en.wikipedia.org/wiki/N-body_simulation

    This is gonna be the last 'simulation' before I dive back into CLI tools or low-level stuff for a while I guess
    This project requires -lraylib and -lm(link math) as you compile since I am using raylib duh and I'll curb the profanity in this file...sometimes I get hyped and code
    Sometimes I just code to shut voices, world, that's one of the Category 2 projects...
    Yk when you build something to prove yourself that you are not an imposter 

    Side track: The wikipedia page has Dark matter simulation too...so no promises for now...unless?

        Limitations: I'll be using Newtonian mechanics so...accuracy is an unknown to me 'till I finish and evaluate accuracy 
        and probably calculation efficiency will be O(n^2) at least for my initial draft  


        and while we're on this... I lowkey wanna merge this with c*t effect attempt... it would look beautiful
*/

/* ============ INCLUDES ============ */

#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

/*=============== DEFINES ============== */

//Helper defines
#define WIDTH 1200
#define HEIGHT 900

#define COLOR_ARR_SIZE 24
#define LAST_POS_BUFFER 10 

//Config defines
#ifndef VSYNC 
    #define VSYNC 0 //If you want VSYNC type -DVSYNC=1 as you compile
#endif

#ifndef FPS
    #define FPS 120     //This time I'll make it configurable as you compile: usage: -DFPS=FPS_YOU_WANT (Hard capped at 300fps and 0 for no limit)
#endif

//Phyiscal constant
#define G (9.8)   //For test purpose (earth's g) real capital G's value is approximately 6.6743×10^-11 can double hold that? I'll check
#define SOFTNESS (13.53)

//Colors

#define SKY_BLUE        CLITERAL(Color){  79, 195, 247, 255 }  // #4FC3F7
#define AZURE           CLITERAL(Color){  41, 182, 246, 255 }  // #29B6F6
#define ELECTRIC_CYAN   CLITERAL(Color){   0, 229, 255, 255 }  // #00E5FF
#define TURQUOISE       CLITERAL(Color){  38, 198, 218, 255 }  // #26C6DA
#define NEON_GREEN      CLITERAL(Color){   0, 230, 118, 255 }  // #00E676
#define EMERALD         CLITERAL(Color){ 102, 187, 106, 255 }  // #66BB6A
#define LIME_GREEN      CLITERAL(Color){ 156, 204, 101, 255 }  // #9CCC65
#define YELLOW_GREEN    CLITERAL(Color){ 212, 225,  87, 255 }  // #D4E157
#define BRIGHT_YELLOW   CLITERAL(Color){ 255, 235,  59, 255 }  // #FFEB3B
#define GOLDY            CLITERAL(Color){ 255, 213,  79, 255 }  // #FFD54F
#define AMBER           CLITERAL(Color){ 255, 183,  77, 255 }  // #FFB74D
#define ORANGEY          CLITERAL(Color){ 255, 152,   0, 255 }  // #FF9800
#define CORAL           CLITERAL(Color){ 255, 112,  67, 255 }  // #FF7043
#define DEEP_ORANGE     CLITERAL(Color){ 244,  81,  30, 255 }  // #F4511E
#define REDISH             CLITERAL(Color){ 239,  83,  80, 255 }  // #EF5350
#define MAGENTA_DUH         CLITERAL(Color){ 233,  30,  99, 255 }  // #E91E63
#define PINKY            CLITERAL(Color){ 240,  98, 146, 255 }  // #F06292
#define HOT_PINK        CLITERAL(Color){ 236,  64, 122, 255 }  // #EC407A
#define SHE_LOVES_PURLE          CLITERAL(Color){ 171,  71, 188, 255 }  // #AB47BC
#define SO_DO_I          CLITERAL(Color){ 126,  87, 194, 255 }  // #7E57C2
#define INDIGO          CLITERAL(Color){  92, 107, 192, 255 }  // #5C6BC0
#define BLUE_GRAY       CLITERAL(Color){ 144, 164, 174, 255 }  // #90A4AE
#define SILVER          CLITERAL(Color){ 207, 216, 220, 255 }  // #CFD8DC
#define RED_AF          CLITERAL(Color){  41,   3,   0, 255 }  // #290300


#define BG              CLITERAL(Color){7,0,5,255}
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

    int status;     // activity status of the body
    int frameCounter;
    
    double r;       //Radius
    double mass;
    

    Color color;    

    Vector2d force;
    
    //Seperated by derivatives (force is not a derivate if any of this)
    Vector2d lastPos[LAST_POS_BUFFER];
    Vector2d position;
    Vector2d velocity;
    Vector2d accel;
    
}Particle;   //Consider renaming it body if needed?


typedef struct{
    double minRadius;
    double maxRadius;
    
    double dt;  // Δtime
    double initVelocity;

    int activeParticles;

}Config;


/* ============= GLOBALS ============= */


/* ============= FUNCTION PROTOTYPES ============= */

//Setup 
void generateParticle(Particle *particle, Config *config);    //I wanna call it particle instead of body regardless of the terminology
void setParticles(Particle *particle, int particleAmount, Config *config);

//Render
void displayParticles(Particle *particles, int particleAmount);
void displayTailing(Particle *particles, int particleAmount);


//Game state
void resetForce(Particle *p);
void updateForce(Particle *p1, Particle *p2);

//Listed accordingly to their integral
void updateAccel(Particle *p);
void updateVelocity(Particle *p, double dT);
void updatePos(Particle *p, double dT);
void updateLastPos(Particle *p);

int setupEnv(void);     //Raylib Window manager wrapper 

//Helpers
void mergeParticles(Particle *p1, Particle *p2);
void updateActiveParticles(Particle *particles, int particleCount, Config *config);

int detectCollision(Particle *p1, Particle *p2);   //raylib CheckCollisonCircles wrapper 

double randDouble(double min, double max);

double calculateDiagonal(Particle *p1, Particle *p2);              //Actually it's hypothenus but I can't spell that right consecutively so I'll use 'diagonal' 
double calculateAttraction(Particle *p1, Particle *p2);

Color randColor();

/* ============= MAIN ============= */


int main(void)
{
    srand(time(NULL));

    int returnCode = 0;    
    int particleAmount = 100;
        
    Particle *particles = (Particle *)(malloc(sizeof(Particle)*particleAmount));
    
        //Error handling
    if (setupEnv()) { returnCode = (-13); goto clean; }
    if (particles == NULL) { returnCode = (-1); goto clean; }
    
 
    Config cfg = {  .minRadius=1, 
                    .maxRadius=10, 
                    .initVelocity=20,
                    .activeParticles=particleAmount,
                    //dT update is in game loop
                };

    setParticles(particles, particleAmount, &cfg);

    while (!WindowShouldClose()) {
        //Key interrupt handling
        if (IsKeyPressed(KEY_ESCAPE)) { break; }
    
        cfg.dt = GetFrameTime();

        //State update 

        for (int i = 0;i < particleAmount; i++) {
            resetForce(&particles[i]);
        }
        //That's the part I said 'gonna be O(n^2)' but this project for peace of mind for me...not about portfolio nor optimzation
        
        // Accumulate this frame's forces before integrating with this frame's dt.
        for (int i = 0;i < particleAmount; i++) {
            for (int j = i+1; j< particleAmount; j++) {
                mergeParticles(&particles[i], &particles[j]);
                updateForce(&particles[i], &particles[j]);
            }
        }

        updateActiveParticles(particles,particleAmount, &cfg);

        for (int i = 0; i < particleAmount;i++) {
            updateLastPos(&particles[i]);
        }


        //Integral-Derivative Gang Loop
        for (int i = 0;i < particleAmount; i++) {
            updateAccel(&particles[i]);
            updateVelocity(&particles[i], cfg.dt);
            updatePos(&particles[i], cfg.dt);
        }

        //Drawing
        BeginDrawing();
        ClearBackground(BG);
        displayTailing(particles, particleAmount);
        displayParticles(particles, particleAmount);
        EndDrawing();

    }

clean:

    free(particles);
    particles = NULL;
    CloseWindow();
    switch (returnCode) {
        case -1:
            perror("Allocation problem\n");
            break;
        case -13:
            perror("Graphics problem");
            break;

        default:
            printf("Everything's fine");
            break;
    }

    //Allocated memory so far : 1
    return(returnCode);
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
    
    for (int i = 0; i < LAST_POS_BUFFER;i++) {
        particle->lastPos[i].x = -1;
        particle->lastPos[i].y = -1;
    }
    particle->frameCounter = 0;
}


void setParticles(Particle *particle, int particleAmount, Config *config)
{
    for (int i = 0;i < particleAmount; i++) {
        generateParticle(&particle[i],config);
    }


}


void displayParticles(Particle *particles, int particleAmount)
{

    for (int i = 0; i < particleAmount; i++) {
        if (particles[i].status) {
            DrawCircleV(((Vector2){particles[i].position.x, (float)particles[i].position.y}), (float)particles[i].r, particles[i].color);
        }
    }
}

void displayTailing(Particle *particles, int particleAmount)
{
    for (int i = 0;i < particleAmount; i++) {
        if (!particles[i].status) { continue; }

        for (int j = 0;j< LAST_POS_BUFFER;j++) {
            float posX = particles[i].lastPos[j].x;
            float posY = particles[i].lastPos[j].y;
        
            if (posX != -1) {
                float resize = (float)(LAST_POS_BUFFER - j) / LAST_POS_BUFFER;
                DrawCircleV((Vector2){posX, posY}, particles[i].r*resize, particles[i].color);
            }
        }
    }

}


int setupEnv(void)
{
    int displayID = GetCurrentMonitor();


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

void updateActiveParticles(Particle *particles, int particleCount, Config *config)
{
    int counter = 0;
    for (int i = 0;i < particleCount;i++) {
        if (particles[i].status) {
            counter++;
        }
    }
    config->activeParticles = counter;
}


void mergeParticles(Particle *p1, Particle *p2)
{
    if (!p1->status || !p2->status ) {return;}

    if (detectCollision(p1, p2)) {
        double mergedMass = p1->mass + p2->mass;
        Particle *survivor = p1->r >= p2->r ? p1 : p2;
        Particle *absorbed = survivor == p1 ? p2 : p1;

        // Preserve center of mass, total momentum, and the total rendered area.
        survivor->position.x = (p1->position.x * p1->mass + p2->position.x * p2->mass) / mergedMass;
        survivor->position.y = (p1->position.y * p1->mass + p2->position.y * p2->mass) / mergedMass;
        survivor->velocity.x = (p1->velocity.x * p1->mass + p2->velocity.x * p2->mass) / mergedMass;
        survivor->velocity.y = (p1->velocity.y * p1->mass + p2->velocity.y * p2->mass) / mergedMass;
        survivor->force.x = p1->force.x + p2->force.x;
        survivor->force.y = p1->force.y + p2->force.y;
        survivor->mass = mergedMass;
        survivor->r = sqrt(p1->r * p1->r + p2->r * p2->r);

        absorbed->status = 0;
    }
}

int detectCollision(Particle *p1, Particle *p2)
{
    if (p1->status && p2->status ) {
        if(CheckCollisionCircles((Vector2){p1->position.x, p1->position.y}, (float)p1->r, 
                                (Vector2){p2->position.x, p2->position.y}, (float) p2->r))
        {
            return(1);
        }
    }
    return(0);
}



double randDouble(double min, double max)
{
    double value = (((double)rand() / RAND_MAX)*(max-min))+min;
     
    return(value);
}

double calculateDiagonal(Particle *p1, Particle *p2)
{
    //2D analytical axis notation 
    double x = p1->position.x - p2->position.x;
    double y = p1->position.y - p2->position.y;
    
    return(sqrt((x*x)+(y*y)));
}


double calculateAttraction(Particle *p1, Particle *p2)
{
    double dist = calculateDiagonal(p1, p2);
    double pull = G * (p1->mass*p2->mass)/((dist*dist)+ (SOFTNESS*SOFTNESS));
    
    return(pull);
    //Newton's gravitation interpret G* m1*m2/d^2
}


Color randColor(void)
{
    static const Color COLOR_PALETTE[COLOR_ARR_SIZE] = {
    SKY_BLUE,
    AZURE,
    ELECTRIC_CYAN,
    TURQUOISE,
    NEON_GREEN,
    EMERALD,
    LIME_GREEN,
    YELLOW_GREEN,
    BRIGHT_YELLOW,
    GOLDY,
    AMBER,
    ORANGEY,
    CORAL,
    DEEP_ORANGE,
    REDISH,
    MAGENTA_DUH,
    PINKY,
    HOT_PINK,
    SHE_LOVES_PURLE,
    SO_DO_I,
    INDIGO,
    BLUE_GRAY,
    SILVER,
    RED_AF
};
    return(COLOR_PALETTE[rand()%COLOR_ARR_SIZE]);
}


/* ============ GAME STATE HANDLERS ============*/

void resetForce(Particle *p)
{
    p->force.x = 0.0;
    p->force.y = 0.0;
    
}

void updateForce(Particle *p1, Particle *p2)
{
    if (p1->status && p2->status) {
        double force = calculateAttraction(p1, p2);
        double dx = p2->position.x - p1->position.x;
        double dy = p2->position.y - p1->position.y;

        double r = calculateDiagonal(p1, p2);
        if (r == 0.0) { return; }

        double fx = force*dx / r;
        double fy = force*dy / r;
        
        //Newton's Third Law Fa = -Fb
        p1->force.x += fx;
        p1->force.y += fy;

        p2->force.x -= fx;
        p2->force.y -= fy;
        
    }
}

void updateAccel(Particle *p)
{
    if (p->status) {
        p->accel.x = p->force.x / p->mass;
        p->accel.y = p->force.y / p->mass;
    }
}

void updateVelocity(Particle *p, double dT)
{
    if (p->status) {
        p->velocity.x += p->accel.x * dT;
        p->velocity.y += p->accel.y * dT;
    }
    
}

void updatePos(Particle *p, double dT)
{
    if (p->status) {
        p->position.x += p->velocity.x * dT;
        p->position.y += p->velocity.y * dT;
    }
     
}

void updateLastPos(Particle *p)
{
    if (!p->status) { return; }

    ++p->frameCounter;
    if (p->frameCounter % 5 == 0) {
        for (int i = LAST_POS_BUFFER-1;i > 0; i--) {
            p->lastPos[i].x = p->lastPos[i-1].x;        //Shitfing indexs to make room
            p->lastPos[i].y = p->lastPos[i-1].y;        
        }
        p->lastPos[0].x = p->position.x;
        p->lastPos[0].y = p->position.y;
    }
    if (p->frameCounter >= 1000) { p->frameCounter = 0; }
}
