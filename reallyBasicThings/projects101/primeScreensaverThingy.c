/*if you've seen my other raylib.h thingies you know how I split the code and it'll be the same*/

/*      Includes        */

#include <stdio.h> //For I/O duh...
#include <stdlib.h> //For Dynamic Shit
#include <raylib.h> // For Graphs
#include <limits.h> //For UINT_MAX (yeah I ain't still gonna remember how much 2^32-1 or shit)
#include <time.h>   //Yeah Include army getting bigger and bigger...I miss the glorious days only me, unistd and math...
 

/*
                    FULL NERDY YAP MOD (if you don't feel like it second and third paragraph is the key part rest is upon your decision)

        Have you ever heard someone saying 'Man...the hardest part of programming is writing the first line'? I say that so often and usually roll with 'fuck everything let's start with #include <stdio.h>'
        only to end up with not using it and removing after I am done with the project/file but it gives the external force to push first commit(pun intended)

        'You started to use raylib so much Neuro' yeah and I have my reasons...
            First, it's the shiny new lib that I laid my hands on so I wanna play with my new toy naturally
            Second, I am working on a project called ShittyVim (for now it's private on Github) and termios needs high attention and manual labor with it's raw mode so I cope with some abstraction raylib provides
            Third, There is a basic 'Baby's First Linux Kernel Driver' file on the way I am letting it marinete (or how tf u spell it) for a bit for better demonstration and tutorial as I expend my knowledge on it...
       
        Sup? New day new thingy i guess...so What we're building today? A Screensaver on the surface using my beloved ones. Prime numbers ofc here is the tea
        
        1-Open a borderless window
        2-Calculate primes up to UINT_MAX (side-track here 4,294,967,295 is UINT_MAX's value and last loop will check till approx. ~68k iteration so that's...gonna be harsh(I made the sqrt mentally so it can be janky)) on the fly with optimization concerns
        3-And pick a random vector on the screen (x,y) on the screen and paint the said pixel for each prime..
            Subideas for painting
                1- A monochrome screen paint for satisfaction with only one color and watch screen change skin
                2- Random selection of color from a predetermined array (that feels tempting since maybe it'll be mona lisa on the 13th run? yk...the infinite time/monkey and hamlet type shit)
                3- Changing values over time for each RGB hex so you can see guess 'warmth' of primes on the screen by just looking
                4- Or for n we can switch colors where n is the 10^n so primes upto 10 would be a color and then (10,100)would another etc.. 
                (basically log10 and every +1 will be new color till the next +1...yeah I explain shit harder than it should be...) 
 
        And I am changing my doctrine(said the 3 weeks old coder as if he's  Kant publishing the Critique of Pure Reason and explaining a paradigm shift) in this file usually I start with a printf()
        or InitWindow to stimulate myself with a dopamine hit but this time we're building toolkit first so here are what we need
       
            1- A dynamic array (that's why stlib's here)
                1- A base array with let's say size of 256 elements and increase it accordingly as we go
                2- A function to wrap realloc around so we can abstarct the error handling and shit.
                3- And that's all I guess
            2- A prime founder that won't take eternity to reach UINT_MAX but here is the twist I'll implement something myself lol...no handholding or algorithm lectures I am a rouge-dev(yeah Red in french and misspelled Rogue both suits me) and the 'no hand holding' rule means that Imma be Terry Davis'ing my way through this file too lol(and yeah I use 'Terry Davis' as verb) 
            3- Two arrays for filling with resolution values (one for Width one for Height...yeah I can use a Vector2 or typedef a struct myself (I used typedef as a verb lol) but we'll see as we roll)
            4- A PRNG thing for selecting an element from the said arrays for x,y coordinates and then a function to delete the point from the array so we don't override a painted pixel
            
            and since I don't know how to ditch an element from an formal array of C I'll probably use two seperate exactly same linked list struct...
            probably an overkill but that what occured in mind that I can handle first...
            
            since we'll pop (or remove) elements randomly (pseudorandomly) probably this will take O(n)(Bachmann–Landau notation but
            I guess in coding we only care about worst case which is O() form instead of omega or anything else...idk) but array is sorted (as I said 1 to width/height)
            so we can use a binary search maybe(tho I don't know yet I just have ideas resemmbling the definition)
           
            Improvment Idea (yeah even before starting to type anything for this one yet)
                1- Ditch the GUI and make it CLI with using 24bit true colors and █ (if that's recolorable i need to try first lol)

            I am good at yapping we got literally nothing yet vim shows 45 rows already and I don't delete those since in a world that every program gets sterilzied people often forget who codes it...

            We humans do...And that comes with its struggles and the banter within files what makes them precious imo like have you read man page of ffplay? I read for 3 hours for some flag hunt for ShittyJukeBox project due to buffer latency of ffplay and saw people'd written things like '360p shitty buffer' '720p cool buffering' etc. that's how programming was or the original source code of doom has cusses in it because WE ARE HUMAN...I mean that's why I've chosen C it is messy, it resembles humanity there is no 'spacing' like python nor abstraction behind abstraction.. for example I can write 010<:arr:> and compiler just accepts (which means arr[8] btw more on that later)
         


            Well...SECOND DOCTRINE CHANGE ABORTING THE LINKED LISTS for faster results... new idea well...that's gonna be a RAM fucker but 2 arrays for each x and y coordinates and 2 for same sized full init zero'd ones as a 'used' flag.
            access will be O(1) but as I said memory will double but keeping track of an linked list (12 byte 8 from pointer(for x86_64 my rig) 4 from the value + padding would be roughly worse anyways...and I wasted my time on linked lists lol) 

            Well... NOW OUT OF BLUE I realized that UINT_MAX is a little big number...so we have to lowkey go multiple processes at the same time...Time to reap what we sow...
            But don't you worry I am a zombie/orphan free guy like my memory hygeine OwO tho I'll probably use a pipe and a fd (file descriptor) to communicate between processes but
            I think that's a shit for tomorrow


            Controls (at least for now):
                1- ESC to quit duh...
                Possible in the future one
                    Hotkeys for each subbullet point for the coloring as option...

*/

