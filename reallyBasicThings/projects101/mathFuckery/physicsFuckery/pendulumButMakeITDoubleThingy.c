/*
                ========================== YAPPING =======================

                'Sup? It's 3 AM and I wonder what if I were to add another ball to the pendulumThingy? we're here to find out 
                Welcome to yet another physics fuckerys 

                well my first idea was more PI gamba using Leibniz series (yk the series) or Basel Problem (which Euler proved that it converges pi^2 / 6) 
                for CLI instead of graphics but I thought that I abondoned physics fuckery for a while now....
                So we start with more balls

                This shit here because I found out this cool graph in MIT's website: https://web.mit.edu/jorloff/www/chaosTalk/double-pendulum/double-pendulum-en.html



                and I may add the graphs too but no promises 


                and lol as always this is a template for now....

*/




/* ======================= INCLUDES =================== */

#include <raylib.h>
#include <stdio.h>
#include <math.h>


/* ======================= DEFINES ======================= */

#define WIDTH 1280
#define HEIGHT 960
#define TITLE "Strings and Balls Thingy"

#ifndef FPS 
    #define FPS 120
#endif

//Color defines
#define SHE_LOVES_PURPLE CLITERAL(Color){191, 0, 255,255}
#define SO_DO_I CLITERAL(Color){153, 102, 204,255}

// Object defines
#define BALL_RADIUS (13.53f)
#define LINE_THICKNESS (3.5)

/* ====================== OBJECTS ============================= */


typedef struct{
    //Well...what should I put here again?

    float th1, th2; //Theta 1 and theta 2 (angles) (btw I'll be following the notation given below)
    float dTh1, dTh2;   //First deriv. of angles (angular velo)
    float ddTh1, ddTh2; //Second deriv of angles (first deriv of angular vel (angualar accel))
    
    float m1,m2;    //Masses
    float l1,l2;    //Rod lengths  
    float gravity; //You know what gravity is right? 

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

//and here is the fun shit... wtf fuck is the formula
/*

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
void math(Physics *eng);
int setEnv(void);


int main(void)
{
    if (setEnv()) { perror("Blame raylib bruh"); return(-53); }


    Config cfg = { 
        .pendCfg[0].ball.color = SHE_LOVES_PURPLE,
        .pendCfg[0].ball.pos = { 0 },
        .pendCfg[0].ball.radius = BALL_RADIUS,
        .pendCfg[0].line.startPos = (Vector2){(float)WIDTH/2, (float)HEIGHT/3},
        .pendCfg[0].line.endPos = { 0 },
        .pendCfg[0].line.color = SO_DO_I,
        .pendCfg[1].ball.color = SO_DO_I,
        .pendCfg[1].ball.pos = { 0 },
        .pendCfg[1].ball.radius = BALL_RADIUS,
        .pendCfg[1].line.startPos = (Vector2){(float)WIDTH/2, (float)(2*HEIGHT)/3},
        .pendCfg[1].line.endPos = { 0 },
        .pendCfg[1].line.color = SHE_LOVES_PURPLE,
        .engineCfg = { 0 },
        .engineCfg.gravity = 9.8f,
        .engineCfg.l1 = 90.f,
        .engineCfg.l2 = 53.13f,
        .engineCfg.m1 = 30.f,
        .engineCfg.m2 = 15.f,        
    };

    Entities objs = { 0 };

    setStage(&objs, &cfg);

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_ESCAPE)) { break; }
 
        BeginDrawing();
        ClearBackground(BLACK);
        drawThingies(&objs);
        EndDrawing();
    }


    CloseWindow();
    return(0);
}

void setStage(Entities *ent, Config *cfg)
{
    ent->engine = cfg->engineCfg;
    for (int i = 0; i < 2; i++) {
        ent->pend[i] = cfg->pendCfg[i];
    }
    ent->pend[0].line.len = ent->engine.l1;
    ent->pend[1].line.len = ent->engine.l2;
}

void drawThingies(Entities *ent)
{
    //TO future me: Please separate(and yeah I finally learned how to spell separate) this shit from draw function current me fucking function purity 
    ent->pend[0].line.endPos = (Vector2){ent->pend[0].line.startPos.x + ent->pend[0].line.len * sinf(ent->engine.th1),
    ent->pend[0].line.startPos.y + ent->pend[0].line.len * cosf(ent->engine.th1)};
    ent->pend[0].ball.pos = ent->pend[0].line.endPos; //the line linked exactly to the center of the ball for now(might change)

    ent->pend[1].line.startPos = ent->pend[0].ball.pos;
    ent->pend[1].line.endPos = (Vector2){ent->pend[1].line.startPos.x + ent->pend[1].line.len * sinf(PI/6),
    ent->pend[1].line.startPos.y + ent->pend[1].line.len * cosf(PI/12)};
    ent->pend[1].ball.pos = ent->pend[1].line.endPos; //the line linked exactly to the center of the ball for now(might change)


    
    for (int i = 1; i >= 0; i--) {
        //To 
        DrawLineEx(ent->pend[i].line.startPos, ent->pend[i].line.endPos, 3.5f, ent->pend[i].ball.color);
        DrawCircleV(ent->pend[i].ball.pos, ent->pend[i].ball.radius, ent->pend[i].ball.color);
    }
}

void math(Physics *eng)
{
    //Bruh...this feels like defusing a bomb...one misplaced parenthesis and your sim is fucked
    //any future reader: those are text substitues if you don't know what that implies please do not fuck with defines
    #define NUMARATOR (-eng->gravity*((2*eng->m1+eng->m2)*sinf(eng->th1) - eng->m2*eng->gravity*sinf(eng->th1-2*eng->th2) - 2*sinf(eng->th1 - eng->th2) * eng->m2*(eng->dTh2*eng->dTh2*eng->l2 + eng->dTh1*eng->dTh1*eng->l1*cosf(eng->th1 - eng->th2))))
    #define DENOMINATOR (eng->l1 * (2*eng->m1+eng->m2-eng->m2*cosf(2*eng->th1-2*eng->th2)))
    if (!DENOMINATOR) {
        return;
    }
    eng-> ddTh1 = NUMARATOR / DENOMINATOR;  //FUUUUUUUUUUUUUUUUUUUUUUUUCK

    #undef NUMARATOR
    #undef DENOMINATOR
}

int setEnv(void)
{

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

