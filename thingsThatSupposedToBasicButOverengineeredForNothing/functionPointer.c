#include <stdio.h>


int calculateShit(int a,int b)
{

    return((2*a)+(3*b));

}


int calculateShit2(int a,int b)
{

    return(a+b);

}


int calculateShit3(int a,int b)
{

    return((3*a)+b);

}

int calculate(int (*ptr)(int,int),int a, int b)
{

    int res = ptr(a,b);
    return(res);
}


int main(void)
{

    int (*funcPtr[3])(int,int);

    funcPtr[0] = calculateShit;
    funcPtr[1] = calculateShit2;
    funcPtr[2] = calculateShit3;


    
    printf("%d\n",calculate(calculateShit,3,5));

    return(0);
}