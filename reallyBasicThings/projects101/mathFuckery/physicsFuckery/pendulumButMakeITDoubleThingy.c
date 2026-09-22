/*
                ========================== YAPPING =======================

                'Sup? It's 3 AM and I wonder what if I were to add another ball to the pendulumThingy? we're here to find out 
                Welcome to yet another physics fuckerys 

                well my first idea was more PI gamba using Leibniz series (yk the series) or Basel Problem (which Euler proved that it converges pi^2 / 6) 
                for CLI instead of graphics but I thought that I abondoned physics fuckery for a while now....
                So we start with more balls

                This shit here because I found out this cool graph in MIT's website: https://web.mit.edu/jorloff/www/chaosTalk/double-pendulum/double-pendulum-en.html

                and lol as always this is a template for now....

*/




/* ======================= INCLUDES =================== */
//cool headers
#include <stdio.h>
#include <time.h>
//Headers that will bitch about not linking them
#include <raylib.h>
#include <math.h>



/* ======================= DEFINES ======================= */

#define WIDTH 1280
#define HEIGHT 960
#define TITLE "Strings and Balls Thingy"


//Color defines
#define SHE_LOVES_PURPLE CLITERAL(Color){191, 0, 255,255}
#define SO_DO_I CLITERAL(Color){153, 102, 204,255}
#define RED_AF CLITERAL(Color){53,0,13,255}
#define GRAYISH       CLITERAL(Color){ 144, 164, 174, 255 }  
// Object defines
#define BALL_RADIUS (33.3f)
#define LINE_THICKNESS (3.5)
#define POSITION_HISTORY_LENGTH 1000
#define TRAIL_HISTORY_LENGTH 240
#define PHYSICS_DT (1.0 / 480.0)  // Accuracy shit : seconds per RK4 step
#define HISTORY_SAMPLE_STEPS 10  
#define MAX_FRAME_TIME 0.25 //Simply to prevent continental drift ater a freeze      

#ifndef FPS 
    #define FPS 120
#endif

#ifndef SIM_SPEED
    #define SIM_SPEED 2.5
#endif

/* ====================== OBJECTS ============================= */


typedef struct{
    //Well...what should I put here again?

    double th1, th2; //Theta 1 and theta 2 (angles) (btw I'll be following the notation given below)
    double dTh1, dTh2;   //First deriv. of angles (angular velo)
    double ddTh1, ddTh2; //Second deriv of angles (first deriv of angular vel (angualar accel))
    
    double m1,m2;    //Masses
    double l1,l2;    //Rod lengths in pixels (80 pixels per metre).
    double gravity; //Pixels per simulation second squared.

}Physics;    //as the giant nerd yapping down here suggests we need both balls affecting each other's movement so keeping physics separate make sense I guess


typedef struct{
    Vector2 startPos;
    Vector2 endPos;
    float len;
    Color color;
}Line;
//Yeah in this file I am getting shit done with weird short names don't mind it...
typedef struct{
    Vector2 pos;
    float radius;
    Color color;
}Ball;

typedef struct{
    Line line;
    Ball ball;
}Pendulum;


typedef struct{
    Pendulum pend[2];   //Yeah as if math is not enough I am going with a little pointer gymnastics too
    Physics engine;
}Entities;


typedef struct{

    Pendulum pendCfg[2];
    Physics engineCfg;

}Config;

typedef struct {
    double th1, th2, dTh1, dTh2;
} State;

typedef struct {
    double accumulator;
    int sampleSteps;
} SimulationClock;

typedef struct {
    Vector2 positions[2][POSITION_HISTORY_LENGTH];
    int next;  // Next slot to overwrite, both bobs (who is bob tho?).
    int count;
} PositionHistory;

