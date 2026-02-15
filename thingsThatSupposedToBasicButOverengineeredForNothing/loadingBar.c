#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int main(void)
{
    srand(time(NULL));
    setvbuf(stdout,NULL,_IONBF,0);
    printf("\033[H\033[J");
    int x = 0;
    while (1)
    {
        x = rand() % 250;
        printf("Loading");
        usleep(534567);
        printf(".");
        usleep(534565);
        printf(".");
        usleep(534564);
        printf(".");
        usleep(534563);

        if (x % 11 == 0) //              Well...I could use switch-case only had I known I would...bro trust me I am at page 43 of K&R not there yet.
        {
            printf("\033[H\033[J");
            printf("Estimated Time Remaining is:IDK lulz");
            sleep(1);
        }
        
        else if (x % 7 == 0)
        {
            printf("\033[H\033[J");
            printf("JACKPOT BABYYYYYY");
            sleep(1);
        }
        
        else if (x % 13 == 0)
        {
            printf("\033[H\033[J");
            printf("Python sux");
            sleep(1);
        }

        else if (x % 53 == 0)
        {
            printf("\033[H\033[J");
            printf("Yeah I only selected niche prime numbers deal with it");
            sleep(1);
        }

        else if (x % 31 == 0)
        {
            printf("\033[H\033[J");
            printf("Yeah I only selected niche prime numbers deal with it");
            sleep(1);
        }
        printf("\033[H\033[J");
    }
    
    return(0);
}