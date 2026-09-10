/*
    'Sup? I know I've promised the Ramanujan series first but...Big nums need a few more test before attempting to do it again so...
    Today's PI gamba is Liebniz series 


    this is gonna be a CLI pi fuckery nothing big or fancy just pi estimation spitting into terminal 

*/

#ifndef INT_MAX
    #define INT_MAX (~0u) >> 1
#endif
//I don't wanna deal with IEEE754 problems so no UINT_MAX this time floats bitching
#include <inttypes.h>
#include <stdio.h>

#ifndef TOGGLE
    #define TOGGLE 0    //Yeah public service for pi gamba addicts now you can watch it
#endif

int main(void)
{
    int upper_limit = INT_MAX;
    int numerator = 0;
    long double result = 0; 
    for(unsigned int i = 0; i < upper_limit; i++)
    {
        if (!(i % 2)) { numerator = 1; }
        else { numerator = -1;}

        result+= ((long double)numerator / ((2*i)+1)); 
        if (TOGGLE) {
            printf("%.20LF\n",4.L*result);   
        }
    }
    result*=4.L;  //This series gives us pi/4 so we need to mulitply
    printf("Result:%.20LF",result);


    return(0);
}