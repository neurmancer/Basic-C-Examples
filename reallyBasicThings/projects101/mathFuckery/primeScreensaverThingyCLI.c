#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/ioctl.h> //For ioctl() and getting winsize and shit
#include <time.h>

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

    Coming improv: Add a flag for primeCheck status then pipe it to child to end the loading bar instead of hardcoded time 
    (yeah I know some of you guys still use IBM notebooks from stone age...I got you bruh)
*/

typedef struct{
    int x; 
    int isUsed;
}flaggedNum; //Yup as I said using the same logic as before



int isPrime(unsigned int *arr,unsigned int val);
int posGen(flaggedNum *arr,int size,int *usedOnes);

flaggedNum *fillTheArray(flaggedNum *root,int size);


/*
What shit are missing (A recap quickie)
    1-Visualization duh...
    2- The IPC pipe I yapped and promised about
    3-

*/

int main(void)
{
    setvbuf(stdout,NULL, _IONBF,0); //The prayer of a classical CLI tool... turning line buffering off
    /*fd[0] reading end
      fd[1] writing end (yeah I am leaving bread crumbs for myself)
    */

    int fd[2] = { 0 }; //File descriptor int array which I'll use for pipe

    if (pipe(fd) == -1) {perror("Piping error(yeah it's a vauge error but still better than window fix tools\n"); return(-1); }


    int pid = fork();
    if (pid == -1) {perror("Forking got spooned\n"); return(-13);}
    if (pid == 0) {
        close(fd[1]);
        printf("I am calculating primes upto your terminal size so please be patient for a few seconds\n");

        const char *bar = "|/-\\";
        int spinner = 0;
        int done = 0;
        while (!done) {
            printf(HIDE_CURSOR);
            printf("\r%c Calculating some primes",bar[spinner%4]);
            usleep(135315);
            spinner++;
            if((read(fd[0],&done,sizeof(done))) == -1) { perror("Illiteracy error\n"); return(-1368953); } 
        } 
        close(fd[0]);
        printf(WIPE_SCREEN);
        return(0);
    }


    else {
        
        close(fd[0]); //I wont be rading shit from child process
        srand(time(NULL) ^ getpid()); //Extra entorpy baby... sinec already use unistd for defines (STDOUT_FILENO,TIOCGWINSZ etc.)
        int arePrimesDone = 0;

        struct winsize window;

        ioctl(STDOUT_FILENO, TIOCGWINSZ,&window);


        const int width = window.ws_col;
        const int height = window.ws_row;

        int primeCount = 0;
        int targetCount = width*height*100;
        unsigned int *primes = (unsigned int *) calloc(targetCount+1,sizeof(unsigned int));
        if (primes == NULL) { return(-1) ; }
        
        unsigned int *iter = primes; //To not to loose the root again...

        flaggedNum *xValues = (flaggedNum *) calloc(width,sizeof(flaggedNum));
        if (xValues == NULL) { return(-1); }
        
        flaggedNum *yValues = (flaggedNum *)calloc(height,sizeof(flaggedNum));
        if(yValues == NULL) { return(-1); }

        int usedXs = 0;
        int usedYs = 0;

        fillTheArray(xValues,width);
        fillTheArray(yValues,height);

        
         
        for (int i = 0;i < targetCount;i++) {
            int primey = isPrime(primes,i);
            if(primey){
                *iter = i;
                iter++;
                primeCount++;
            }
        }

        arePrimesDone = 1;
        
        if(write(fd[1], &arePrimesDone,sizeof(arePrimesDone)) == -1) {perror("Eloquence error\n"); return(-689);} //Yk...cuz it couldn't writ?lulz
        close(fd[1]);
        wait(NULL); //I won't be bothered to check for a specific child since I only have one

        printf("Now ready!\n");

        
        printf(WIPE_SCREEN);
        for(int j = 0;j < targetCount;j++) {
            
            int posX = posGen(xValues,width,&usedXs);
            int posY = posGen(yValues,height,&usedYs);
            int rValue = ((primes[j]*13) % 256); 
            int gValue = ((primes[j]*53) % 256);
            int bValue = ((primes[j]*689) % 256);
            printf(MOVE_CURSOR,posY,posX);
            printf(PAINT,rValue,gValue,bValue,WALL_STRING);
            usedXs++;
            usedYs++;

            usleep(SECOND*0.2);
        }
        

        
        free(primes);
        free(xValues);
        free(yValues);

        primes = NULL;
        xValues = NULL;
        yValues = NULL;

    }
    
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


flaggedNum *fillTheArray(flaggedNum *root,int size)
{
    if (root == NULL){ return(NULL); }

    for (int i = 0;i < size;i++) { //CLI interface starts at index 1,1 not 0,0 (yeah that fucks me up each time)
        root[i].x = i+1; //As I said I need to reach size but not seg-assulting my own ass 
        root[i].isUsed = 0;
    }
    return(root);
}

int posGen(flaggedNum *arr,int size,int *usedOnes)
{
    if (*usedOnes == size) {
        return(-1); //To prevent infinte loop    
    }

    int x = 0;
    do {
        x = (rand() % size)+1; //Never trust a computer to compute use bracelets  -Sun Tzu (or Linus Torvalds IDK)    
    }while (arr[x].isUsed);
    
    arr[x].isUsed = 1;

    return(x);
}