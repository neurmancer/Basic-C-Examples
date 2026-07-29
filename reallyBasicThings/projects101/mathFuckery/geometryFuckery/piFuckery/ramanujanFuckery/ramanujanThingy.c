/*

    Luckly this won't be a raylib project but unluckly that will be a me project where I'll use my own fft to multiply shit in my own big num lib to 
    build this so this is the voltran of my side-quests anways...

    What's today's fuckery? MORE PI GAMBA...
    
    Honestly? Math looks like a fucking hell to go and I highly recommend you to use the given Makefile 
    this file is a tempalte for later use for now
*/

#include "bignums.h"
#include <math.h>

int main(void)
{

    BigInt bigInt = { 0 };
    bigIntZero(&bigInt);

    BigFloat bF = { 0 };
    bigFloatZero(&bF);

    double x = sqrt(8)/9801; //The constant multiplier before Sigma notation in the equation

    for (int k = 0; k < 1000;k++) {
        /*And that's where my brain gave up...*/
    }


    return(0);
}