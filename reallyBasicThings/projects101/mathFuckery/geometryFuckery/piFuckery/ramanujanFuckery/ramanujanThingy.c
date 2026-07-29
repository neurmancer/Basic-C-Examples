/*

    Luckly this won't be a raylib project but unluckly that will be a me project where I'll use my own fft to multiply shit in my own big num lib to 
    build this so this is the voltron of my side-quests anways...

    What's today's fuckery? MORE PI GAMBA...
    
    Honestly? Math looks like a fucking hell to go and I highly recommend you to use the given Makefile 
    this file is a tempalte for later use for now
*/

#include "bignums.h"
#include <stdio.h>
//#include <math.h> you know what? Fuck math.h we're going full my own crap mode 
//I'll finish this project with my own shit made out of pure spite blackjack and hookers 
double sqrty(unsigned int val);

typedef unsigned char uint8_t;

int main(void)
{

    BigInt bigInt = { 0 };
    bigIntZero(&bigInt);

    BigFloat bF = { 0 };
    bigFloatZero(&bF);

    double x = sqrty(8)/9801; //The constant multiplier before Sigma notation in the equation
    //My casio calc says: 0.00028858556 and my sqrty nods in agreement
    printf("%.10lf\n",x);
    //I realized I didn't implement a printBigNum function so...I'll be going back that brb...
    for (int k = 0; k < 1000;k++) {
        /*And that's where my brain gave up...*/
    }

    return(0);
}


double sqrty(unsigned int val)
{
    if (val == 0) { return(0.0l); }
    if (val == 1) { return(1.0l); }
    
    int msb = 0;
    unsigned int temp = val;
    while (temp >>= 1) msb++;

    int expon = msb/2;

    double z = (double) (1u << expon);    
    for (uint8_t i = 0; i < 8; i++) {  

        z = (z + val / z) * 0.5l;
    }
    
    return(z);
}