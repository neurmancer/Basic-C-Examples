#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h> //for tolower()
#include <unistd.h>


        //Please just see how input buffer gets handled and learn using tolower() and DO FUCKING NOT handle the logic like me it's 23.30 and my buffer is long overflown

int main(void)
{

    srand(time(NULL));  //May the RNGsus give his seed to us
    char *arr[] = {"Rock","Paper","Scissors"};
    
    
    while (1)
    {   
        int computerInput = rand() % 3;
        int realGet = computerInput;
        if (computerInput == 2)
        {
            computerInput = -1;
        }
        
        int playerInput = 0;
        char buffer[10];
        printf("Rock, paper, scissors?");
        fflush(stdout);
        if (scanf(" %s",buffer) < 0)
        {
            printf("Bro try not to be dumb.\n");
            int c;
            while ((c = getchar()) != '\n' && c != EOF) { } //Don't worry that just clearing input buffer before exit 
            return(-1);
        }
        printf("%s\n",buffer);
        buffer[0] = tolower(buffer[0]);
        if (buffer[0] == 'r')
        {
            playerInput = 0;
        }
        else if (buffer[0] == 'p')
        {
            playerInput = 1;
        }
        
        else if (buffer[0] == 's')
        {
            playerInput = -1;
        }
        else
        {
            printf("Try entering something useful next time?\n");
            return(-2);
        }

        printf("You:%s\nAI(definitly not RNGsus):%s\n",buffer,arr[realGet]);
        sleep(2);

        if (playerInput == computerInput)
        {
            printf("Tie bitch\n");
        }

        else if (arr[computerInput+1] == arr[playerInput] || playerInput == -1 && computerInput == 1)
        {
            printf("You won...yeah\n");
        }
        else {printf("You lost sucker\n");}
        printf("\nWanna try again (y/n): ");
        fflush(stdout);
        if(scanf(" %s",buffer) < 0) {int c; while((c = getchar() != '\n' && c != EOF)){ }}
        switch (buffer[0])
        {
        case 'n':
            return(0);
            break;
        
        default:
            printf("\033[H\033J");
            break;
        }
    }

    return(0);
}