//and here is the fun shit... wtf fuck is the formula
/*

            ====================== MINI CALCULUS LECTURE =========================

x = horizontal position of pendulum mass
y = vertical position of pendulum mass
θ = angle of pendulum (0 = vertical downwards, counter-clockwise is positive)
L = length of rod (constant)


x1 = L1 sin θ1

y1 = −L1 cos θ1

x2 = x1 + L2 sin θ2

y2 = y1 − L2 cos θ2

The velocity is the derivative with respect to time of the position.

x1' = θ1' L1 cos θ1

y1' = θ1' L1 sin θ1

x2' = x1' + θ2' L2 cos θ2

y2' = y1' + θ2' L2 sin θ2

The acceleration is the second derivative.

  	x1'' = −θ1'2 L1 sin θ1 + θ1'' L1 cos θ1	(1)
  	y1'' = θ1'2 L1 cos θ1 + θ1'' L1 sin θ1	(2)
  	x2'' = x1'' − θ2'2 L2 sin θ2 + θ2'' L2 cos θ2	(3)
  	y2'' = y1'' + θ2'2 L2 cos θ2 + θ2'' L2 sin θ2	(4)


Forces in the Double Pendulum
forces in upper mass of double pendulum
upper mass

forces in lower mass of double pendulum
lower mass
We treat the two pendulum masses as point particles. 
Begin by drawing the free body diagram for the upper mass and writing an expression for the net force acting on it. Define these variables:

T = tension in the rod
m = mass of pendulum
g = gravitational constant
The forces on the upper pendulum mass are the tension in the upper rod T1 , 
the tension in the lower rod T2 , and gravity −m1 g . 
We write separate equations for the horizontal and vertical forces, since they can be treated independently. 
The net force on the mass is the sum of these. Here we show the net force and use Newton's law F = m a .

  	m1 x1'' = −T1 sin θ1 + T2 sin θ2	(5)
  	m1 y1'' = T1 cos θ1 − T2 cos θ2 − m1 g	(6)
For the lower pendulum, 
the forces are the tension in the lower rod T2 , and gravity −m2 g .

  	m2 x2'' = −T2 sin θ2	(7)
  	m2 y2'' = T2 cos θ2 − m2 g	(8)
In relating these equations to the diagrams, 
keep in mind that in the example diagram θ1 is positive and θ2 is negative, because of the convention that a counter-clockwise angle is positive.


Now we do some algebraic manipulations with the goal of finding expressions for θ1'', θ2'' in terms of θ1, θ1', θ2, θ2' . 
Begin by solving equations (7), (8) for T2 sin θ2 and T2 cos θ2 and then substituting into equations (5) and (6).

  	m1 x1'' = −T1 sin θ1 − m2 x2''	(9)
  	m1 y1'' = T1 cos θ1 − m2 y2'' − m2 g − m1 g	(10)
Multiply equation (9) by cos θ1 and equation (10) by sin θ1 and rearrange to get

  	T1 sin θ1 cos θ1 = −cos θ1 (m1 x1'' + m2 x2'')	(11)
  	T1 sin θ1 cos θ1 = sin θ1 (m1 y1'' + m2 y2'' + m2 g + m1 g)	(12)
This leads to the equation

  	sin θ1 (m1 y1'' + m2 y2'' + m2 g + m1 g) = −cos θ1 (m1 x1'' + m2 x2'')	(13)
Next, multiply equation (7) by cos θ2 and equation (8) by sin θ2 and rearrange to get

  	T2 sin θ2 cos θ2 = −cos θ2 (m2 x2'')	(14)
  	T2 sin θ2 cos θ2 = sin θ2 (m2 y2'' + m2 g)	(15)
which leads to

  	sin θ2 (m2 y2'' + m2 g) = −cos θ2 (m2 x2'')	(16)
Next we need to use a computer algebra program to solve equations (13) and (16) for θ1'', θ2'' in terms of θ1, θ1', θ2, θ2' . 
Note that we also include the definitions given by equations (1-4), so that we have 2 equations (13, 16) and 2 unknowns ( θ1'', θ2'' ). 
The result is somewhat complicated, but is easy enough to program into the computer.

θ1'' =  	−g (2 m1 + m2) sin θ1 − m2 g sin(θ1 − 2 θ2) − 2 sin(θ1 − θ2) m2 (θ2'2 L2 + θ1'2 L1 cos(θ1 − θ2))
L1 (2 m1 + m2 − m2 cos(2 θ1 − 2 θ2))
θ2'' =  	2 sin(θ1 − θ2) (θ1'2 L1 (m1 + m2) + g(m1 + m2) cos θ1 + θ2'2 L2 m2 cos(θ1 − θ2))
L2 (2 m1 + m2 − m2 cos(2 θ1 − 2 θ2))
These are the equations of motion for the double pendulum.


The above equations are now close to the form needed for the Runge Kutta method. Thx nerds of MIT I luv u OwO   -Neuro
The final step is convert these two 2nd order equations into four 1st order equations. 

Define the first derivatives as separate variables:

ω1 = angular velocity of top rod
ω2 = angular velocity of bottom rod
Then we can write the four 1st order equations:

θ1' = ω1

θ2' = ω2

ω1' =  	−g (2 m1 + m2) sin θ1 − m2 g sin(θ1 − 2 θ2) − 2 sin(θ1 − θ2) m2 (ω22 L2 + ω12 L1 cos(θ1 − θ2))
L1 (2 m1 + m2 − m2 cos(2 θ1 − 2 θ2))
ω2' =  	2 sin(θ1−θ2) (ω12 L1 (m1 + m2) + g(m1 + m2) cos θ1 + ω22 L2 m2 cos(θ1 − θ2))
L2 (2 m1 + m2 − m2 cos(2 θ1 − 2 θ2))
This is now exactly the form needed to plug in to the Runge-Kutta method for numerical solution of the system.


Well...I am feeling too smart and too fucking dumb at the same time rn... Who would have thought that I need to open my calculus book to study at 4 AM before coding anything...me...I'd thought that...
5AM me gonna read this again and cry...

*/


