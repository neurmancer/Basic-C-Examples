
#include <limits.h> //Yeah I won't remember 2^31-1 no matter what
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h> //For ioctl() and getting winsize and shit
#include <time.h>
#include <signal.h>


/*ANSI DEFINES */
#define HIDE_CURSOR "\033[?25l"
#define RETURN_CURSOR "\033[?25h"      //Basic ANSI escape codes for hiding/showing cursor (l means low and h means high as you can guess)
#define WIPE_SCREEN "\033[H\033[J"
#define WALL_STRING "█" 
//That's not ANSI but you got the idea and it's a 'string' in C since it is not an ASCII char 
// (the standard 0-255 bit(for extended ASCII) format for characters) but a UTF-8 multibyte character so it is a char array in C sense  
#define RESET_COLOR   "\033[0m"
#define PAINT "\033[38;2;%d;%d;%dm%s" //Gets the RGB values and a string as parameters 
#define MOVE_CURSOR "\033[%d;%dH"

#define SECOND 1000000

/*

                                **This project is finished**
    Welcome to my shell or tty I'd say...Where I exactly know what I am doing. This is my domain and you're on trusted hands here. 


    This is gonna be as same as primeScreensaverThingy but for low-level gremlins (like me OwO)(and I use emoticons so much so what?Don't act like you didn't use mySpace)
    'Sup? it's almost 11PM so...you know...I flipped the questioning switch off and started coding
    
    We'll 'reimplement the primeScreensaverThingy for CLI interafaces so you can enjoy it without thinking about graphic libs... and let me get this clear...
    I don't wanna waste so much time on this file since it's lowkey against my don't do same thing twice philosphy
    (tho in Software Engineering it's called D.R.Y..Don't repeat yourself )
    
    I'll use ioctl for getting terminal size (yeah I am planning this shit on the way too so I don't even typed int main yet...)
    but I won't bother to resize the array for resizing the terminal
    
    since it'll require me to keep track of the already filled pixels, already filled array for flagged points on the screen etc. 
    So here is the deal: 
        Pls do not resize the window after starting the program UnU ...and for the record if you wanna use this I presume you want to see what's on screen...hence why resizing to break it?Right?
          
    and I intend to do the coloring with full ANSI fuckery so no external libs...no ncurse, no window just a colored 24-bit coloring with primes 

    and since the idea is same as the gui version most of the logic will be same too...just ported to CLI 

    and if you can't tell this is a linux gang exclusive screensaver since 
    windows powershell does not fucking support ANSI (a decades old tech btw) natively and 
    unistd is a unix exclusive header if you can't tell duh 


    and for the record: This program will be using Ctrl+C for exit with a custom handler... 
    Chaged the shuffle logic with Fisher-Yates algorithm 
    (I guess that's correct term but not sure and It is also known as the Knuth shuffle after popularizing the algorithm in The Art of Computer Programming) 
    did I implement it correctly?
    No fucking idea...
    

    You know what this file needs? Low-level fuckkery... so..we're gonna type everything with write() for the next version (yeah I added this line after saying this project is finished OwO)
*/

volatile sig_atomic_t flag = 0;

/* what is sig_atomic_t ? It is explicitly designed to safely communicate between a main program and an asynchronous signal handler.
   which is exactly what I need to free my shit in case of aborting the program and for the people doesn't know what volatile is...
 
   rough take: Compiler sometimes(most of the time) tends to optimize shit especially there is no significant part of code chages it directly.
   volatile is our way to saying 'Do not presume it's value when you see the var,
   check RAM for the value every time you need from RAM do not cache it'...That's a rough take but you got the idea  
*/

typedef struct{
    int x; 
    int y;


}point; //Slightly different logic this time



int isPrime(unsigned int *arr,unsigned int val);

point *fillTheArray(point *root,int width,int height);
point *shuffle(point *root,int size);


void handleSIGINT(int sig);
void handleSIGWINCH(int sig);

/*Global vars cuz needed*/


unsigned int *primes = NULL;
struct winsize window;
point *points = NULL;


