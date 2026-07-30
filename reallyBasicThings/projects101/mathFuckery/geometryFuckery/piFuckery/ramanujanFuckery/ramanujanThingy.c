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

    BigInt denominantor = { 0 };
    int_32ToBigInt(&denominantor, 396);
    
    BigInt res = { 0 };
    int_32ToBigInt(&res, 396);
    


    double x = sqrty(8)/9801; //The constant multiplier before Sigma notation in the equation
    //My casio calc says: 0.00028858556 and my sqrty nods in agreement
    printf("%.10lf\n",x);
    //I realized I didn't implement a printBigNum function so...I'll be going back that brb...
    
    int k = 0;
    //My brain really says no and it's 3AM...sorry I forgot my bigNum factorial in the other repo lmfao
    /*
        but idea is 
        bigFloatFactorial(&numerator,4k);
        bigFloatMul(&numerator,(26390n+1103));

        then the rest is the denominantor which is same shit but with 4th power so I might need to add bigFloat/bigInt pow() to the API first...
    
    */
    

    for (; k < 4;k++) {
        bigIntFactorial(&bigInt, 4*k);      //Numerator part
        bigIntMulUInt_32(&bigInt, (26390*k+1103));
        for (size_t i = 0;i < 4*k; i++ ) {
            bigIntMulFFT(&denominantor, &res, &denominantor);        //I won't bother to create a pow function
            //But I guess I need a bigIntDivBigInt() that retrurns bigFlaot
        }
        
    }

    printBigInt(&bigInt);
    printf("\n");
    printBigInt(&denominantor);
    printf("\n");
    printBigInt(&res);
    printf("\n");
    

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