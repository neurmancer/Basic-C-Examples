#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/ioctl.h> //For ioctl() and getting winsize and shit
#include <time.h>
#include <signal.h>


/*ANSI DEFINES */
#define HIDE_CURSOR "\033[?25l"
#define RETURN_CURSOR "\033[?25h"      //Basic ANSI escape codes for hiding/showing cursor (l means low and h means high as you can guess)
#define WIPE_SCREEN "\033[H\033[J"
#define WALL_STRING "█" //That's not ANSI but you got the idea
#define RESET_COLOR   "\033[0m"
#define PAINT "\033[38;2;%d;%d;%dm%s" //Gets the RGB values and a string as parameters 
#define MOVE_CURSOR "\033[%d;%dH"

#define SECOND 1000000

/*

                                **This project is finished** (nah it's still broken I'll change the internal structure of flagging shit tomorrow (it's 1.37AM))


    This is gonna be as same as primeScreensaverThingy but for low-level gremlins (like me OwO)(and I use emoticons so much so what?Don't act like you didn't use mySpace)
    'Sup? it's almost 11PM so...you know...I flipped the questioning switch off and started coding
    
    We'll 'reimplement the primeScreensaverThingy for CLI interafaces so you can enjoy it without thinking about graphic libs... and let me get this clear...
    I don't wanna waste so much time on this file since it's lowkey against my don't do same thing twice philosphy (tho in Software Engineering it's called D.R.Y..Don't repeat yourself )
    I'll use ioctl for getting terminal size (yeah I am planning this shit on the way too so I don't even typed int main yet...) but I won't bother to resize the array for resizing the terminal
    since it'll require me to keep track of the already filled pixels, already filled array for flagged points on the screen etc. 
    So here is the deal: 
        Pls do not resize the window after starting the program UnU ...and for the record if you wanna use this I presume you want to see what's on screen...hence why resizing to break it?Right?
          
    and I intend to do the coloring with full ANSI fuckery so no external libs...no ncurse, no window just a colored 24-bit coloring with primes 

    and since the idea is same as the gui version most of the logic will be same too...just ported to CLI 


    and for the record: This program will be using Ctrl+C for exit with a custom handler...

    



*/

typedef struct{
    int x; 
    int y;


}point; //Slightly different logic this time



int isPrime(unsigned int *arr,unsigned int val);

point *fillTheArray(point *root,int width,int height);

void handleSIGINT(int sig);
void cleanUp(void);

/*Global vars cuz needed*/


unsigned int *primes = NULL;

point *points = NULL;


int main(void)
{
    setvbuf(stdout,NULL, _IONBF,0); //The prayer of a classical CLI tool... turning line buffering off
    printf(HIDE_CURSOR);


    struct sigaction sa = { 0 };
    sa.sa_handler = &handleSIGINT;
    sigaction(SIGINT,&sa,NULL); //I use sigaction because linux man page suggests this over signal() due to compability issues https://man7.org/linux/man-pages/man2/signal.2.html <- Here is why nerds

    if (atexit(cleanUp) != 0) { perror("At exit failed...you're probably leaking some memory TnT\n");return(-1); };

    srand(time(NULL) ^ getpid()); //Extra entorpy baby... sinec already use unistd for defines (STDOUT_FILENO,TIOCGWINSZ etc.)

    struct winsize window;

    ioctl(STDOUT_FILENO, TIOCGWINSZ,&window);


    const int width = window.ws_col;
    const int height = window.ws_row;

    int primeCount = 0;
    int targetCount = width*height;
    primes = (unsigned int *) calloc(targetCount+1,sizeof(unsigned int));
    if (primes == NULL) { return(-1) ; }
    unsigned int *iter = primes; //To not to loose the root again...

    points = (point *)calloc(targetCount,sizeof(point));

    if (points == NULL){ return(-1); }
    points = fillTheArray(points,width,height);
    

    for(int i = 0;i < width;i++)
    {
        for(int j = 0;j < height;j++)
        {
            printf("x:%d\ty:%d\n",points[j].x,points[j].y);
        }
    }




    for (int i = 0;i < targetCount;i++) {
        int primey = isPrime(primes,i);
        if(primey){
            *iter = i;
            iter++;
            primeCount++;
        }
    }

    //printf("Press Ctrl+C to exit\nHave FUN!\n");
    usleep(SECOND*5.0f);



/*
    printf(WIPE_SCREEN);
    for(int j = 0;j < targetCount;j++) {

       
       
        int rValue = ((primes[j]*13) % 256); 
        int gValue = ((primes[j]*53) % 256);
        int bValue = ((primes[j]*689) % 256);
        //printf(MOVE_CURSOR,posY,posX);
        printf(PAINT,rValue,gValue,bValue,WALL_STRING);

        usleep(SECOND*0.25);
    }
*/

    return(0);
}


/*And I'll call this a day since I wanna sleep tonight (and yeah against common belief I do have a sleeping schedule)*/


/*Dynamically allocated arrays by far: 3 
(yeah still keeping score of it not to loose or skip any free)
*/

int isPrime(unsigned  int *arr,unsigned int val)
{
    /*  Base Cases   */
    if (val == 0 || val == 1) {
        return(0);
    }

    if (val == 2 || val == 3) {
        return(1);
    }
    //Same drive-by sieve from other screensaver yk...
    unsigned  int *iter = arr;
    if (val % 6 == 1 || val % 6 == 5) {
        for (;(*iter)*(*iter) <= val;iter++) { 
           if (val % *iter == 0) {
                return(0);
            }

        }
        return(1);
    }

    return(0);
}


point *fillTheArray(point *root,int width,int height)
{
    int index = 0;
    for(int i = 0;i < width;i++)
    {   
        for(int j = 0;j < height;j++)
        {
             //I hope this works lmfao
            root[index].x = i+1;
            root[index].y = j+1;
            index++;
        }
    }
    return(root);
}


void cleanUp(void) {
    free(primes);
    free(points);

    primes = NULL;
    points = NULL;

    printf(WIPE_SCREEN RESET_COLOR RETURN_CURSOR);
}


void handleSIGINT(int sig)
{
    printf(WIPE_SCREEN RESET_COLOR RETURN_CURSOR);
    exit(0);
}