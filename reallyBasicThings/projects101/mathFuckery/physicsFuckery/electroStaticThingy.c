/*

                            ================ YAPPING =====================

    'sup? In today's episode of how to make Coulomb roll in his grave we're doing electrostatic particle sim... you remember the n body sim right? this is inspired by that idea too...
    We're simply doing the same thing for 'subatomic particles' the last one was all particles attract all particles this one gonna be 
    opposing forces attract each other for initial draft we'll see how it goes... 


    Anyways this is here as a template tho...

*/


/* ========================= INCLUDES =================== */


//Coool headers
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/random.h>

//Linky bois    (-lraylib, -lm)
#include <raylib.h>
#include <math.h>

/* ======================== DEFINES ==================== */

#define WIDTH 1200.f
#define HEIGHT 900.f
#define TITLE "Fancy very small balls attracting some of them"


#ifndef FPS 
    #define FPS 120
#endif //FPS


#define CHARGE_AMOUNT 130
#define SPEED 12

#define CHARGE_R 5

#define MAGIC_SIM_NUM 5313.1353f
// Simulation units: equal masses of 1, charges +/-1, positions in pixels

#define SOFTENING CHARGE_R
#define PHYSICS_DT (1.0 / 240.0)
#define MAX_FRAME_DT 0.1

#define GLOW_RADIUS_SCALE 6.0f
#define GLOW_STRENGTH 0.85f

//Color defines
#define RED_AF CLITERAL(Color){128, 0, 6, 255}
#define BLUE_BLUE CLITERAL(Color){6, 0, 88, 255}


/* =================================== SHADERS ========================== */
//This is what I've duct-taped together using raylib tutorials + google lol (still sorcery )
static const char *CHARGE_GLOW_FS =
    "#version 330\n"
    "in vec2 fragTexCoord;\n"
    "in vec4 fragColor;\n"
    "out vec4 finalColor;\n"
    "uniform float glowRadius;\n"
    "uniform float glowStrength;\n"
    "void main()\n"
    "{\n"
    "    float radius = length(fragTexCoord * 2.0 - 1.0);\n"
    "    float d = radius * glowRadius;\n"
    "    float aa = max(fwidth(d), 0.001);\n"
    "    float core = 1.0 - smoothstep(1.0 - aa, 1.0 + aa, d);\n"
    "    float halo = glowStrength * (0.7 * exp(-0.3*d*d)\n"
    "                               + 0.3 * exp(-1.3*d*d));\n"
    "    float hotCenter = 1.0 - smoothstep(0.0, 0.85, d);\n"
    "    vec3 light = fragColor.rgb * (core + halo)\n"
    "               + vec3(0.65) * hotCenter;\n"
    "    float fade = 1.0 - smoothstep(0.8, 1.0, radius);\n"
    "    finalColor = vec4(light, fragColor.a * fade);\n"
    "}\n";


/* ========================== OBJECTS ==================== */

typedef struct{

    float r;    //Radius ykr?
    Vector2 pos;
    Vector2 vel;
    //Accel in spirit
    Vector2 force;  //does force have vectors?
    int charge; //Yeah struct and field has the same 'charge' var so...
    
    Color color;
}Charge;


/* =========================== FUNCTION PROTS =============== */



void drawCharges(Charge *charges, int amount, Shader glow, Texture2D glowQuad);
void resetForce(Charge *charges, int amount);
void math(Charge *charges, int amount);
void collCheck(Charge *charges, int amount);
void updateCharges(Charge *charges, int amount, float dt);
int setupEnv(void);
int rng(int *holder,int min, int max); //CSPRNG BITCH!!!!
int setCharges(Charge *charges, int amount);

/* ====================== MAIN ==================== */


