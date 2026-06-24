#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h> //For ioctl() and getting winsize and shit

#define HIDE_CURSOR "\033[?25l"
#define RETURN_CURSOR "\033[?25h"      //Basic ANSI escape codes for hiding/showing cursor (l means low and h means high as you can guess)


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

*/

typedef struct{
    int x; 
    int isUsed;
}flaggedNums; //Yup as I said using the same logic as before



unsigned int isPrime(unsigned int *arr,int size);
flaggedNums *fillTheArray(flaggedNums *root,int size);



int main(void)
{
    struct winsize window;

    ioctl(STDOUT_FILENO, TIOCGWINSZ,&window);
    printf("Lines %d\tCols:%d\n",window.ws_row,window.ws_col); //Okkie it works 

    const int width = window.ws_row;
    const int heigth = window.ws_col;





    return(0);
}


/*And I'll call this a day since I wanna sleep tonight (and yeah against common belief I do have a sleeping schedule)*/