//That's it I guess
/* =================== FUNCTION PROTOTYPES ==================*/

void drawThingies(Entities *ent);
void setStage(Entities *ent, Config *cfg);
void rk4Step(Physics *engine, double dt);
void updateAccelerations(Physics *engine);
void advanceSimulation(Entities *ent, PositionHistory *history, SimulationClock *clock, double frameTime);
void updatePositions(Entities *ent);
void recordPositions(PositionHistory *history, const Entities *ent);
void drawTrail(const PositionHistory *history, Vector2 currentPosition);
void drawPositionGraphs(const PositionHistory *history, const Entities *ent);
int setEnv(void);


State math(State s, Physics *eng);


int main(void)
{
    SetRandomSeed(time(NULL));
    if (setEnv()) { perror("Blame raylib bruh"); return(-53); }


Config cfg = {
    .engineCfg = {
        .m1 = 20.0f,
        .m2 = 10.0f,
        .l1 = 250.0f,
        .l2 = 200.0f,
        .gravity = 9.81 * 80.0,
        .th1 = GetRandomValue(-120, 120) * (acos(-1.0) / 180.0),
        .th2 = GetRandomValue(-120, 120) * (acos(-1.0) / 180.0),
        .dTh1 = 0.0f,
        .dTh2 = 0.0f,
        .ddTh1 = 0.0f,
        .ddTh2 = 0.0f
    },
    .pendCfg[0] = {
        .line = { (Vector2){WIDTH/2.0f, 80.0f}, {0}, 0,  GRAYISH},
        .ball = { {0}, BALL_RADIUS, RED_AF }
    },
    .pendCfg[1] = {
        .line = { {0}, {0}, 0, GRAYISH },
        .ball = { {0}, BALL_RADIUS * 0.75f, RED_AF }
    }
};

    //Btw I never mentioned that but designated initilizers are a C99+ feature so if your standard is C89 or ISO-C compile with -std=c99 and some people say c99 is buggy but I didn't encounter such thing yet tho


    Entities objs = { 0 };

    setStage(&objs, &cfg);
    PositionHistory history = { 0 };
    bool showGraphs = false;
    recordPositions(&history, &objs);
    
    SimulationClock clock = { 0 };
    double previousTime = GetTime();
    while (!WindowShouldClose()) {
        double now = GetTime();
        double dt = now - previousTime;
        previousTime = now;
        if (IsKeyPressed(KEY_ESCAPE)) { break; }
        if (IsKeyPressed(KEY_G)) { showGraphs = !showGraphs; }

        advanceSimulation(&objs, &history, &clock, dt);

        BeginDrawing();
        ClearBackground(BLACK);
        drawTrail(&history, objs.pend[1].ball.pos);
        drawThingies(&objs);
        if (showGraphs) { drawPositionGraphs(&history, &objs); }
        DrawText(showGraphs ? "[G] Hide position graphs" : "[G] Show position graphs", 20, 20, 20, RAYWHITE);
        DrawText("Peak autism...", 20, 50 , 20, RAYWHITE);
        EndDrawing();
    }


    CloseWindow();
    return(0);
}

