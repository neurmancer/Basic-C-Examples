/*


    'Sup? You know the tea but if I must vocalize (or textualize if that's a word) today's low-level fuckery is implementing malloc using the
    ancient scrolls of sbrk insted of mmap. 
        
        This is the second time I am attempting to implement this because the first implementation respectfully got corrupted by ADHD with meaningless defines and 
        lost the actual point...Hence, We're doing it from scratch


        Shit to know:
            0- I'll use doubly linked lists so...go take a peek wtf it is
            1- Know how the pointers work at least fundementally
            2- Well...know how to use malloc and free at least

        and here is the source I am using implement malloc: https://levelup.gitconnected.com/malloc-is-not-magic-implementing-my-own-memory-allocator-e0354e914402
        So...let's fucking get the keyboard moving before I need to eventually use pyt*n for the android client for the TODO server
        and as always this is here as a template...
        
*/


//So let's start with headers...

#include <assert.h>

#include <stdlib.h> //This file is here to ditch you bruh just come and watch your funeral from a better seat
#include <stdbool.h> 
#include <stdint.h> //For data types such as uint32_t
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>





int main(void)
{


    return(0);
}