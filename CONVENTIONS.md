# Error Naming Conventions and Project Structures

- I'll make this standard validated in all the project within this repo... right now this is not valid for every project (I'll retro inspect)

- This file is a guide for all the considerably large projects in this repo
- Will cover: 
- - return codes and meanings,
- - How I structure bigger (usually raylib) projects

- - - First let me start with this: I am aware some projects are over 500LoC because this is a beginner repo and I don't want people to handle multiple files for 
one project so my goal is making them as self-contained as possible

## Error Codes 

> I'll be using the integer values in the code since I don't wanna copy paste/include a header for just <custom_err.h> and you can check it from here
> But usually I document what went wrong quite good so you don't need this for the most of the time and as a repo for beginners I don't want a custom header to deal with in case of moving the indiviual source file to somewhere else where the header no longer exists 

> I tend to use 13, 53 and 689 so much in my old code so we're building on top of it
> And keep that in mind that is a rough take, use case may differ in projects but perror() or err() will tell you what went wrong exactly within the given program/context

- (-1) For Allocation related problems (malloc,realloc,calloc etc. even mmem or sbrk if exists)
- (-13) Multi-purpose errors (depending on the project) may be syscall errors, may be fork() failures etc...
- (-53) external api dependent errors such as: InitWindow() failure
- (13) User Invalid Input
- (53) User Invalid Input back-up and multi-purpose
- (-689) Critical Failure   such as :Segmentation fault risks, overflow etc. 
- (689)  Multi-purpose      Dependent on project 
- (-1368953) Fatal Eror     Such as : Risk of data corruptiton 
- (1368953)         User related out of bounds error or invalid access  
- (INT_MIN and INT_MAX) Computational Errors    such as: Divide by Zero, integer overflow, floating point overflow 


## Project Structure


> The files in [Projects](reallyBasicThings/projects101/), [CLI Clones](reallyBasicThings/cliToolClones/) will be using this conventions. The rest are just:
> - Intro Lectures for concepts such as: Dynamic Allocation, Pointer usage, preprocessors without any depth or 'project' value

> The projects in said subfolders will follow this pattern with chance of slight variations: 