int main(void)
{

    Charge *charges = (Charge *)malloc(sizeof(Charge)*CHARGE_AMOUNT);
    if (charges == NULL) { perror("Charges fucked..."); return(-1); }
    

    if (setupEnv()) { free(charges); return(-53); }

    if (setCharges(charges, CHARGE_AMOUNT)) {
        perror("Could not initialize charges");
        free(charges);
        CloseWindow();
        return EXIT_FAILURE;
    }

    Shader glow = LoadShaderFromMemory(NULL, CHARGE_GLOW_FS);
    Texture2D glowQuad = {0};
    int radiusLoc = GetShaderLocation(glow, "glowRadius");
    int strengthLoc = GetShaderLocation(glow, "glowStrength");
    // Missing uniforms also detect raylib falling back to its default shader.
    if (radiusLoc >= 0 && strengthLoc >= 0) {
        float radius = GLOW_RADIUS_SCALE;
        float strength = GLOW_STRENGTH;
        SetShaderValue(glow, radiusLoc, &radius, SHADER_UNIFORM_FLOAT);
        SetShaderValue(glow, strengthLoc, &strength, SHADER_UNIFORM_FLOAT);
        Image whitePixel = GenImageColor(1, 1, WHITE);
        glowQuad = LoadTextureFromImage(whitePixel);
        UnloadImage(whitePixel);
    }
    if (glowQuad.id == 0) {
        TraceLog(LOG_WARNING, "Charge glow unavailable; drawing solid particles");
    }

    double accumulator = 0.0;
    while (!WindowShouldClose()) {
        if(IsKeyPressed(KEY_ESCAPE)){ break; }
        double frame_dt = GetFrameTime();
        // Discard long pauses instead of taking a huge, unstable physics step.
        if (isfinite(frame_dt) && frame_dt > 0.0) {
            accumulator += fmin(frame_dt, MAX_FRAME_DT);
        }

        //Math thigny
        while (accumulator >= PHYSICS_DT) {
            updateCharges(charges, CHARGE_AMOUNT, (float)PHYSICS_DT);
            accumulator -= PHYSICS_DT;
        }

        //Draw thingy
        BeginDrawing();
        ClearBackground(BLACK);
        drawCharges(charges, CHARGE_AMOUNT, glow, glowQuad);
        EndDrawing();
    }


    free(charges);
    charges = NULL;

    if (glowQuad.id != 0) { UnloadTexture(glowQuad); }
    UnloadShader(glow);
    CloseWindow();
    return(0);
}


/* =================== FUNCTION BODIES =============0*/

int setupEnv(void)
{
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(WIDTH, HEIGHT, TITLE);
    if (!IsWindowReady()) { return(-1);}
    
    SetTargetFPS(FPS);
    
    return(0);
}

int rng(int *holder, int min, int max)
{

    if (holder == NULL || min >= max) { errno = EINVAL; return(-1); }

    uint64_t span = (uint64_t)((int64_t)max - min);
    uint64_t limit = (UINT64_C(1) << 32) / span * span;
    uint32_t sample;

    do {
        size_t filled = 0;
        while (filled < sizeof(sample)) {
            ssize_t count = getrandom((unsigned char *)&sample + filled,
                                      sizeof(sample) - filled, 0);
            if (count < 0) {
                if (errno == EINTR) { continue; }
                return(-1);
            }
            if (count == 0) { errno = EIO; return(-1); }
            filled += (size_t)count;
        }
    } while ((uint64_t)sample >= limit);
    *holder = (int)((int64_t)min + (int64_t)(sample % span));

    return(0);
}


int setCharges(Charge *charges, int amount)
{
    if (charges == NULL) {
        errno = EINVAL;
        return(-1);
    }

    int x,y;
    int vx,vy;
    int charge_roll;
    
    for (Charge *iter = charges; iter < charges+amount; iter++) {
        //Been a while since I've used pointers to walk so...why not?
        
        iter->r = CHARGE_R;
        iter->force = (Vector2){ 0 };
        
        if (rng(&charge_roll, 0, 20)) { return(-1); }
        
        iter->charge = (charge_roll % 2) ? 1 : -1;
        iter->color = iter->charge > 0 ? RED_AF : BLUE_BLUE;
        
        if(rng(&x, iter->r, (WIDTH-iter->r))) { return(-1); }
        if(rng(&y, iter->r, (HEIGHT- iter->r))) { return(-1); }
        
        iter->pos.x = (float)x;
        iter->pos.y = (float)y;
        
        if(rng(&vx, -SPEED, SPEED + 1)) { return(-1); }
        if(rng(&vy, -SPEED, SPEED + 1)) { return(-1); }
        
        iter->vel.x = (float)vx;
        iter->vel.y = (float)vy;
        
    }

    return(0);
}

