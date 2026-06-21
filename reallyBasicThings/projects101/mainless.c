// #include <stdio.h> nah 2 headers too much gotta ditch this one

#include <unistd.h> // For getting _exit() 

/*  
    Yeah just experimenting with low level fuckery 
    Overriding the default system entry point

    Important shits to know
    1-This requires -nostartfiles as you compile since we need to tell the linker to skip the standard startup sequence
    2- _exit just exists immediately unlike return() which clears stdio buffers and shit you can use atexit() with a function to clear buffers with:
        - fflush(stdout) for output
        and a basic getchar loop for stdin buffer clear 
    3- We're basically saying linker to fuck crt0.o itself (crt0.o is basically the 'safe' exit option that main returns to and 


    init part where argc and argv get parsed so if you were to use cli arguments you gotta parse it manuelly 
    if you use _start and if you feel like those words are gibbrish don't worry they are don't mind you can think this as the dwarves in the ATMs pushing you money and your card back,checking if your 
    pin is correct or not etc. (yeah there is dwarves living in ATMs for minimum wage you can't prove me otherwise))

    And totally unrelated as I search for difference between return and _exit google's 'Also check' thingy showed me a bullet point 
    suggesting 'How to code 'I Love you' in C' some people trying impress nerds ig....
    be carefull gang don't fall for it unless it's a mainless I love you statement (tho I wouldn't advise that too since if they're gonna use _exit() they'd probably ghost you after 3 days)
    so...moral of the story:Marry your compiler (I love you cc mwah)
*/

//void butler(void); that's a basic demo for you if you wanna use atexit() but since I didn't care enough to rewrite flushes in unistd func or from scratch you'll need <stdio.h> for functions in this


void _start() {

    char lulz[] = "MAIN IS FOR THE WEAK\n";  //Mutable char array not (char *) since yk...sizeof() doesn't work with it...well it does but gives you 8(unless you are using a toaster) due to the decay 
    write(1,lulz, sizeof(lulz)-1); //Since we use write you don't need to worry about null terminator (more on that later) I can ditch the last byte  
    //printf("MAIN IS FOR THE WEAK\n"); why using stdio lol
    char e[] = "Here is a prime number for you before I dip: 13\n"; 
    write(1,e, sizeof(e)-1); //Same reason here
    
    // Terminate the process immediately
    //atexit(&cleanUP());
    _exit(0); //Basically a magnum to the temple with an empty bottle o' jack on the table (or kill -9 if you know)
    //return(0); would cause segfault (if not UB) since there is no crt0.o return TO...there is no return address on stack for _start 
}

/*
void butler(void)
{
    
    fflush(stdout);
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        c++ One must imagine c++ happy...
    }
}
*/