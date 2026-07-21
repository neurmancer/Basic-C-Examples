
/*
        Sup? you 'member my second best idea to approixmate pi in dftThingy.c? Today we're doing that visually for no reason despite having fuck ton of things in futureShit.md
        Yeah that's a muse-driven one...

        So for the people who don't know what's buffon's needle:
        It is a classic geometric probability experiment used to estimate the value of PI by dropping a needle onto a sheet of lined paper but I'll cheese my way a little
        with a 'presumption' which is assuming the P = (2L)/(π·2L) (we're taking D = 2L) so we can simply do P = 1/π or 1/P = π. But this is a **SPECIAL CASE**
        I know and I'm simplifying it 

        Here's a good demonstration, explanation and a SIMULATION by University of Illinois Urbana-Champaign : https://mste.illinois.edu/activity/buffon/
        and for the people saying 'Neuro you ain't citing your resources properly' I do know... I am just showing you a way I am like a pointer just holding address 
        you gotta check the address for the information and how many times you've seen any citation in source code besides mine in a learning repo?Lulz

        And that's how I am gonna remember some math...since right now I don't know how to rotate a fixed size line to 'simulate' random needle drops on the 'paper' 
        probably I'll use cos and sin as always but question is: In which cursed ways?
        
        I guss I found out... I mean rotation is just x' = x + r*cos(x) and y' = y + r*sin(x) right? RIGHT? I mean I can do that...but real question is:
        DO I NEED GRAVITIY simulation to drop the needles? or just nah?...Damn...

        And yeah this's gonna use raylib.h for visualization (so compile with -lraylib -lm  and have it installed in your system) but as always Imma leave this as a template
        since I Got shit to do beforehand and this is gonna be a quickie...


        Man I really can't start to work on something without defining the problem (and investigating) first in a huge comment...

            For the record I'll be using DEG2RAD for readibilty even tho I wanna do (M_PI/180.f * rand() % 360) but that's exactly what DEG2RAD does

            What I need to do
            0- Create the needle using trigo fuckery 
            1-Draw needles on the screen A4 
            2- compute the ratio 
            3- Show the ratio under the M_PI constant (which is our reference)
            4- Clear the screen partially to print the new estimation (probably with 0.1 interval between each drop)
            5-Repeat up until UINT_MAX lol 

            Now...how the fuck I can calculate the lines x values won't change (since lines will be separeted on y-axis)
            p1.x and p2.x will be same for each line... and p1 and p2 will be different for each line but will same for the same line
             
            Man I hate analitical geometry I HATE GEOMETRY IN GENERAL
            
*/

/* =================== INCLUDES ================ */

/* Neat headers */


#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
/*  Headers that requires flags */
#include <math.h>    //To math.
#include <raylib.h>  //For making my life easier

/* ==================== DEFINES ================== */

#define WIDTH 1200.0
#define HEIGHT 900.0
#define FPS 120 //I am starting to get used this 120 thing my monitor is 180Hz I should be using that but...

#define LINE_AMOUNT 10 //10's good..we have 10 fingers, we use decimal, it's 2*5 both prime
#define FONT_SIZE 35

/* ============== OBJECTS ==================== */


typedef struct{

    Vector2 p1; //Starting point: x1,y1
    Vector2 p2; //Second point: x2,y2
    //Yeah I noted those since I Fucking forget after closing the file
}Line;

/* ================== GLOBALS ================= */


/* =========== FUCNTION PROTOTYPES ============ */

void displayPI(void);

Line randomNeedleDrop(Vector2 rectSize, float needleLength);

