/*

    'Sup? if you don't know I got myself a bignum lib and managed the make it .so after a while of struggling 
    and this file is to test it...

    if you don't have the lib in path this won't compile...
*/

#include <bignums.h>
#include <stdio.h>


int main(void)
{

    setvbuf(stdout, NULL, _IONBF, 0);   //I forgot whether I add '\n' to print helpers so...here this is
    BigInt bi = { 0 };
    bigIntFromString(&bi, "123456789");
    bigIntAddUInt_32(&bi, 99999999);
    bigIntAddUInt_32(&bi, 99999999);
    bigIntAddUInt_32(&bi, 99999999);
    printBigInt(&bi);
    printf("\n");
    BigInt ba;
    bigIntFactorial(&ba, 100);

    printBigInt(&ba);
    printf("\n");   //apperantly I did not
    //Lol big nums go brrrrrrrrrrrrr
    return(0);
}