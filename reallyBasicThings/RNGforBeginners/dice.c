#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
/*This program gets user input for desired dice amount and sums it in a while loop I do know for loop would be more appropraite 
but I use while less so I need to try new things too don't judge or do IDC. And yeah I am a passive-agressive person so what? At least you smirk when you learning C 
That's unusal among segfaults (Tho I have a .c file for bending segfaults or their knees called important.c but it needs load shit before starting so be patient with it)
*/


int main(void)
{
    srand(time(NULL)); //Classical seed thingy
    int dices = 0; //even tho scanf will overwrite it declaring AND assigning shit to 0 is a good practive avoiding garbage data usually.Keep it in mind
    int sum = 0;
    printf("How many D6 you wanna roll you little gambler(pleaase dont say -1 or 99999999):");
    fflush(stdout);
    scanf("%d",&dices);
    while (dices != 0)
    {
        int roll = (rand() % 6)+1; //Use bracelets don't trust computers computing orders Sun Tzu (or Linus Torvalds IDK) 
        sum += roll;
        printf("Your roll:%d\n",roll);
        dices--; //Decrease it 
    }

    printf("Total:%d\n",sum);

    return(0);
}