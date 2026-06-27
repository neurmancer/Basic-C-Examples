/*  Includes    */


#include <stdlib.h> //For malloc and free
#include <raylib.h> //For everything?
#include <stdio.h> //For moral support
#include <math.h> //For math...yk

/*  Defines     */
#define WIDTH 1600.0f
#define HEIGHT 1200.0f
#define FPS 120 //I guess 120 is the sweet-spot or I can make this dynamic in the future for V-Sync type shit

#define TURN_ANGLE (M_PI/3)
#define BUFFER_COFACTOR 2

float STEP_SIZE = 22.5f;


/*              Sup? You know the tea...Got bored, thought something now I must implement...The usual fuck around and find out thing        

                This is here as a template for now...  
                For the uninitated (or how tf u spell it) I have file called BitWizardy.c in experimenting subfolder where I tried to visulize Koch's Snowflake with Thue-Morse sequence
                Except the visulization part since it was my 13th day of programming so here we are finishing the shit that I've started out of passion but problem is...I forgot the instructions
                and refuse to check again lol...MY BRAIN GONNA GIVE IT BACK TO ME (yeah I am terry davis'ing my way to knowledge if you can't tell)

                And this file is where we split our ways with Beckett since this file is where Godot arrives...

                Here is the video I encountered this at first : https://www.instagram.com/p/DTVXyKlDh0s/
                And here is the wikipedia page for more : https://en.wikipedia.org/wiki/Thue–Morse_sequence (I haven't checked myself yet so...you are on your own in this one)

                The Idea is simply:
                    1-Lay numbers out up until a fixed number (non-negative) 
                    2- Get the binary interpretation for each number upto the fixed number
                    3-Sum the up beats or 1 bits in the number 
                the even move, odd rotate 60 degrees counter-clockwise(or towards positive for you trigo nerds)

                As always Important Shit To Know:
                    
                    1- ESCAPE FOR...esacpe yk...
                    2- This program is frame-rate dependent sicne there is no abstraction involved so you'll get 120 iterations a second at max you may tweak your FPS yourself 
                    3- Math was correct since last time I've checked...
                    4- *Probably* Memory safe since I couldn't run valgrind due to some problems I couldn't resolve UnU
                    5- And this project is finished...thx for checking anyways  

                    6-Controls are: ESC to close the window (hence end the program) And scroll up/down for zoom in/out



                Now the question is how the fuck can I implement consecutive steps of the koch snowflake only with a DrawLine() and a dream? 
                    First, I need an angle for 60 degree turns and for the sake of not typing degree fuck ton of times I'll use radiant and if you don't know 60 degress = PI/3
                        I mean I got 2 points one beginning and one end... I gotta keep the turn angle in a var to calculate the next point's hypothenus 
                    void DrawSplineLinear(const Vector2 *points, int pointCount, float thick, Color color);    found a function like that in raylib.h Vector2 * is probably an array of vectors which is exactly what I need


                I had failed math in highschool anyways lol... 

                This is my experimenting part and where I pull funcs from raylib.h to dissect before I use

                RLAPI bool IsWindowFullscreen(void);                              // Check if window is currently fullscreen
                RLAPI void ToggleFullscreen(void);                                // Toggle window state: fullscreen/windowed, resizes monitor to match window resolution


                For resizing the size of drawing I stole this from rcore.c from their srcs lol 

                float GetMouseWheelMove(void)
                    {
                        float result = 0.0f;

                        if (fabsf(CORE.Input.Mouse.currentWheelMove.x) > fabsf(CORE.Input.Mouse.currentWheelMove.y)) result = (float)CORE.Input.Mouse.currentWheelMove.x;
                        else result = (float)CORE.Input.Mouse.currentWheelMove.y;

                        return result;
                    }


                    Known Weaknesses:
                        1-Calculates the fractions from ground-up with each space(resize) instead of storing it 


*/


/*   Function Declarations            */

unsigned int popCount(unsigned int x); //This is bitsy mathematical part 
Vector2 *instructor(Vector2 *arr, int *arrSize, int maxSteps);
Vector2 *reallocator(Vector2 *arr,int *currentSize);


/*      Global Vars     */

float angle = 0.0f;
int pointIndex = 0;
int resizeCount = 0;