int main(void)
{

    srand(time(NULL));

    InitWindow(WIDTH, HEIGHT, "PI THAT TAKES AN ETERNITY");
    if(!IsWindowReady()) { return(-1); } 
    
    SetTargetFPS(FPS);

    Vector2 rectSize = (Vector2){WIDTH/3,(WIDTH/3)*sqrtf(2.0)}; //The ususal ratio of A4 1/sqrt(2) which I CAN'T FORGET FOR SOME FUCKING REASON
    Vector2 rectPos = (Vector2){WIDTH/2-rectSize.x/2, HEIGHT/2-rectSize.y/2};
    if (LINE_AMOUNT == 0) { return(-2); /*0 division check*/}
    
    const float distance = rectSize.y / LINE_AMOUNT;
    const float needleLength = distance/2.0f;
    

    Line lines[LINE_AMOUNT] = { 0 };     //TO make my job easier with collision detection
    
    for (int i = 0;i < LINE_AMOUNT;i++) {
        lines[i].p1 = (Vector2){rectPos.x,(rectPos.y+(i*distance))}; //Is that casting? I mean I am using the (Vector2) and (Line) thing but I feel like that's something different than (float) or (int *)
        lines[i].p2 = (Vector2){(rectPos.x+rectSize.x),(rectPos.y+(i*distance))};
        //It's time for the blind faith babyy
    }
    
    BeginDrawing();
    ClearBackground(BLACK);
    DrawRectangle(rectPos.x, rectPos.y, rectSize.x,rectSize.y, BEIGE); //I Guess it's centered now... 
        
    EndDrawing();

    unsigned int needleDropCount = 0;
    unsigned int intersectionCount = 0;
    unsigned int iter = 0; //Lmfao that's not gonna end but yeah we're still being careful about overflow
    
    float estimatedPI = 0;

    while (!WindowShouldClose() && iter <= UINT_MAX) {
        if (IsKeyPressed(KEY_ESCAPE)) { CloseWindow(); }
        needleDropCount++;
        Line needle = randomNeedleDrop(rectSize,needleLength);
        needle.p1.x += rectPos.x;
        needle.p1.y += rectPos.y;
        needle.p2.x += rectPos.x;
        needle.p2.y += rectPos.y;

        bool intersection = false; //Yeah I am now a readibilty gremlin...except the ternary operation below lol 

        // Collision parameters? I guess...
        float maxY = (needle.p1.y > needle.p2.y) ? needle.p1.y : needle.p2.y;
        float minY = (needle.p1.y < needle.p2.y) ? needle.p1.y : needle.p2.y;

        for (int i = 1;i < LINE_AMOUNT;i++) {
            float lineY = lines[i].p1.y;

            if (lineY >= minY && lineY <= maxY) {
                intersection = true;
                intersection++;
                break;
            }
        }

        estimatedPI = (float) needleDropCount/(float) intersectionCount;

        BeginDrawing(); //Lol...I've done everything except math

        displayPI();
        for (int i = 1; i < LINE_AMOUNT;i++) {
            DrawLineEx(lines[i].p1, lines[i].p2,2.0, PURPLE); // Dev blog: YOLO        
            //Won't use the upper edge of paper as a collision part and won't use the lower edge either so starting from 1 
            //Check collision accordingly (besides...does thickness fuck with probabilty? Please don't...)
        }
        
        DrawLineEx(needle.p1,needle.p2,2,GREEN);

        if (intersection) {
            DrawLineEx(needle.p1, needle.p2, 2, RED);
        }

        else {
            DrawLineEx(needle.p1, needle.p2, 2, GREEN);
        }

        EndDrawing();
        iter++;
    }

debug: 

    return(0);
}


void displayPI(void)
{
        DrawText(TextFormat("PI : %.48lf",PI),  32, 10, FONT_SIZE, BEIGE); //Using PI or M_PI is me admiting defeat...
}

Line randomNeedleDrop(Vector2 rectSize,float needleLength)
{
    Line needlePos = { 0 };
    needlePos.p1.x = ((float)rand() / RAND_MAX)*rectSize.x;
    needlePos.p1.y = ((float)rand() / RAND_MAX)*rectSize.y;

    float rangle = ((float)rand() / RAND_MAX)*180;
    rangle *= DEG2RAD; //Converting to radians
    //Random+angle = rangle (yeah addition works on words too) 
    needlePos.p2.x = needlePos.p1.x + needleLength*cosf(rangle);
    needlePos.p2.y = needlePos.p1.y + needleLength*sinf(rangle);
    
    return(needlePos);
}
