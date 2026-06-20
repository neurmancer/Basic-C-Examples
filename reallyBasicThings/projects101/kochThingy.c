/*  Includes    */

#include <raylib.h>
#include <stdio.h>

/*  Defines     */
#define WIDTH 600.0f
#define HEIGHT 400.0f
#define FPS 60


/*              Sup? You know the tea...Got bored, thought something now I must implement...The usual fuck around and find out thing        

                This is here as a template for now...  
                For the uninitated (or how tf u spell it) I have file called BitWizardy.c in experimenting subfolder where I tried to visulize Koch's Snowflake with Thue-Morse sequence
                Except the visulization part since it was my 13th day of programming so here we are finishing the shit that I've started out of passion but problem is...I forgot the instructions
                and refuse to check again lol...MY BRAIN GONNA GIVE IT BACK TO ME


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


unsigned int popCount(unsigned int x); //This is mathematical part 


int main(void)
{


    InitWindow(WIDTH, HEIGHT, "Koch Thingy");
    if (!IsWindowReady()) {perror("Something bad occured\n"); return(-1);}
    SetTargetFPS(FPS);

    while (!WindowShouldClose()) {
        
        if(IsKeyPressed(KEY_ESCAPE)){CloseWindow();}



        BeginDrawing();
        ClearBackground(BLACK);
        DrawLine(5, 5, 9, 8, PURPLE); 
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
 