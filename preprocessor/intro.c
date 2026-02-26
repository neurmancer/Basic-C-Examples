/*This folder is dedicated to introduction to preprocessors in C*/

#include <stdio.h>

#define NUM 20  //Define a const
#define SUM +   //Simply says put '+' sign when you see SUM 
#define COMPARE_NUMS(num1,num2) num1 > num2 ? num1 : num2
#define SQR(num) num*num    //This is a bad idea and I'll show you why


int main(void)
{

    printf("%d\n",NUM);
    printf("%d\n",NUM SUM NUM);
    printf("Square of num: %d\n",SQR(NUM));
    printf("Bigger one: %d\n",COMPARE_NUMS(5,30));


    /*Here where I show you why defining functions is something quite deceptive*/

    //Let's try a square 
    int x = 5;
    printf("Square of x+1: %d\n",SQR(x+1));     //If you know math you'd know the answer is 11 lol. run and see for yourself
    /*But honestly tho the thing is happening preprocessors are dumb so it takes x(which is 5)
    and puts tha value so the multipication becomes 5+1*5+1 and if you know order of operations it will be 5+ 5*1 + 1 = 11
    so if you really want to use it like that use parens
    
    */
    printf("Actual square of x+1: %d\n",SQR((x+1))); 

    return(0);
}