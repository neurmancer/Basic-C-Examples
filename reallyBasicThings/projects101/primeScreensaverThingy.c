#include <stdio.h>  //For I/O duh...
#include <stdlib.h> //For Dynamic Shit
#include <raylib.h> // For Graphs


/*
        Have you ever heard someone saying 'Man...the hardest part of programming is writing the first line'? I say that so often and usually roll with 'fuck everything let's start with #define <stdio.h>' 
        only to end up with not using it and removing after I am done with the project/file but it gives the external force to push first commit(pun intended)  

        'You started to use raylib so much Neuro' yeah and I have my reasons...
        First, it's the shiny new lib that I laid my hands on so I wanna play with my new toy naturally
        Second, I am working on a project called ShittyVim (for now it's private on Github) and termios needs high attention and manual labor with it's raw mode so I cope with some abstraction raylib provides
        Third, There is a basic 'Baby's First Kernel Module' file on the way I am letting it marinete (or how tf u spell it) for a bit for better demonstration and expend my knowledge...
        

        Sup? New day new thingy i guess...so What we're building today? A Screensaver on the surface using my beloved ones. Prime numbers ofc here is the tea
        1-Open a borderless window
        2-Calculate primes up to UINT_MAX on the fly with optimization concerns 
        3-And pick a random vector on the screen (x,y) on the screen and paint the said pixel for each prime..
            Subideas for painting 
                1- A monochrome screen paint for satisfaction with only one color and watch screen change skin 
                2- Random selection of color from a predetermined array
                3- Changing values over time for each RGB hex so you can see guess 'warmth' of primes on the screen by just looking 
                4- Or for n we can switch colors where n is the 10^n  so primes upto 10 would be a color and then (10,100)would another etc..
        
        And I am changing my doctrine in this file usually I start with a printf() or InitWindow to stimulate myself but this time we're building toolkit first so here are what we need
        
            1- A dynamic array (that's why stlib's here) 
                1- A base array with let's say size of 256 elements and increase it accordingly as we go
                2- A function to wrap realloc around so we can abstarct the error handling and shit.
                3- A 
            2- A prime founder that won't take eternity to reach UINT_MAX but here is the twist I'll implement something myself lol...no handholding or algorithm lectures I am a rouge-dev
            3- Two arrays for filling with resolution values (one for Width one for Height...yeah I can use a Vector2 or typedef a struct myself (I used typedef as a verb lol) but we'll see as we roll)
            4- A PRNG thing for selecting an element from the said arrays for x,y coordinates and then a function to delete the point from the array so we don't override a painted pixel
            since we'll pop (or remove) elements randomly (pseudorandomly) probably this will take O(n) but array is sorted (as I said 1 to width/height) so we can use a binary search maybe(tho I don't know yet I just have ideas resemmbling the definition)

            And shoutout to my English Lit teachy that told me that I am bad at writing...she was right lol 
            I am good at yapping we got literally nothing yet vim shows 45 rows already and I don't delete those since in a world that every program gets sterilzied people often forget who codes it...
            We humans do...And that comes with its struggles
*/



int main(void)
{





    return(0);
}