void setStage(Entities *ent, Config *cfg)
{

    ent->engine = cfg->engineCfg;

    for (int i = 0; i < 2; i++) {
        ent->pend[i].ball.color  = cfg->pendCfg[i].ball.color;
        ent->pend[i].ball.radius = cfg->pendCfg[i].ball.radius;
        ent->pend[i].line.color  = cfg->pendCfg[i].line.color;
    }

    ent->pend[0].line.startPos = (Vector2){ WIDTH / 2.0f, 80.0f };

    updateAccelerations(&ent->engine);
    updatePositions(ent);
}

void advanceSimulation(Entities *ent, PositionHistory *history, SimulationClock *clock, double frameTime)
{
    clock->accumulator += fmin(frameTime, MAX_FRAME_TIME) * SIM_SPEED;
    while (clock->accumulator >= PHYSICS_DT) {
        rk4Step(&ent->engine, PHYSICS_DT);
        clock->accumulator -= PHYSICS_DT;
        if (++clock->sampleSteps == HISTORY_SAMPLE_STEPS) {
            updatePositions(ent);
            recordPositions(history, ent);
            clock->sampleSteps = 0;
        }
    }
    updatePositions(ent);
}

void drawThingies(Entities *ent)
{
    for (int i = 1; i >= 0; i--) {
         
        DrawLineEx(ent->pend[i].line.startPos, ent->pend[i].line.endPos, 6.f, ent->pend[i].line.color);
        DrawCircleV(ent->pend[i].ball.pos, ent->pend[i].ball.radius, ent->pend[i].ball.color);   
    }
}

void recordPositions(PositionHistory *history, const Entities *ent)
{
    for (int bob = 0; bob < 2; bob++) {
        history->positions[bob][history->next] = ent->pend[bob].ball.pos;
    }
    history->next = (history->next + 1) % POSITION_HISTORY_LENGTH;
    if (history->count < POSITION_HISTORY_LENGTH) { history->count++; }
}

void drawTrail(const PositionHistory *history, Vector2 currentPosition)
{
    int length = history->count < TRAIL_HISTORY_LENGTH ? history->count : TRAIL_HISTORY_LENGTH;
    int start = (history->next - length + POSITION_HISTORY_LENGTH) % POSITION_HISTORY_LENGTH;
    for (int i = 1; i < length; i++) {
        int previous = (start + i - 1) % POSITION_HISTORY_LENGTH;
        int current = (start + i) % POSITION_HISTORY_LENGTH;
        float opacity = (float)i / (length - 1);
        DrawLineEx(history->positions[1][previous], history->positions[1][current],
                   2.5f, Fade(SHE_LOVES_PURPLE, opacity));
    }
    if (length > 0) {
        int newest = (history->next - 1 + POSITION_HISTORY_LENGTH) % POSITION_HISTORY_LENGTH;
        DrawLineEx(history->positions[1][newest], currentPosition, 2.5f, SHE_LOVES_PURPLE);
    }
}

