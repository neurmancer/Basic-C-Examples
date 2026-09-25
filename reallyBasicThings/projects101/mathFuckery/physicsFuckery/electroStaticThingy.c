/*

                            ================ YAPPING =====================

    'sup? In today's episode of how to make Coulomb roll in his grave we're doing electrostatic particle sim... you remember the n body sim right? this is inspired by that idea too...
    We're simply doing the same thing for 'subatomic particles' the last one was all particles attract all particles this one gonna be 
    opposing forces attract each other for initial draft we'll see how it goes... 


    Anyways this is here as a template tho...

*/


/* ========================= INCLUDES =================== */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/random.h>
#include <raylib.h>

/* ======================== DEFINES ==================== */

#define WIDTH 1200.f
#define HEIGHT 900.f
#define TITLE "Fancy very small balls attracting some of them"


#ifndef FPS 
    #define FPS 120
#endif //FPS


#define CHARGE_AMOUNT 30
#define SPEED 12

#define MAGIC_SIM_NUM 530.f
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


void setCharges(Charge *charges, int amount);
void drawCharges(Charge *charges, int amount);
void math(Charge *charges, int amount);
void updateCharges(Charge *charges, int amount, float dt);
int setupEnv(void);
int rng(int *holder,int min, int max); //CSPRNG BITCH!!!!


/* ====================== MAIN ==================== */


int main(void)
{

    Charge *charges = (Charge *)malloc(sizeof(Charge)*CHARGE_AMOUNT);
    if (charges == NULL) { perror("Charges fucked..."); return(-1); }
    

    if (setupEnv()) { perror("Raylib...bruh..."); return(-53); }

    setCharges(charges, CHARGE_AMOUNT);

    float dt = 0.0f;
    while (!WindowShouldClose()) {
        if(IsKeyPressed(KEY_ESCAPE)){ break; }
        dt = GetFrameTime();
        
        math(charges, CHARGE_AMOUNT);
        updateCharges(charges, CHARGE_AMOUNT , dt);
        BeginDrawing();
        ClearBackground(BLACK);
        drawCharges(charges, CHARGE_AMOUNT);
        EndDrawing();
    }


    free(charges);
    charges = NULL;

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
    if (getrandom(holder, sizeof((*holder)), 0) < 0) { return(-13); }
    if (*holder < 0) { *holder = (~(*holder))+1; }

    *holder = (*holder) % (max-min) + min;

    return(0);
}


void setCharges(Charge *charges, int amount)
{
    if (charges == NULL) {
        perror("I need at least one charge bruh...");
        return;
    }

    int x,y;
    int vx,vy;
    
    for (Charge *iter = charges; iter < charges+amount; iter++) {
        //Been a while since I've used pointers to walk so...why not?
        
        iter->r = 10;
        iter->force = (Vector2){ 0 };
        iter->charge = 1;  
        iter->color = BLUE;
        
        if(rng(&x, iter->r, (WIDTH-iter->r))) { perror("RNGSUS ERROR"); return; }
        if(rng(&y, iter->r, (HEIGHT- iter->r))) { perror("RNGSUS ERROR"); return; }
        iter->pos.x = (float)x;
        iter->pos.y = (float)y;
        
        if(rng(&vx, -SPEED, SPEED)) { perror("RNGS SAID NOPE AGAIN!"); return; }
        if(rng(&vy, -SPEED, SPEED)) { perror("RNGS SAID NOPE AGAIN!"); return; }
        iter->vel.x = (float)vx;
        iter->vel.y = (float)vy;
        
    }

}

void drawCharges(Charge *charges, int amount)
{
    if (charges == NULL) {
        perror("Can not be null tho");
        return;
    }

    for (Charge *iter = charges; iter < charges + amount ; iter++) { DrawCircleV(iter->pos, iter->r, iter->color); }

}

//Force brute-forcing lol
void math(Charge *charges, int amount)
{
    if (charges == NULL) {
        perror("Bruh really?");
        return;
    }

    for (int i = 0; i < amount; i++) {
        charges[i].force = (Vector2){ 0 };
    }

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
            float d_squared = fmaxf(dx*dx + dy*dy, 1.0f);
            float dist = sqrtf(d_squared);

            float normalized_x = dx / dist;
            float normalized_y = dy / dist;

            //This is correct ig... (except I didn't put the coulomb constant I guess?)
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

    for (Charge *iter = charges; iter < charges+amount; iter++) {
        iter->vel.x += iter->force.x*dt; //Force acting like accel basically ( yeah I know this is stupid but...)
        iter->vel.y += iter->force.y*dt;
        
        iter->pos.x += iter->vel.x*dt;
        iter->pos.y += iter->vel.y*dt;
    }

}
