#include <stdio.h>
#include <stdlib.h>


/*
    Hi, kids, do you like violence? Wanna see me stick nine-inch nails through each one of my eyelids?
    (Uh-huh) Wanna copy me and do exactly like I did? (Yeah, yeah)
    Try deref a dangling pointer and get fucked up worse than my life is? (Huh?)

    anyways enough Slim Shady Hi kids! today me, The John Constantine of Heap, will show you 
    how to get your shit together with dynamic memory with the holy roll 20 guranteed grail of free() spell 
*/




int main(void)
{


/*
    have you ever played pokemon emerald?
    if you do here is the deal think this like you have  pokemons(malloc,calloc,realloc,free()) 
    living in pokeball(<stdlib.h>) and when you encounter a charizard in wilderness
    (a problem where you need full control over memory) 
    you unleash your pokemon upon and when it's done (or faints) you recall(free()) your shiny pikachu(malloc) 
    and if you haven't played Pokemon Emerald
    go fucking learn java since at has garbage collectors to pick  your trash game taste up

*/

    int *ptr = NULL;
    ptr = (int *) malloc(sizeof(int));//the casting (the part (int *)) is not necessary 
    // but I do it for two reasons first word 'casting' suits the persona accordingly 
    // and second I love to see what I am working with to reduce confusion 
    // and I do know it offends some people but there is a debugger for that problem
    //  called 'Rising each middle finger up against their face with a faint smirk'

    printf("%p\n",(void *) ptr); //printing address of pointer
    *ptr = 15; //Gave 15 value to allocated memory 
    printf("%p\t%d\n",(void *)ptr,*ptr);
    free(ptr); //always free the memory (and for fuck sake don't use the pointer after freeing it if you don't want segfault/UB)

    return(0);
}