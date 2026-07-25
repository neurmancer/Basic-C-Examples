# Error Naming Conventions and Project Structures

- I'll make this standard validated in all the project within this repo... right now this is not valid for every project (I'll retro inspect)

- This file is a guide for all the considerably large projects in this repo
- Will cover: 
- - return codes and meanings,
- - How I structure bigger (usually raylib) projects
- but not right now lmfao it's 5.03AM...I just left this here so I won't forget tomorrow

## Error Codes 

- (-1) For Allocation related problems (malloc,realloc,calloc etc. even mmem or sbrk if exists)
- (-13) Multi-purpose errors
- (-53) System Errors 
- (13) User Invalid Input
- (53) User fuck up 
- (-689) Critical Failure
- (689)  Multi-purpose 
- (-1368953) Fatal Eror 
- (1368953) Error 
- (INT_MIN and INT_MAX) Computational Errors 



## Project Structure


> I usually define function prototypes right on top of main: projects follow this pattern

```c
/*YAPPING*/
/*INCLUDES*/
//libc headers 
#include <stdio.h>
#include <stdlib.h>
//Headers that require external linking (such as -lm, -lraylib)
#include <raylib.h>
#include <math.h>

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

//Compile time dependent ones at the bottom of the defines...such as:

#ifndef FPS
    #define FPS 120
#endif //So you can change those with -D(define name)=VALUE 

/*OBJECTS(or structs)*/

//Objects has 2 different convetions
//First: Padding optimized
typedef struct{
    char *str;  //8 bytes
    double d;   //8 bytes
    float f;    //4 bytes
    int i;      //4 bytes
    //2*8 + 4*2 = 24 bytes
}paddingOptimized;

//Second: Context dependent

typedef{
    
    //Ordered by derivative 
    double posX,posY;
    double velX,velY;
    double accelX,accelY;

    //Related factors F = m*a
    double force;
    double mass;

}2dPhysics;

//... etc..

/*FUNCTION PROTOTYPES*/
//void returns
void exmp(void);
void exmp2(int a);
//Primivte types
int exmp3(void);
int exmp4(int a);
int *exmp5(void);
int *exmp5(void);

 //Custom struct types
n example(void);
n *example2(int);

//The convention follows this pattern pointer returns always under the original types, void parameters on top of the ones that takes parameters etc...


/*MAIN*/

int main(void)
{

    return(0);
}

/*FUNCTION BODIES*/

//All the bodies independent from the order on prototype section most-likely to be in order according to their first apperance in main


```c


