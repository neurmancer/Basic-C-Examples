#include <stdio.h>
#include <unistd.h> // For getting _exit() 

/*  
    Yeah just experimenting with low level fuckery 
    Overriding the default system entry point

    Important shits to know
    1-This requires -nostartfiles as you compile since we need to tell the linker to skip the standard startup sequence
    2- _exit just exists immediately unlike return() which clears stdio buffers and shit you can use atexit() with a function to clear buffers with:
        - fflush(stdio) for output
        and a basic getchar loop for stdin buffer clear 

    And totally unrelated as I search for difference between return and _exit google's 'Also check' thingy showed me a bullet point 
    suggesting 'How to code 'I Love you' in C' some people trying impress nerds ig....
    be carefull gang don't fall for it unless it's a mainless I love you statment 

*/

int _start() {

    printf("MAIN IS FOR THE WEAK\n");
    printf("Here is a prime number for you before I dip: 13\n");
    
    // Terminate the process immediately
    _exit(0); 
}