/*      #Defines#       */


#define FPS 120


/*     Declarations      */

typedef struct{
    int value;
    int isUsed;
}flaggedInts; //Yeah even my var names are too long but point is I am a dumb guy...I forget shit...

void fillFlaggeds(flaggedInts *arr,int elements);
void drawPrimePixels(Vector2* vector,int size); //I'll use Vector2 array instead of seperate x,y arrays to avoid array parallelling and keeping up with it... and probably I'll need another (Color) array for...yk keeping the colors of the each pixel
//That feels inefficient...is there another way? Another struct for this?Eh we'll see


int dontOverthinkTheNames(flaggedInts *arr,int element);
int isPrime(unsigned int *arr,unsigned int val);

//I realized something I usually tend to factorize those function prototypes based on their return type (unless they are serving the same bigger meaning...That feels neat!) 

/*      Global Vars...   (yeah I am cheesing my way out with globals)*/




unsigned int primeCount = 0;


int main(void)
{

    srand(time(NULL));
    int printablePrimes = 0;

    //  Graphical User Interface thingies (yeah saying GUI feels weird)

    InitWindow(1600,1200,"Prime Thingy");
    int monitor = GetCurrentMonitor();
    int WIDTH = GetMonitorWidth(monitor);
    int HEIGHT = GetMonitorHeight(monitor);
    if (WIDTH <= 0) { WIDTH = 1200; }
    if (HEIGHT <= 0) { HEIGHT = 900; }


    if(!IsWindowReady()) { return(-1); }
    SetTargetFPS(FPS);

    ToggleBorderlessWindowed();

/*  ################################################################################    */
    
    flaggedInts *xValues = (flaggedInts *)(malloc(sizeof(flaggedInts)*WIDTH));
    
    if (xValues == NULL) { return(-1); }
    
    flaggedInts *yValues = (flaggedInts *)(malloc(sizeof(flaggedInts)*HEIGHT));
    if (yValues == NULL) { return(-1); }



    WIDTH = GetMonitorWidth(monitor); //I learned that on error this returns 0 (same for Height too...)

    HEIGHT = GetMonitorHeight(monitor);

    fillFlaggeds(xValues,WIDTH);
    fillFlaggeds(yValues,HEIGHT);
    
    //Works until this point
    int target = HEIGHT*WIDTH; //Why tf am I getting segfault?..hmmm

    unsigned int *primes = (unsigned int *)malloc(sizeof(unsigned int)*target); //And I abonden the idea of primes UP TO UINT_MAX which is pointless since we don't have that many pixels on screen
    if (primes == NULL) { return(1); } //I'll probably add perror() later for each check but not now...
    
    unsigned int *iter = primes;       //I'll use pointer walks probably so much so... I gotta keep primes as a constant so I can free without problem

    Vector2 *pixels = (Vector2 *)malloc(sizeof(Vector2)*target);
    if (pixels == NULL) { return(-1); }
 
    Vector2 *pixelIter = pixels;    //Yeah I am trying to use iters as much as possible...paranoia? Nope never heard of her...

    int posX = 0, posY = 0;

    double dLastPrint = 0.0f;

    BeginDrawing();
    ClearBackground(BLACK);
    EndDrawing();

    while (!WindowShouldClose()) {
        
        dLastPrint += GetFrameTime();
        
        //Keyboard conditions
        if (IsKeyPressed(KEY_ESCAPE)) { CloseWindow(); }

        //Logic
        while (isPrime(primes,primeCount) == 0 && primeCount < target+10) {
            primeCount++;
        }
        *iter = primeCount;

        //Incrementation (or how tf u spell it)
        iter++;
        primeCount++;
        
        BeginDrawing();

        if (dLastPrint > 0.1f) {
            posX = dontOverthinkTheNames(xValues,WIDTH);
            posY = dontOverthinkTheNames(yValues,HEIGHT);
            pixelIter->x = posX;
            pixelIter->y = posY;
            printablePrimes++;
            dLastPrint -= 0.1f;

            DrawPixelV(*pixelIter,PURPLE);        
            pixelIter++;
        }

        
        EndDrawing();
    }



    free(primes);
    free(xValues);
    free(yValues);
    free(pixels);

    primes = NULL;
    xValues = NULL;
    yValues = NULL;
    pixels = NULL;

    printf("If you can see this after pressing ESC we're memory safe\n");

    return(0);
}

