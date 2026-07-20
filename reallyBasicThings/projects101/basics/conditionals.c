#include <stdio.h>

/* This file is the core idea of every conditional type, if-else chain*/

int main(void)
{


    int e = 13; //Just declaring two variables 
    int a = 53;

    char c = 'E';

    
    /*and here is all conditional
        a != b is a not equal to b
        a > b  is a greater than b
        a < b  is a les than b
        a >= b  is a greater or equal to b
        a <= b  is a lesser than b or equal to b
        a == b is a eqaul to b *This works with chars (since they're just sugarcoated ints...like 65 for 'A' but not for string you can use strcmp() instead)
    */

    //This is a condition
    if (e > a) {
        //If E is  bigger than A execute this block
        printf("E is bigger");
    }

    else {
        //If not do that (e <=a)
        //You can nest another if in here in this block to check if they're equal but I won't lol
        printf("A is bigger\n");
    }

    //In C every non-zero value is considered as true so

    if (!a) // or a == 0 ! is basically not operator and shit 
    {

        printf("You won't even see this");
    }


    return(0);
}