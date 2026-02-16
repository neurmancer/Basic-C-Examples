#include <stdio.h>
#include <stdlib.h>
#include <time.h> //Won't be explaining those again check coinflip.c for srand and time

int main(void)
{
    srand(time(NULL));
    int victoriasSecret = rand() % 100; //gives 0-100 random number
    int guesses;
    //I am bad at var naming srry > /// <
    int win = 0;
    for (int i = 3; i > 0; i--) //giving 3 tries to user
    {   
        ; //To check the situatin out of the loop
        printf("You have %d remaining guesses\n",i);
        printf("Try a number 0-100:");
        fflush(stdout);
        scanf("%d",&guesses);
        if (guesses == victoriasSecret)
        {
            printf("You guessed correct at your %d.try\n",3-i);
            win = 1;
            break;
        }
        else
        {
            if (guesses > victoriasSecret)
            {
                printf("You are too far gone\n");
            }
            else
            {
                printf("Scale up a little\n");
            }
        }
    }    

    if (!win)
    {
        printf("The number was :%d\n",victoriasSecret);
    }
    

    return(0);
}