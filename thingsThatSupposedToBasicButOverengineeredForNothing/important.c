#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define LOOP_OF_FOR 484

void sigsegvHandler(int sig);

int main(void)
{
    srand(time(NULL));
    //Installing signal handler Yeah this repo teaches shit about what NOT TO DO.You're welcome.
    signal(SIGSEGV,sigsegvHandler);
    setvbuf(stdout,NULL,_IONBF,0); //Note to future me bro don't fucking underestimate buffer old me had been debugging for 15 mins just 'cuz he forgot that.
    char *s = "A";
    printf("\033[?25l");
    printf("\033[H\033[J");
    for (int i = 0; i <= LOOP_OF_FOR; i++)
    {
        if (i % 53 == 0)
        {
            printf("Loading super duper important shit that won't dox your search history to your crush's DMs\t");
            usleep(300000);
            for (int i = 0; i < 5; i++)
            {
                printf("|\b");
                usleep(175250);
                printf("/\b");
                usleep(175250);
                printf("—\b"); //Yeah I don't know how to do this longer with ASCII yet...
                usleep(175250); //This is the most hardcoded shit I've ever done probably but won't be last I swear
                printf("\\\b");
                usleep(175250);
                printf("|\b");;
                usleep(175250);
                printf("/\b");
                usleep(175250);
                printf("—\b");
                usleep(175250);
                printf("\\\b");
                usleep(175250);
            }
            printf("\033[H\033[J");
        }
        else
        {
            printf("Loading very important shit"); //Rule #1 of programming: Never trust a computer's computing way use bracelets. -Sun Tzu(or Linus Torvalds.)
            usleep(150000* ((rand() % 4)+1));
            printf(".");
            usleep(150000* ((rand() % 4)+1));
            printf(".");
            usleep(150000* ((rand() % 4) +1));
            printf(".");
            usleep(300000);
            printf("\033[H\033[J"); //I am pretty sure there is a better way to retur to start but that's the only way I know for now
        }

    
    }

    s[0] = 'a';
    fprintf(stderr,"FUCK\n");


    return(0);
}

void sigsegvHandler(int sig)
{
    printf("Oh fuck something ain't right\r");
    sleep(6);
    printf("I can feel it...end is coming for me\n");
    fflush(stdout);
    sleep(6);
    printf("\033[H\033[JSegmentation fault (core dumped)\n");
    printf("\033[?25h"); //Don't worry I didn't eat your cursor here it is...
    exit(1);
}