void drawPositionGraphs(const PositionHistory *history, const Entities *ent)
{

    //Graphing was fucking harder than the math itself wtf? (yup I added graph as a second thought Hi!)
    Vector2 pivot = ent->pend[0].line.startPos;

    float range = ent->engine.l1 + ent->engine.l2;

    int oldest = (history->next - history->count + POSITION_HISTORY_LENGTH) % POSITION_HISTORY_LENGTH;

    for (int bob = 0; bob < 2; bob++) {
        int left = 20 + bob * (WIDTH / 2);
        
        Rectangle panel = { (float)left, HEIGHT - 290.0f, WIDTH / 2.0f - 40.0f, 270.0f };
        Rectangle plot = { panel.x + 60.0f, panel.y + 70.0f, panel.width - 80.0f, 160.0f };
        
        float middle = plot.y + plot.height / 2.0f;

        DrawRectangleRec(panel, Fade(DARKGRAY, 0.95f));
        DrawText(TextFormat("Bob %d position / samples (%d of %d)", bob + 1,
                            history->count, POSITION_HISTORY_LENGTH), left + 12, (int)panel.y + 12, 18, RAYWHITE);

        DrawText("X (pixels)", left + 12, (int)panel.y + 40, 18, SKYBLUE);
        DrawText("Y (pixels, down +)", left + 150, (int)panel.y + 40, 18, ORANGE);
        
        DrawRectangleLinesEx(plot, 1.0f, GRAY);
        DrawLineEx((Vector2){plot.x, middle}, (Vector2){plot.x + plot.width, middle}, 1.0f, GRAY);
        
        DrawText(TextFormat("+%.0f", range), left + 5, (int)plot.y, 16, LIGHTGRAY);
        DrawText("0", left + 35, (int)middle - 8, 16, LIGHTGRAY);
        DrawText(TextFormat("-%.0f", range), left + 5, (int)(plot.y + plot.height) - 16, 16, LIGHTGRAY);
        DrawText(TextFormat("-%.2f simulation s", (POSITION_HISTORY_LENGTH - 1) * HISTORY_SAMPLE_STEPS * PHYSICS_DT),
                 (int)plot.x, (int)(plot.y + plot.height) + 10, 16, LIGHTGRAY);
        DrawText("Latest sample", (int)(plot.x + plot.width) - 115,
                 (int)(plot.y + plot.height) + 10, 16, LIGHTGRAY);
        
        for (int i = 1; i < history->count; i++) {
            Vector2 previous = history->positions[bob][(oldest + i - 1) % POSITION_HISTORY_LENGTH];
            Vector2 current = history->positions[bob][(oldest + i) % POSITION_HISTORY_LENGTH];
            
            float x0 = plot.x + plot.width * (POSITION_HISTORY_LENGTH - history->count + i - 1) / (POSITION_HISTORY_LENGTH - 1);
            float x1 = x0 + plot.width / (POSITION_HISTORY_LENGTH - 1);
            float scale = plot.height / (2.0f * range);
            
            DrawLineEx((Vector2){x0, middle - (previous.x - pivot.x) * scale},
                       (Vector2){x1, middle - (current.x - pivot.x) * scale}, 1.5f, SKYBLUE);
            DrawLineEx((Vector2){x0, middle - (previous.y - pivot.y) * scale},
                       (Vector2){x1, middle - (current.y - pivot.y) * scale}, 1.5f, ORANGE);
        }
    }
}



State math(State s, Physics *eng) {
    State d;

    d.th1 = s.dTh1;
    d.th2 = s.dTh2;
    

    double num1 = -eng->gravity * (2*eng->m1 + eng->m2) * sin(s.th1)
                 - eng->m2 * eng->gravity * sin(s.th1 - 2*s.th2)
                 - 2 * sin(s.th1 - s.th2) * eng->m2
                   * (s.dTh2*s.dTh2*eng->l2 + s.dTh1*s.dTh1*eng->l1*cos(s.th1 - s.th2));
    double den1 = eng->l1 * (2*eng->m1 + eng->m2 - eng->m2*cos(2*s.th1 - 2*s.th2));
    
    d.dTh1 = (den1 != 0.0f) ? num1 / den1 : 0.0f;
    
    double num2 = 2 * sin(s.th1 - s.th2)
                 * (s.dTh1*s.dTh1*eng->l1*(eng->m1 + eng->m2)
                    + eng->gravity*(eng->m1 + eng->m2)*cos(s.th1)
                    + s.dTh2*s.dTh2*eng->l2*eng->m2*cos(s.th1 - s.th2));
    double den2 = eng->l2 * (2*eng->m1 + eng->m2 - eng->m2*cos(2*s.th1 - 2*s.th2));
    d.dTh2 = (den2 != 0.0f) ? num2 / den2 : 0.0f;
    
    return(d);
}