int main(void)
{
    int amIFuckedUp = 0;

    setvbuf(stdout,NULL, _IONBF,0); //The prayer of a classical CLI tool... turning line buffering off
    printf(HIDE_CURSOR);


    struct sigaction sa = { 0 }; // Termination handler (yeah I used sa and sa2 as vars for no reason)
    sa.sa_handler = &handleSIGINT;
    sigaction(SIGINT,&sa,NULL); 
    //I use sigaction because linux man page suggests this over signal() due to compability issues https://man7.org/linux/man-pages/man2/signal.2.html <- Here is why nerds

    struct sigaction sa2 = { 0 }; //Resize handler
    sa2.sa_handler = &handleSIGWINCH;
    sigaction(SIGWINCH,&sa2,NULL);

    srand(time(NULL) ^ getpid()); //Extra entropy baby... since already use unistd for defines (STDOUT_FILENO,TIOCGWINSZ etc.) and for the record this is still 'Pseduo' random not cryptic just it makes it less predictible...witohut process ID two executions started at the same second would generate the same seed (due to time(NULL) giving just the Unix Epoch)  



    ioctl(STDOUT_FILENO, TIOCGWINSZ,&window);


    const int width = window.ws_col;
    const int height = window.ws_row;

    int primeCount = 0;
    int targetCount = width*height;
    primes = (unsigned int *) calloc(targetCount+1,sizeof(unsigned int));
    points = (point *)calloc(targetCount,sizeof(point));
    
    if (primes == NULL) { amIFuckedUp = -1; goto farewell; }
    unsigned int *iter = primes; //To not to loose the root again...

    if (points == NULL){ amIFuckedUp = -1; goto farewell; }
    points = fillTheArray(points,width,height);
    
    if (INT_MAX / window.ws_row > window.ws_col) {
        printf("Bruh what's your screensize? Are you on a fucking Times Square billboard or smthng?\n");
        sleep(SECOND*1.3);
        amIFuckedUp = INT_MIN+1; //Just to scare the user lmfao
        goto farewell;
    }

    int index = 0;
    
    points = shuffle(points,targetCount);


    
    for (int i = 0;i < targetCount;i++) {
        int primey = isPrime(primes,i);
        if(primey){
            *iter = i;
            iter++;
            primeCount++;
        }
    }

    printf("Press Ctrl+C to exit\nHave FUN!\n");
    usleep(SECOND*1.3f);




    printf(WIPE_SCREEN);
    for(int j = 0;j < targetCount && !flag;j++) {

        int rValue = ((primes[j]*13) % 256); 
        int gValue = ((primes[j]*53) % 256);
        int bValue = ((primes[j]*689) % 256);
        
        printf(MOVE_CURSOR,points[j].y,points[j].x);
        printf(PAINT,rValue,gValue,bValue,WALL_STRING);

        usleep(SECOND*0.33);
    }


    /*uhhh...getting fancier i guess..using goto and shit what's that Windows cmd matrix? using %rand% and goto to get an infinite loop? but it's better to not leak i guess 
    Before you start to talk about Damnation of Dikjtra(was that his name?The maze guy) over goto usage;
    First, did he read linux kernel code ever before publishing in '68(in Go To Statement Considered Harmful)? I don't think so
    but I did and, secondly, did this look spegetti to you or just avoiding copypasta code in each allocation fail?I think so so stfu...and go solve your fucking mazes...
    
    Psych!
    First, let me get this clear I am using Dijkstra as STRAWMAN his paper is absolutely right if you've seen some goto fetishists. 
    Second, I am against the 'dogma' in programming because some cases he's right and in some he's not and he clearifies his point, go read the paper for yourself to form your opinions please.
    Second hand knowledge is an accsessible curse. 
    
    but for the lazy people (yeah this is second-hand knowledge too)
    Dijkstra is saying those things for unstructured goto of 1960s assembly programming in his writing hence, my point still stands
    */

farewell:     
    free(primes);
    free(points);

    primes = NULL;
    points = NULL;

    printf(WIPE_SCREEN RESET_COLOR RETURN_CURSOR);
    if (flag == 2 || flag == -1) {
        printf("I literally told you not to do that and yet...your great ignorace couldn't resist the temptation...\nNow I am not gonna give you primes hmph...(⸝⸝>w<⸝⸝)"); //Tsundere prime saver lol
        usleep(SECOND*3);
        if (flag == -1) {
            printf("Besides...you didn't even resize correctly and ioctl bitched about it lol\n");
            usleep(SECOND);
        }
        printf(WIPE_SCREEN RESET_COLOR RETURN_CURSOR);

    }
    

    return(amIFuckedUp);
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

point *shuffle(point *root,int size)
{

    for(int i = 0;i < size;i++)
    {
        int j = rand() % size;
        point temp = root[i];
        root[i] = root[j];
        root[j] = temp;
    }
   //After reading TAOCP (yeah this comment is an addition) 
   // I realized this is a slightly biased version so that's not purely random original verison selects from unshuffled part instead of all array but this is close enough for a screensaver 

    return(root);
}



void handleSIGINT(int sig)
{
/*    printf(WIPE_SCREEN RESET_COLOR RETURN_CURSOR);
    exit(0); printf not beign async and a few complicated shit so we're using a fancy volatile flag
*/ 
    flag = 1;
}

void handleSIGWINCH(int sig)
{
    if (sig == SIGWINCH)
    {
        if(ioctl(STDOUT_FILENO,TIOCGWINSZ,&window) == -1) { /*No perror since async being a bitch*/ }
        flag =-1;
    }
    else { flag = 2; }
    }