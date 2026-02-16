#include <stdio.h> //For prinft/scanf 
#include <stdlib.h> //For rand()
#include <time.h> //to give srand(time(NULL)) to get RNG instead of same number back to back

int main(void)
{
    srand(time(NULL));      //seed random
    int result = rand() % 2; //It will give us 0 or 1 

    if (result) //or rand == 1;
    {
        printf("HEADS\n");
    }
    else
    {
        printf("TAILS\n");
    }
    printf("\n\n\n"); //This time takes input before result
    
    result = rand() % 2; //Roll again and update so get new result
    printf("%d",result);

    char guess;
    printf("Heads or tails?(H/T) :");
    fflush(stdout); //Forces printf to print befor scanf
    scanf("%c",&guess);
    int answer;
    switch (guess)
    {
    case 'H':
        answer = 1;
        break;
    default:
        answer = 0;
        break;
    }
 
    if (result == answer)
    {
        printf("Congrats you little gambler\n");
    }
    else
    {
        printf("Better luck next time\n");
    }
    //Improvement Idea...make this in a game loop using for and printing remaining guess chances (I'll be working on Shitty Jukebox.)
    return(0);  //Be like me kids use () with return like a 50 y.o. grumpy guy because C only talks to them. 
}