int main(void)
{

    /*Declaration*/
    Vector2 *instructions = NULL; //Yup classic me being defensive yk
    
    int instructionSize = 256;
    int maxSteps = 512; // crank this shit up
    

    
    instructions = (Vector2 *)malloc(sizeof(Vector2)*instructionSize);
    if (instructions == NULL) {perror("Allocation fuck up occured\n"); return(-1);}
    Vector2 *root = instructions; //For a few reasons first... I may need reallocate that in the future so I don't wanna ditch the memory and I'll probably use the first pointer to walk instead of arr[i] notation
    instructions[0] = (Vector2){(2*WIDTH)/3,HEIGHT/2}; //Starting point
    

    int iter = 1; //To iterate over the array to draw one more line each frame 

    //Setting up the window and OpenGL(at least that's what I heard from raylib) 
    InitWindow(WIDTH, HEIGHT, "Koch Thingy");
    if (!IsWindowReady()) {perror("Something bad occured\n"); return(-1);}
    SetTargetFPS(FPS);
    if (!IsWindowFullscreen()) { ToggleBorderlessWindowed(); }
    instructions = instructor(instructions, &instructionSize, maxSteps);
    
    while (!WindowShouldClose()) {
        
        if(IsKeyPressed(KEY_ESCAPE)){ CloseWindow(); }
        if(IsKeyPressed(KEY_SPACE))
        {   
            iter = 0;
            angle = 0.0f;
            maxSteps *= BUFFER_COFACTOR;
            if (STEP_SIZE > 0.5f) {
                STEP_SIZE -= 0.75;
            }

            instructions = reallocator(instructions,&instructionSize);
            
            if(instructions == NULL){ perror("reallocation fucked up so I close the window\n") ; CloseWindow(); } //And this is the exact reason for keeping root in a separete var for me 
            
            root = instructions;
            instructions = instructor(instructions, &instructionSize, maxSteps);
            resizeCount++;
            WaitTime(0.25); //Wait for quarter of a second with each space so you don't fuck your heap spamming SPACE 
        }
        float resizeFactor = GetMouseWheelMove();  //Nice! it returns 1 for upscroll and -1 for downscroll

        BeginDrawing();
        ClearBackground(BLACK); //Damn all of the if else chain occured in a flow-state I didn't even comment on anything so this is meta-narration
        if (resizeFactor > 0.0f && STEP_SIZE < 250.0f) {
            
            STEP_SIZE += 1.5f;
            
            resizeFactor = 0;
            
            angle = 0;
            instructions = instructor(instructions, &instructionSize, maxSteps);
        }

        else if(resizeFactor < 0.0f && STEP_SIZE > 0.5f)
        {
            
            STEP_SIZE -= 1.5f;   
            if (STEP_SIZE < 0.0f) {
                break;
            }

            resizeFactor = 0;
            
            angle = 0;    
            instructions = instructor(instructions, &instructionSize, maxSteps);
        }
        else {
            DrawSplineLinear(instructions, iter, 2.25f,WHITE); //If that works I'll cal it a night...it's 1.42 AM (lol Douglas Adams reference yeah...)
        }
        EndDrawing(); 
        if (iter < pointIndex) {iter++;}
    }

    
    free(root);
    instructions = NULL;
    root = NULL; //it reaches here if you terminate window via using ESC so it SHOULD clear everything before dipping out 
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
 




Vector2 *instructor(Vector2 *arr, int *arrSize, int maxSteps)
{
    if (arr == NULL) { return(NULL); }

    Vector2 pos = arr[0];  // start position
    pointIndex = 1;

    for (unsigned int n = 0; n < (unsigned int)maxSteps && pointIndex < *arrSize; n++) {
        unsigned int t = popCount(n);
        
        if (t % 2 == 0) {
            pos.x += cosf(angle) * STEP_SIZE; //Trigonometry...man even that confuses me
            pos.y += sinf(angle) * STEP_SIZE;
            
            if (pointIndex < *arrSize) {
                arr[pointIndex] = pos;
                pointIndex++;
            }
        } else {
            //CCW turn
            angle += TURN_ANGLE;
        }
    }
    return(arr); 
}


Vector2 *reallocator(Vector2 *arr,int *currentSize)
{
    if (arr == NULL) {
        arr = malloc(256*sizeof(Vector2));
        if (arr == NULL) {perror("Allocation error\n"); return(NULL); }    
        return(arr);
    }
    (*currentSize) *= BUFFER_COFACTOR;
    Vector2 *temp = realloc(arr,sizeof(Vector2)*(*currentSize));
    if (temp == NULL){perror("You don't have enough RAM TnT\n"); return(NULL);}
    arr = temp;

    return(arr);
}