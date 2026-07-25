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

#define COLOR_ARR_SIZE 3
#define LAST_POS_BUFFER 10 

//Config defines
#ifndef VSYNC 
    #define VSYNC 0 //If you want VSYNC type -DVSYNC=1 as you compile
#endif

#ifndef FPS
    #define FPS 120     //This time I'll make it configurable as you compile: usage: -DFPS=FPS_YOU_WANT (Hard capped at 300fps and 0 for no limit)
#endif

//Phyiscal constant
#define G (59.8)   //For test purpose (earth's g) real capital G's value is approximately 6.6743×10^-11 can double hold that? I'll check
#define SOFTNESS (7.5)

static const char *CRT_FRAGMENT_SHADER =
    "#version 330\n"
    "in vec2 fragTexCoord;\n"
    "uniform sampler2D texture0;\n"
    "uniform float uTime;\n"
    "uniform vec2 uResolution;\n"
    "out vec4 finalColor;\n"
    "\n"
    "void main()\n"
    "{\n"
    "    vec2 uv = fragTexCoord * 2.0 - 1.0;\n"
    "    vec2 bentUv = uv * (1.0 + 0.16 * vec2(uv.y * uv.y, uv.x * uv.x));\n"
    "    vec2 sourceUv = bentUv * 0.5 + 0.5;\n"
    "    float inScreen = step(0.0, sourceUv.x) * step(sourceUv.x, 1.0)\n"
    "                   * step(0.0, sourceUv.y) * step(sourceUv.y, 1.0);\n"
    "    float vignette = smoothstep(0.40, 1.15, length(bentUv));\n"
    "\n"
    "    float scanline = 0.5 + 0.5 * sin(fragTexCoord.y * uResolution.y * 3.14159265);\n"
    "    float rollingBar = smoothstep(0.03, 0.0, abs(fragTexCoord.y - fract(uTime * 0.16)));\n"
    "    float flicker = 0.985 + 0.015 * sin(uTime * 55.0);\n"
    "\n"
    "    vec3 color = texture(texture0, sourceUv).rgb;\n"
    "    color *= mix(0.92, 1.0, scanline) * flicker;\n"
    "    color += rollingBar * 0.012;\n"
    "    color *= 1.0 - vignette * 0.18;\n"
    "\n"
    "    finalColor = vec4(color * inScreen, 1.0);\n"
    "}\n";


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
    int crtEnabled = 0;
    Particle *particles = NULL;
    RenderTexture2D simulationTarget = {0};
    Shader crtShader = {0};
    int crtTimeLocation = -1;
    int crtResolutionLocation = -1;
    float crtResolution[2] = { WIDTH, HEIGHT };
        
    //Error handling
    if (setupEnv()) { returnCode = (-13); goto clean; }

    simulationTarget = LoadRenderTexture(WIDTH, HEIGHT);
    crtShader = LoadShaderFromMemory(NULL, CRT_FRAGMENT_SHADER);
    if (simulationTarget.id == 0 || crtShader.id == 0) { returnCode = (-14); goto clean; }

    crtTimeLocation = GetShaderLocation(crtShader, "uTime");
    crtResolutionLocation = GetShaderLocation(crtShader, "uResolution");
    if (crtTimeLocation < 0 || crtResolutionLocation < 0) { returnCode = (-14); goto clean; }
    SetShaderValue(crtShader, crtResolutionLocation, crtResolution, SHADER_UNIFORM_VEC2);

    particles = malloc(sizeof(*particles) * (size_t)particleAmount);
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
        if (IsKeyPressed(KEY_C)) { crtEnabled = !crtEnabled; }
    
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

        // Draw the simulation to a texture so it can be presented normally or through the CRT shader.
        BeginTextureMode(simulationTarget);
        ClearBackground(BLACK);
        displayTailing(particles, particleAmount);
        displayParticles(particles, particleAmount);
        EndTextureMode();

        BeginDrawing();
        ClearBackground(BLACK);
        Rectangle source = { 0.0f, 0.0f, (float)simulationTarget.texture.width, -(float)simulationTarget.texture.height };
        if (crtEnabled) {
            float crtTime = (float)GetTime();
            SetShaderValue(crtShader, crtTimeLocation, &crtTime, SHADER_UNIFORM_FLOAT);
            BeginShaderMode(crtShader);
            DrawTextureRec(simulationTarget.texture, source, (Vector2){ 0.0f, 0.0f }, WHITE);
            EndShaderMode();
        }
        else {
            DrawTextureRec(simulationTarget.texture, source, (Vector2){ 0.0f, 0.0f }, WHITE);
        }
        EndDrawing();

    }

clean:

    if (crtShader.id != 0) { UnloadShader(crtShader); }
    if (simulationTarget.id != 0) { UnloadRenderTexture(simulationTarget); }
    free(particles);
    CloseWindow();
    switch (returnCode) {
        case -1:
            perror("Allocation problem\n");
            break;
        case -13:
            perror("Graphics problem");
            break;
        case -14:
            fprintf(stderr, "Could not create the CRT render target or shader.\n");
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
    Color colors[COLOR_ARR_SIZE] = { RED,GREEN,BLUE };
    return(colors[rand()%COLOR_ARR_SIZE]);
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