```c
/*YAPPING*/
//Where I yap about the concept and tangents for like 10-100 lines 
//Yapping structure is usually: 
/*
    Greeting
    Concept 
    Brief explanation of the Concept(aka 'Important Shit to Know')
    Citation -if used any-  
    Required flags for compiling -if needed- 
    Tangents (can be anything)
    Implementation details and internal discussion
    and Known Weaknesses or Bugs
*/

//Includes with specific goals will have their use-case noted next to them such as following

/*INCLUDES*/
//libc headers 
#include <stdio.h> //Standard headers will be adjacent to each other
#include <stdlib.h> //Dynamic Memory Allocation + rand()
#include <time.h>   //time(NULL)
//Headers that require external linking (such as -lm, -lraylib)
#include <raylib.h>     //For everything graphical
#include <math.h>      //sqrt(), cos(), sin(), etc. depending on the project

//Platform specific headers
#ifdef (__WIN32)
    #include <windows.h>
#else 
    #include <unistd.h>
#endif


/*DEFINES*/
//Defines gets seperated by '//' inline comment sections such as UI, UX, design, physics  such as:
//Init
#define WIDTH 1200
#define HEIGHT 900
//UI
#define RED CLITERAL(Color){255,0,0,255}

//defines that will be used in calculations will be explicitly wrapped with () and specified their types
//such as 
#define VEL_X (120.5L) //Long double
#define VEL_Y (30.25L)

#define FRICTION (0.42f) // L for long double capital and f for float  

//Compile time dependent ones at the bottom of the defines...such as:

#ifndef FPS
    #define FPS 120
#endif //So you can change those with -D(define name)=VALUE 
//some visual applications are framerate dependent because making them independent would be overkill just visualization this option won't be in those kind of files


/*OBJECTS(or structs)*/

//Objects has 2 different convetions
//First: Padding optimized
typedef struct{
    char *str;  //8 bytes
    double d;   //8 bytes
    float f;    //4 bytes
    int i;      //4 bytes
    //2*8 + 4*2 = 24 bytes
}PaddingOptimized;

//Second: Context dependent

typedef{
    
    //Ordered by derivative 
    double posX,posY;
    double velX,velY;
    double accelX,accelY;

    //Related factors F = m*a
    double force;
    double mass;

}Physics;

//... etc..

//I try to avoid usage of global vars but if needed they'll be here between function prototypes and objects with this flag such as:
/* GLOBAL VARS  */

volatile sig_atomic_t flag = 0;
//Some obscure concepts for beginners such as signal handling will have comment blocks to explain the idea roughly 

/*FUNCTION PROTOTYPES*/
//void returns
void exmp(void);
void exmp2(int a);
//Primivte types
int exmp3(void);
int exmp4(int a);
int *exmp5(void);
int *exmp6(void);

 //Custom struct types
n example(void);
n *example2(int);

//The convention follows this pattern pointer returns always under the original types, void parameters on top of the ones that takes parameters etc...
//Functions and rest of the program uses camelCase for naming and structs are using PascalCase... defines and constant values uses FULL_CAPS snake_case
//my primary motivation to use camelCase for functions is making them distinguishable from raylib.h functions which are using PascalCase such as:
//  IsKeyPressed(int Key) 


/*MAIN*/

int main(void)
{
    //Main doesn't have a certain structure but somethings that worth noting:
    //return value variable (if needed) is always on the top such as:
    int retValue = 0;   //name may change since I tend to name things randomly
    //If used buffer handling and random seeding follows returnValue
    srand(time(NULL));
    setvbuf(stdout, NULL, _IONBF, 0);   //Example buffer handling (if needed)
    //After those are done the inline comment (//) sign will guide you through all the stages such as Init, var assignment, loops, allocation etc...

    //The projects that uses dynmaic allocation will have them right after enviroment setup such as:
    int *p = (int *)(malloc(SIZE*sizeof(int)));
    int *p2 = (int *)(malloc(SIZE*sizeof(int)));
    int *p3 = (int *)(malloc(SIZE*sizeof(int)));
    //First, I do cast allocations and I am aware of the debate I do that for making reading easier and I do check <stdlib.h>'s existence before I to do so
    //Then NULL checks;
    if(p == NULL || p2 == NULL || p3 == NULL) { retValue = (-1); goto cleanUp; }


//Programs with more than 3 error paths will use retValue + goto cleanUp pattern, if less than 3 they'll be returning inline instead of clean up pattern
//Haven't needed any more than 10 allocations but if needed in the future you may encounter a :

int *allocatedMemories[ALLOCATED_AMOUNT] = { 0 }; //To keep track of the all memory to free and NULLify with a for loop 
cleanUp: 
//And fyi: 'Go To Statement Considered Harmful by Dijkstra (1968) isn't about C clean-up pattern but more about the time's assembly goto abuse 

    free(p);
    free(p2);
    free(p3);

    p = NULL;
    p2 = NULL;
    p3 = NULL;
    
/*
        Here is an example for the said allocation array
        for (size_t i = 0; i < ALLOCATED_AMOUNT;i++)
        {
            free(allocatedMemories[i]);
            allocatedMemories[i] = NULL;
        }
        but never used before as I said 
*/


    return(retValue); //This is a stylistic choice that I inhabited
    //return and sizeof operator uses () explicitly even though not being a necessity
}

//and in between main and function bodies I usually have a Memory Accountant part manually counting allocations as I allocate in case of Valgrind malfunctions
//or projects I couldn't run valgrind due to some problems

/*
    Allocated memory so far : x 
    free'd : x 
*/ 


/*FUNCTION BODIES*/

//All the bodies independent from the order on prototype section most-likely to be in order according to their first apperance in main
//Sectored accordingly to their use case such as:

//Rendering/Drawing
//Computational functions
//Helpers / Wrappers
//Initilaze/Misc
```c

