#include <stdio.h>
#include <unistd.h>

/*      I was doom scrolling and saw this https://www.instagram.com/p/DTVXyKlDh0s/ video about Koch Curve and couldn't help myself. so here we are trying to implement 
        Idea is getting a 0-n range(where n is a positive integer) and summing 1 bits in it (so I'll use my old function that I build for K&R repo )
        https://github.com/neurmancer/K-R-Examples (you can check if you wonder) and then if '1' bit count is even we move straight one unit and if odd we rotate 60 degrees counter-clockwise
        (or positive rotation you nerds)

        Normally I gotta visulize that but this is my 13th day of programming and I couldn't think of a way to rotate display for visulization on CLI

*/


int countBits(unsigned int number);

typedef struct{
    int delta;
    int angle;
}Line;

int main(void)
{
    Line line = {0,0}; 

    for (int i = 0; i < 64; i++)
    {
  
        if (countBits(i) % 2 == 0)
        {
            line.delta;
            printf("Moved straight\n");

        }
        else
        {
            line.angle+=60;
            printf("Rotated 60 degrees.\tCurrent angle: %d\n",line.angle);
        }
        if (line.angle >= 360)
        {
            line.angle = line.angle % 360; // Keeping it periodic
        }
        sleep(1);
    }
    return(0);
}



int countBits(unsigned int number)
{
    int upBits = 0;
    while (number != 0)
    {
        number &= (number-1);       //This will erase rightmost 1 bit every time (really tho if you interested check 2-9 in K&R repo)
        upBits++;
    }
    return(upBits);
}