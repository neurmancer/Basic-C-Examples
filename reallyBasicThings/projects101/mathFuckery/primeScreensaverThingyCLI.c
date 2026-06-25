#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h> //For ioctl() and getting winsize and shit
#include <time.h>

/*ANSI DEFINES */
#define HIDE_CURSOR "\033[?25l"
#define RETURN_CURSOR "\033[?25h"      //Basic ANSI escape codes for hiding/showing cursor (l means low and h means high as you can guess)
#define WIPE_SCREEN "\033[2J"
#define WALL_STRING "█" //That's not ANSI but you got the idea
#define RESET_COLOR   "\033[0m"
#define PAINT "\033[38;2;%d;%d;%dm%s" //Gets the RGB values and a string as parameters 

/*
    This is gonna be as same as primeScreensaverThingy but for low-level gremlins (like me OwO)(and I use emoticons so much so what?Don't act like you didn't use mySpace)
    'Sup? it's almost 11PM so...you know...I flipped the questioning switch off and started coding
    
    We'll 'reimplement the primeScreensaverThingy for CLI interafaces so you can enjoy it without thinking about graphic libs... and let me get this clear...
    I don't wanna waste so much time on this file since it's lowkey against my don't do same thing twice philosphy (tho in Softwere Engineering it's called D.R.Y..Don't repeat yourself )
    I'll use ioctl for getting terminal size (yeah I am planning this shit on the way too so I don't even typed int main yet...) but I won't bother to resize the array for resizing the terminal
    since it'll require me to keep track of the already filled pixels, already filled array for flagged points on the screen etc. 
    So here is the deal: 
        Pls do not resize the window after starting the program UnU
          
    and I intend to do the coloring with full ANSI fuckery so no external libs...no ncurse, no window just a colored 24-bit coloring with primes 

    and since the idea is same as the gui version most of the logic will be same too...just ported to CLI 


    and for the record: This program will be using Ctrl+C for exit with a custom handler...

*/

typedef struct{
    int x; 
    int isUsed;
}flaggedNums; //Yup as I said using the same logic as before



int isPrime(unsigned int *arr,unsigned int val);
flaggedNums *fillTheArray(flaggedNums *root,int size);



int main(void)
{
    struct winsize window;

    ioctl(STDOUT_FILENO, TIOCGWINSZ,&window);
    printf(WIPE_SCREEN "Lines %d\tCols:%d\n",window.ws_row,window.ws_col); //Okkie it works 
    printf(PAINT RESET_COLOR,53,12,255,WALL_STRING);
    printf("\n");

    const int width = window.ws_col;
    const int height = window.ws_row;

    int primeCount = 0;

    unsigned int *primes = calloc(width*height,sizeof(unsigned int));
    if (primes == NULL) { return(-1) ; }
    
    unsigned int *iter = primes; //To not to loose the root again...

    flaggedNums *xValues = calloc(width,sizeof(flaggedNums));
    if (xValues == NULL) { return(-1); }
    
    flaggedNums *yValues = calloc(height,sizeof(flaggedNums));
    if(yValues == NULL) { return(-1); }

    fillTheArray(xValues,width);
    fillTheArray(yValues,height);

    for (int i = 0;i <= 100;i++) {
        unsigned int primey = isPrime(primes,i);
        if (primey) {
            *iter = i;
            iter++;
            primeCount++;
        }
    }


    for (int i = 0;i < primeCount;i++) {
        printf("%d is prime bruh\n",primes[i]);
    }//Yup drive-by sieve still working like a charm

    
    free(primes);
    free(xValues);
    free(yValues);

    primes = NULL;
    xValues = NULL;
    yValues = NULL;

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


flaggedNums *fillTheArray(flaggedNums *root,int size)
{
    if (root == NULL){ return(NULL); }

    for (int i = 1;i <= size;i++) { //CLI interface starts at index 1,1 not 0,0 (yeah that fucks me up each time)
        root[i].x = i;
        root[i].isUsed = 0;
    }
    return(root);
}