// #include <stdio.h> nah 2 headers too much gotta ditch this one
#include <unistd.h> // For getting _exit() 

/*  
    Yeah just experimenting with low level fuckery 
    Overriding the default system entry point

    Important shits to know
    1-This requires -nostartfiles as you compile since we need to tell the linker to skip the standard startup sequence
    2- _exit just exists immediately unlike return() which clears stdio buffers and shit you can use atexit() with a function to clear buffers with:
        - fflush(stdio) for output
        and a basic getchar loop for stdin buffer clear 
    3- We're basically saying linker to fuck crt0.o itself (crt0.o is basically the 'safe' exit option that main returns to and 
    init part where argc and argv get parsed so if you were to use cli arguments you gotta parse it manuelly 
    if you use _start and if you feel like those words are gibbrish don't worry they are don't mind) 
    And totally unrelated as I search for difference between return and _exit google's 'Also check' thingy showed me a bullet point 
    suggesting 'How to code 'I Love you' in C' some people trying impress nerds ig....
    be carefull gang don't fall for it unless it's a mainless I love you statement 
*/

int _start() {

    char lulz[] = "MAIN IS FOR THE WEAK\n";  //Mutable char array not (char *) since yk...sizeof() doesn't work with it...well it does but gives you 8 (unless you are using a toaster)
    write(1,lulz, sizeof(lulz)); //Since we use write you don't need to worry about 
    //printf("MAIN IS FOR THE WEAK\n"); why using stdio lol
    char e[] = "Here is a prime number for you before I dip: 13\n";
    write(1,e, sizeof(e));
    
    // Terminate the process immediately
    _exit(0); //Basically a magnum to the temple with an empty bottle o' jack on the table (or kill -9 if you know)
    //return(0); would cause segfault (if not UB) since there is no crt0.o return TO
}