/*

    'Sup? This is the season finale of the repo till next summer... And I wanted to finish it with this project I've been teasing for months

    Shit to know: 
        This one's gonna be the ultimate PI gamba 
        I'll be using my own big nums to hold the values and shit and you'll see include with <bignums.h> instead of "bignums.h"
        since I have it installed in the path and I highly recommend you to do too if you wanna run this code but you can use it with local builds and shit with a few tweaks

        So...shamless self-promo: https://github.com/neurmancer/Big-Nums go read this 

        and it requires bignums ABI 3 and -lbignums to compile lol
        cc ramanujanThingy.c -lbignums -o ramanujan
        ./ramanujan [decimal_places]    (default: 100)

        1/pi = (2*sqrt(2)/9801) * sum((4k)!*(1103+26390k) / ((k!)^4*396^(4k)))
        The sum starts at k=0. Flip the result at the end to get pi.
        Limbs are dynamically allocated now; precision is in 32-bit limbs.


    btw 2 hours after  finishing this there is an Pi gamba ultimate²

    The big nums now use dynamic allocation instead of stack based limbs.
*/

#include <stdio.h>
#include <stdlib.h>  //strtol for the optional decimal-place count
#include <errno.h>
//Requires my own fucking LIB
#include <bignums.h>


#define DEFAULT_DIGITS 100
#define GUARD_DIGITS 16

#define MAX_DIGITS ((int)(7u * ((UINT32_MAX - 1103u) / 26390u) - GUARD_DIGITS))

static int gamba(BigFloat *pi, int terms, size_t precision);

int main(int argc, char **argv)
{
    int digits = DEFAULT_DIGITS;
    if (argc > 2) {
        fprintf(stderr, "Usage: %s [decimal_places: 1..%d]\n", argv[0], MAX_DIGITS);
        return(13);
    }
    if (argc == 2) {
        char *end;
        errno = 0;
        long requested = strtol(argv[1], &end, 10);
        if (errno != 0 || end == argv[1] || *end != '\0' ||
            requested < 1 || requested > MAX_DIGITS) {
            fprintf(stderr, "Decimal places must be an integer from 1 to %d\n", MAX_DIGITS);
            return(13);
        }
        digits = (int)requested;
    }

    //The series gains about 8 digits per term so we're using 7 and and a condom
    int terms = (digits + GUARD_DIGITS) / 7 + 1;
    //Rounding the shit up
    /* 10/3 is a conservative upper bound on bits per decimal digit. */
    size_t precision = (((size_t)digits + GUARD_DIGITS) * 10 + 95) / 96;
    BigFloat pi = BIGFLOAT_INIT;
    int status = gamba(&pi, terms, precision);
    if (status != 0) {
        bigFloatDestroy(&pi);
        fprintf(stderr, "Bignums needs degree ig... (shit that went sideways: %d)\n", status);
        return(-13);
    }

    printf("Ramanujan series (%d terms, %d decimal places):\n", terms, digits);
    status = printBigFloat(&pi, (size_t)digits);
    bigFloatDestroy(&pi);

    if (status != 0) {
        fprintf(stderr, "Could not print pi (bignums status: %d)\n", status);
        return(-53);
    }
    
    putchar('\n');

    if (fflush(stdout) == EOF || ferror(stdout)) {
        fprintf(stderr, "Could not write the result\n");
        return(-13);
    }

    return(0);
}

static int gamba(BigFloat *pi, int terms, size_t precision)
{
    BigFloat coefficient = BIGFLOAT_INIT, sum = BIGFLOAT_INIT;
    BigFloat term = BIGFLOAT_INIT, factor = BIGFLOAT_INIT;
    BigFloat denominator = BIGFLOAT_INIT, sqrt_two = BIGFLOAT_INIT;
    BigFloat *values[] = {&coefficient, &sum, &term, &factor, &denominator, &sqrt_two};
    int status;

    /* Add and multiply round to the destination's precision in ABI 3. */
    for (size_t i = 0; i < sizeof(values) / sizeof(values[0]); i++) {
        status = bigFloatSetPrecision(values[i], precision);
        if (status != 0) { goto cleanup; }
    }

    status = bigFloatFromUint32(&coefficient, 1); //k=0: 0! / ((0!)^4 * 396^0) = 1.
    if (status != 0) { goto cleanup; }

    for (int k = 0; k < terms; k++) {
        status = bigFloatFromUint32(&factor, 1103u + 26390u * (uint32_t)k);
        if (status != 0) { goto cleanup; }

        status = bigFloatMul(&term, &coefficient, &factor);

        if (status != 0) { goto cleanup; }

        status = bigFloatAdd(&sum, &sum, &term);

        if (status != 0) { goto cleanup; }
        if (k == terms - 1) { break; }

        /*
            Instead of rebuilding enormous fucking factorials, update their ratio:
            c[k+1] = c[k] * (4k+1)(4k+2)(4k+3)(4k+4) / (396*(k+1))^4.
        */

        for (uint32_t j = 1; j <= 4; j++) {
            status = bigFloatFromUint32(&factor, 4u * (uint32_t)k + j);
            if (status != 0) { goto cleanup; }
            
            status = bigFloatMul(&coefficient, &coefficient, &factor);
            
            if (status != 0) { goto cleanup; }
        }

        status = bigFloatFromUint32(&factor, 396u * ((uint32_t)k + 1u));
        if (status != 0) { goto cleanup; }
        
        status = bigFloatMul(&denominator, &factor, &factor);
        if (status != 0) { goto cleanup; }
        
        status = bigFloatMul(&denominator, &denominator, &denominator);
        if (status != 0) { goto cleanup; }
        
        status = bigFloatDiv(&coefficient, &coefficient, &denominator, precision);
        if (status != 0) { goto cleanup; }
    }

    status = bigFloatFromUint32(&factor, 2);
    if (status != 0) { goto cleanup; }

    status = bigFloatSqrt(&sqrt_two, &factor, precision);
    if (status != 0) { goto cleanup; }
    
    status = bigFloatMul(&denominator, &sqrt_two, &factor);
    if (status != 0) { goto cleanup; }
    
    status = bigFloatMul(&denominator, &denominator, &sum);
    if (status != 0) { goto cleanup; }
    
    status = bigFloatFromUint32(&factor, 9801);
    if (status != 0) { goto cleanup; }

    status = bigFloatDiv(pi, &factor, &denominator, precision);


cleanup:
    for (size_t i = 0; i < sizeof(values) / sizeof(values[0]); i++) {
        bigFloatDestroy(values[i]);
    }
    return(status);
}
