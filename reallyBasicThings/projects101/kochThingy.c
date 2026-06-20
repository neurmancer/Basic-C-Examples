/*  Includes    */


#include <stdlib.h> //For malloc and free
#include <raylib.h> //For everything?
#include <stdio.h> //For moral support
#include <math.h> //For math...yk

/*  Defines     */
#define WIDTH 1200.0f
#define HEIGHT 800.0f
#define FPS 60

#define MOVEMENT_UNIT 0.5f


/*              Sup? You know the tea...Got bored, thought something now I must implement...The usual fuck around and find out thing        

                This is here as a template for now...  
                For the uninitated (or how tf u spell it) I have file called BitWizardy.c in experimenting subfolder where I tried to visulize Koch's Snowflake with Thue-Morse sequence
                Except the visulization part since it was my 13th day of programming so here we are finishing the shit that I've started out of passion but problem is...I forgot the instructions
                and refuse to check again lol...MY BRAIN GONNA GIVE IT BACK TO ME

                And this file is where we split our ways with Beckett since this file is where Godot arrives...

                Here is the video I encountered this at first : https://www.instagram.com/p/DTVXyKlDh0s/
                And here is the wikipedia page for more : https://en.wikipedia.org/wiki/Thue–Morse_sequence (I haven't checked myself yet so...you are on your own in this one)

                The Idea is simply:
                    1-Lay numbers out up until a fixed number (non-negative) 
                    2- Get the binary interpretation for each number upto the fixed number
                    3-Sum the up beats or 1 bits in the number 
                the even move, odd rotate 60 degrees counter-clockwise(or towards positive for you trigo nerds)



                Now the question is how the fuck can I implement consecutive steps of the koch snowflake only with a DrawLine() and a dream? 
                    First, I need an angle for 60 degree turns and for the sake of not typing degree fuck ton of times I'll use radiant and if you don't know 60 degress = PI/3
                        I mean I got 2 points one beginning and one end... I gotta keep the turn angle in a var to calculate the next point's hypothenus 
                    void DrawSplineLinear(const Vector2 *points, int pointCount, float thick, Color color);    found a function like that in raylib.h Vector2 * is probably an array of vectors which is exactly what I need


                I had failed math in highschool anyways lol... 

*/


unsigned int popCount(unsigned int x); //This is bitsy mathematical part 
Vector2 *calculationShit(Vector2* array, unsigned int arrSize,unsigned int startIndex); //I'll definitely rename that...



int main(void)
{

    /*Declaration*/
    Vector2 *instructions = NULL; //Yup classic me being defensive yk
    unsigned int instructionSize = 512;
    
    instructions = (Vector2 *)malloc(sizeof(Vector2)*instructionSize);
    if (instructions == NULL) {perror("Allocation fuck up occured\n"); return(-1);}
    instructions[0] = (Vector2){WIDTH/2,HEIGHT/2}; //Starting point
    unsigned int start = 1;
    
    
    //Setting up the window and OpenGL(at least that's what I heard from raylib) 
    InitWindow(WIDTH, HEIGHT, "Koch Thingy");
    if (!IsWindowReady()) {perror("Something bad occured\n"); return(-1);}
    SetTargetFPS(FPS);

    instructions = calculationShit(instructions,instructionSize,1);

    while (!WindowShouldClose()) {
        
        if(IsKeyPressed(KEY_ESCAPE)){CloseWindow();}



        BeginDrawing();
        ClearBackground(BLACK);
        DrawSplineLinear(instructions, instructionSize, 2.0f,WHITE); //If that works I'll cal it a night...it's 1.42 AM (lol Dough Adams reference yeah...)
        EndDrawing(); 
    }

    

    return(0);
}



unsigned int popCount(unsigned int x)
{
    unsigned int upBits = 0; //Yeah I am not giving up my Up 'beat' joke
    while (x != 0) {
        x &= (x-1); //Brian Kernighan's trick for flipping the rightmost '1' off (pun intended) (and yeah after 'reinventing' it in Bitwizardy.c I learned the proper name of the guy) 
        upBits++;
    } //Honest take? This trick is so elegant in my opinion... 
    return(upBits);
}
 
/*

Vector2 *calculationShit(Vector2* array,unsigned int arrSize,unsigned int startIndex)
{

    for (int i = startIndex;i < arrSize;i++) {
        int flag = 0;        
        
        if (popCount(i) % 2) {
            if (flag) {
                array[i].x = array[i-1].x+TURNED_POINT;
            }
            else {
                array[i].x = array[i-1].x+MOVEMENT_UNIT;
            }
            flag = 0;
        }
        else {
            int flag = 1;
        }
    }

    return(array);
}

This function is indeed a crime against humanity...leaving a template for tomorrow's plan

NOTE TO FUTURESELF: USE FUCKING TRIG FUNCS YOU IDIOT 

if (t == 0) {
            // MOVE
            pos.x += cosf(angle) * STEP_SIZE;
            pos.y += sinf(angle) * STEP_SIZE;
            points[pointIndex++] = pos;
        } else {
            // TURN only
            angle += TURN_ANGLE;
        }
    }

*/ 