void fillFlaggeds(flaggedInts *arr,int elements)
{
    for (int i = 0; i < elements;i++) {
        arr[i].value = i;
        arr[i].isUsed = 0;
    }
}


int isPrime(unsigned  int *arr,unsigned int val) //I thought using my old prime func but improving something new...
{
    /*  Base Cases   */
    if (val == 0 || val == 1) {
        return(0);
    }

    if (val == 2 || val == 3) {
        return(1);
    }
    //Drive-by sieve lmfao
    unsigned  int *iter = arr;
    if (val % 6 == 1 || val % 6 == 5) {
        for (;(*iter)*(*iter) <= val;iter++) { 
            //I usally don't explain the math but instead of incremanting two by two we're checking if it can be divided by the primes before that number up to it's square root 
            //and sice this project's gonna use -lraylib I don't wanna deal with -lm too so we're flipping the script and checking if iter's square is less or equal to target val
            if (val % *iter == 0) {
                return(0);
            }
            /*Well I could've done this skipping 2 and 3 entirely (since 6k+1 elimnates those and iterating 2+ times for each candidate is suboptimal) 
            but I wanna create the array on the go too so it'll stay like that but that's the reason people are obsessed with 'abstraction' Ig...
            */
        }
        return(1);
    }

    return(0);
}


int dontOverthinkTheNames(flaggedInts *arr,int arrSize)
{
    int point = 0;

    do {
        point = rand() % arrSize;
    }while (arr[point].isUsed); //As far as I know (I only now do..while loops in theory) this SHOULD run at least once and goes on as the condition is provided
                                //(provided isn't the best word but my vocabulary is halved right now...lol)

    arr[point].isUsed = 1;
    
    return(point);
}



void drawPrimePixels(Vector2* vector,int size)
{
    for (int i = 0;i < size;i++) {
        DrawPixelV(vector[i],CLITERAL(Color){0,13,53,255});
    }
//That's gonna be very inefficient isn't it? Pew... I FUCKING SOLVED IT
}


/*
    Malloc counter : 4 (I have more than a few so I gotta keep track of each allocation to free easier later)
*/