void rk4Step(Physics *eng, double dt) {
    State y0 = { eng->th1, eng->th2, eng->dTh1, eng->dTh2 };
    
    State k1 = math(y0, eng);
    
    State y1 = {
        y0.th1  + k1.th1  * dt * 0.5f,
        y0.th2  + k1.th2  * dt * 0.5f,
        y0.dTh1 + k1.dTh1 * dt * 0.5f,
        y0.dTh2 + k1.dTh2 * dt * 0.5f
    };
    State k2 = math(y1, eng);
    
    State y2 = {
        y0.th1  + k2.th1  * dt * 0.5f,
        y0.th2  + k2.th2  * dt * 0.5f,
        y0.dTh1 + k2.dTh1 * dt * 0.5f,
        y0.dTh2 + k2.dTh2 * dt * 0.5f
    };
    State k3 = math(y2, eng);
    
    State y3 = {
        y0.th1  + k3.th1  * dt,
        y0.th2  + k3.th2  * dt,
        y0.dTh1 + k3.dTh1 * dt,
        y0.dTh2 + k3.dTh2 * dt
    };
    State k4 = math(y3, eng);
    
    eng->th1  += (k1.th1  + 2.0f*k2.th1  + 2.0f*k3.th1  + k4.th1)  * dt / 6.0f;
    eng->th2  += (k1.th2  + 2.0f*k2.th2  + 2.0f*k3.th2  + k4.th2)  * dt / 6.0f;
    eng->dTh1 += (k1.dTh1 + 2.0f*k2.dTh1 + 2.0f*k3.dTh1 + k4.dTh1) * dt / 6.0f;
    eng->dTh2 += (k1.dTh2 + 2.0f*k2.dTh2 + 2.0f*k3.dTh2 + k4.dTh2) * dt / 6.0f;
    updateAccelerations(eng);
}

void updateAccelerations(Physics *eng)
{
    State derivative = math((State){eng->th1, eng->th2, eng->dTh1, eng->dTh2}, eng);
    eng->ddTh1 = derivative.dTh1;
    eng->ddTh2 = derivative.dTh2;
}


int setEnv(void)
{

    SetConfigFlags(FLAG_MSAA_4X_HINT);

    InitWindow(WIDTH, HEIGHT, TITLE);
    if (!IsWindowReady()) {
        return(-1);
    }

    if (FPS < 0 || FPS > 300) {
        SetTargetFPS(120);
    }
    else {
        SetTargetFPS(FPS);
    }

    return(0);
}
void updatePositions(Entities *ent)
{
    //Yeah I could'vce used arrays for thetas too to iterate everything with loops but...sun already arisen and I am half-dead
    ent->pend[0].line.endPos.x = ent->pend[0].line.startPos.x + ent->engine.l1 * sin(ent->engine.th1);
    ent->pend[0].line.endPos.y = ent->pend[0].line.startPos.y + ent->engine.l1 * cos(ent->engine.th1);
    ent->pend[0].ball.pos     = ent->pend[0].line.endPos;

    ent->pend[1].line.startPos = ent->pend[0].ball.pos;
    ent->pend[1].line.endPos.x = ent->pend[1].line.startPos.x + ent->engine.l2 * sin(ent->engine.th2);
    ent->pend[1].line.endPos.y = ent->pend[1].line.startPos.y + ent->engine.l2 * cos(ent->engine.th2);
    ent->pend[1].ball.pos     = ent->pend[1].line.endPos;
}
