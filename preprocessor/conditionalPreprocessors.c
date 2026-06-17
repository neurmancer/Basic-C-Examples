#include <stdio.h>

/* This lecture will show you how actually ifdef/ifndef does and how to use*/

#define NUM 35  //Whether you assign something or not the important part is the macro in conditional block

#define EN "English"
#define RU "Russian"
#define FR "French"


int main(void)
{

    #ifdef NUM
        printf("Number is defined and its value is: %d\n",NUM);
    #else
        printf("Number is not defined\n"); //Btw if you use VSCode with C intellisense the false block will darkened like this
    #endif

    #ifndef _WIN32 //If not defined 
        printf("You are superior\n");
    #else 
        printf("You are on windows\n");
    #endif

    //Here is else-if block usage
    #if defined(EN)
        printf("User language is english\n");
        #undef EN //Removes definition
    #endif

    //Let's simulate a fallback language 
    #ifndef EN
        #if defined(RU)
            printf("User language is russian\n");
        #elif defined(FR)
            printf("User language is french\n") 

            /*
            'But Neuro you forgot the ';' after printf this won't gonna compile!'
            congrats meatloaf you got good eyes...for someone diagnosed with compiler illiteratacy... 
            I know it doesn't have the ';' but the point is it doesn't need it
            RU is checked first so interpreter will get rid of this statement before compiling hence compiler will never see this.
            I dare you to compile...go for it it fucking compiles */
        #endif
    #endif

    //since Russian is first if block second else-if macro won't be running so you'll only see russian

    return(0);
}