void drawCharges(Charge *charges, int amount, Shader glow, Texture2D glowQuad)
{
    if (charges == NULL) {
        perror("Can not be null tho");
        return;
    }

    if (glowQuad.id == 0) {
        for (Charge *iter = charges; iter < charges + amount; iter++) {
            DrawCircleV(iter->pos, iter->r, iter->color);
        }
        return;
    }

    BeginBlendMode(BLEND_ADDITIVE);
    BeginShaderMode(glow);
    for (Charge *iter = charges; iter < charges + amount; iter++) {
        float radius = iter->r * GLOW_RADIUS_SCALE;
        Rectangle destination = {iter->pos.x - radius, iter->pos.y - radius,
                                 radius * 2.0f, radius * 2.0f};
        DrawTexturePro(glowQuad, (Rectangle){0, 0, 1, 1}, destination,
                       (Vector2){0, 0}, 0.0f, iter->color);
    }
    EndShaderMode();
    EndBlendMode();

}

//Force brute-forcing lol
void math(Charge *charges, int amount)
{
    if (charges == NULL) {
        perror("Bruh really?");
        return;
    }

    resetForce(charges, amount);

    Charge *first;
    Charge *second; 
    for (int i = 0; i < amount; i++) {
        first = &charges[i];
        
        for (int j = i+1; j < amount ; j++) {
            //The same minor 'optimization' trick using C(n,2) instead of looping over the same pair twice
            second = &charges[j];

            //Coulomb math 
            float dx = second->pos.x - first->pos.x; 
            float dy = second->pos.y - first->pos.y;
            // Smooth potential U = k*q1*q2 / sqrt(r*r + epsilon*epsilon).
            //To prevent fucking singularity
            float d_squared = dx*dx + dy*dy + SOFTENING*SOFTENING;
            float dist = sqrtf(d_squared);

            float normalized_x = dx / dist;
            float normalized_y = dy / dist;

            // Effective Coulomb constant in simulation units.
            float force = MAGIC_SIM_NUM * (first->charge * second->charge)/(d_squared); 
            
            float fx = force * normalized_x;
            float fy = force * normalized_y;

            first->force.x -= fx; 
            first->force.y -= fy;   //particles repel each other when same charges are present and vice versa when not (you got the idea)
            second->force.x += fx;   // Fa = -Fb due to Newton 
            second->force.y += fy;
            
        }
    }

}


void updateCharges(Charge *charges, int amount, float dt)
{
    if (charges == NULL) {
        perror("No charge...");
        return;
    }

    if (!isfinite(dt) || dt <= 0.0f) { return; }

    // Velocity Verlet: half kick, full drift, new forces, half kick (mass = 1).
    math(charges, amount);
    for (Charge *iter = charges; iter < charges+amount; iter++) {
        iter->vel.x += 0.5f * iter->force.x*dt;
        iter->vel.y += 0.5f * iter->force.y*dt;
        
        iter->pos.x += iter->vel.x*dt;
        iter->pos.y += iter->vel.y*dt;
    }
    collCheck(charges, amount);
    math(charges, amount);
    for (Charge *iter = charges; iter < charges+amount; iter++) {
        iter->vel.x += 0.5f * iter->force.x*dt;
        iter->vel.y += 0.5f * iter->force.y*dt;
    }

}

void resetForce(Charge *charges, int amount)
{
    if (charges == NULL) {
        perror("This gets repetitive for no reason...");
        return;
    }

    for (Charge *iter = charges; iter < charges+amount; iter++) {
        iter->force = (Vector2){0,0};
    }

}

static void reflectAxis(float *position, float *velocity, float min, float max)
{
    if (*position > min && *position < max) { return; }

    // Fold the traveled distance into the box, preserving overshoot and speed,
    // including steps that cross more than one wall.
    double width = (double)max - min;
    double folded = fmod((double)*position - min, 2.0 * width);
    if (folded < 0.0) { folded += 2.0 * width; }
    if (folded >= width) {
        *position = (float)(max - (folded - width));
        *velocity = -*velocity;
    } else {
        *position = (float)(min + folded);
    }
    if (*position <= min) { *velocity = fabsf(*velocity); }
    if (*position >= max) { *velocity = -fabsf(*velocity); }
}

void collCheck(Charge *charges, int amount)
{

    if (charges == NULL) {
        perror("Please stop sending null pointers those won't even gonna see those things");
        return;
    }

    for (Charge *iter = charges; iter < charges + amount; iter++) {
        reflectAxis(&iter->pos.x, &iter->vel.x, iter->r, WIDTH - iter->r);
        reflectAxis(&iter->pos.y, &iter->vel.y, iter->r, HEIGHT - iter->r);
    }
}
