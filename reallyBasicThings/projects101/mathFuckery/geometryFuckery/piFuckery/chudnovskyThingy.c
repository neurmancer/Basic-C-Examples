/*

    'Sup you remember when I say the ramanujan fuckery was the ulimate pi gamba right?
    Well..I lied Chudnovsky gets there FASTER this ist he PI GAMBA ULTIMATE²

    Same bignums same things so...here you go...

    Requires bignums ABI 3:
        cc -O2 chudnovskyThingy.c -lbignums -o chudnovsky
        ./chudnovsky [decimal_places]    (default: 100)

    1/pi = 12 * sum((-1)^k * (6k)! * (13591409 + 545140134*k)
                   / ((3k)! * (k!)^3 * 640320^(3k + 3/2)))

    Binary splitting keeps the sum exact as T/Q, then:
        pi = 426880 * sqrt(10005) * Q/T.
    Derivation: https://www.craig-wood.com/nick/articles/pi-chudnovsky/

    well...after 50k digits it slows down but still better than M_PI tho
*/

#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <bignums.h>

#define DEFAULT_DIGITS 100
#define GUARD_DIGITS 16
/* Protect the term-count arithmatic 
by bignums. At this bound, the leaf factors 6*k-1 still fit in uint32_t ig...
*/

#define MAX_DIGITS (INT_MAX - GUARD_DIGITS)
#define CUBED_OVER_24 INT64_C(10939058860032000)

typedef struct {
    BigInt p, q, t;
} Split;


#define SPLIT_INIT {BIGINT_INIT, BIGINT_INIT, BIGINT_INIT}

static void splitDestroy(Split *value)
{
    bigIntDestroy(&value->p);
    bigIntDestroy(&value->q);
    bigIntDestroy(&value->t);
}

/* 
    So here is the nerdy stuff...

  Evaluate [a,b), with b > a. Every output is initialized by the caller.
  Leaves: P = (6k-5)(2k-1)(6k-1), Q = k^3 * 640320^3/24,
  T = (-1)^k * P * (13591409 + 545140134*k).
  The k=0 leaf instead has P=Q=1, T=13591409.
  Merge: P=Pl*Pr, Q=Ql*Qr, T=Tl*Qr + Pl*Tr. */


  static int binarySplit(Split *result, uint32_t a, uint32_t b)
{
    Split right = SPLIT_INIT;
    BigInt first = BIGINT_INIT, second = BIGINT_INIT;
    int status;

    if (b - a == 1) {
        if (a == 0) {
            status = int_32ToBigInt(&result->p, 1);
            if (status != 0) { goto rome; }
            status = int_32ToBigInt(&result->q, 1);
            if (status != 0) { goto rome; }
            status = int_32ToBigInt(&result->t, 13591409);
            goto rome;
        }

        status = int_32ToBigInt(&result->p, 6u * a - 5u);
        if (status != 0) { goto rome; }
        status = bigIntMulUInt_32(&result->p, 2u * a - 1u);
        if (status != 0) { goto rome; }
        status = bigIntMulUInt_32(&result->p, 6u * a - 1u);
        if (status != 0) { goto rome; }

        status = bigIntFromInt64(&result->q, CUBED_OVER_24);
        if (status != 0) { goto rome; }
    
        for (int i = 0; i < 3; i++) {
            status = bigIntMulUInt_32(&result->q, a);
            if (status != 0) { goto rome; }
        }

        /* This coefficient fucks uint32_t already at k=8. */
        status = bigIntFromInt64(&first, INT64_C(13591409) + INT64_C(545140134) * a);
        if (status != 0) { goto rome; }
        status = bigIntMul(&result->t, &result->p, &first);
        if (status != 0) { goto rome; }
        if (a & 1u) { bigIntNegate(&result->t); }
    } 
    
    else {
        uint32_t middle = a + (b - a) / 2;
        status = binarySplit(result, a, middle);
        if (status != 0) { goto rome; }
        status = binarySplit(&right, middle, b);
        if (status != 0) { goto rome; }

        /* Use the original left P and T before replacing them. bigIntMul
         * uses the library's smarterFFT.c */

        status = bigIntMul(&first, &result->t, &right.q);
        if (status != 0) { goto rome; }
        
        status = bigIntMul(&second, &result->p, &right.t);
        if (status != 0) { goto rome; }
        
        status = bigIntAdd(&result->t, &first, &second);
        if (status != 0) { goto rome; }
        
        status = bigIntMul(&first, &result->p, &right.p);
        if (status != 0) { goto rome; }
        
        bigIntSwap(&result->p, &first);
        
        status = bigIntMul(&first, &result->q, &right.q);
        if (status != 0) { goto rome; }
        
        bigIntSwap(&result->q, &first);
    }

rome:
    splitDestroy(&right);
    bigIntDestroy(&first);
    bigIntDestroy(&second);
    return(status);
}

/* ABI 3 exposes the mantissa but has no BigInt-to-BigFloat constructor.
 * Copy its magnitude with exponent zero, then normalize at our precision.
 * Swap only on success so errors leave the destination unchanged. */
static int floatFromInt(BigFloat *result, const BigInt *value, size_t precision)
{
    BigFloat converted = BIGFLOAT_INIT;
    int status = bigIntCopy(&converted.mantissa, value);
    if (status == 0) {
        converted.sign = value->sign;
        converted.mantissa.sign = 1;
        status = bigFloatSetPrecision(&converted, precision);
    }
    if (status == 0) { bigFloatSwap(result, &converted); }
    bigFloatDestroy(&converted);
    return(status);
}

static int gamba(BigFloat *pi, uint32_t terms, size_t precision)
{
    Split series = SPLIT_INIT;
    BigFloat numerator = BIGFLOAT_INIT, denominator = BIGFLOAT_INIT;
    BigFloat root = BIGFLOAT_INIT, factor = BIGFLOAT_INIT;
    int status = binarySplit(&series, 0, terms);
    if (status != 0) { goto cleanup; }

    status = floatFromInt(&numerator, &series.q, precision);
    if (status != 0) { goto cleanup; }
    status = floatFromInt(&denominator, &series.t, precision);
    if (status != 0) { goto cleanup; }
    splitDestroy(&series);

    status = bigFloatSetPrecision(&factor, precision);
    if (status != 0) { goto cleanup; }
    status = bigFloatFromUint32(&factor, 10005);
    if (status != 0) { goto cleanup; }
    status = bigFloatSqrt(&root, &factor, precision);
    if (status != 0) { goto cleanup; }
    status = bigFloatFromUint32(&factor, 426880);
    if (status != 0) { goto cleanup; }
    status = bigFloatMul(&root, &root, &factor);
    if (status != 0) { goto cleanup; }
    status = bigFloatMul(&numerator, &numerator, &root);
    if (status != 0) { goto cleanup; }
    status = bigFloatDiv(pi, &numerator, &denominator, precision);

cleanup:
    splitDestroy(&series);
    bigFloatDestroy(&numerator);
    bigFloatDestroy(&denominator);
    bigFloatDestroy(&root);
    bigFloatDestroy(&factor);
    return(status);
}

int main(int argc, char **argv)
{
    int digits = DEFAULT_DIGITS;
    if (argc > 2) {
        fprintf(stderr, "Usage: %s [decimal_places: 1..%d]\n", argv[0], MAX_DIGITS);
        return(EXIT_FAILURE);
    }
    if (argc == 2) {
        char *end;
        errno = 0;
        long requested = strtol(argv[1], &end, 10);
        if (errno != 0 || end == argv[1] || *end != '\0' ||
            requested < 1 || requested > MAX_DIGITS) {
            fprintf(stderr, "Decimal places must be an integer from 1 to %d\n", MAX_DIGITS);
            return(EXIT_FAILURE);
        }
        digits = (int)requested;
    }

    /* About 14.18 decimal digits per term; use 14 plus guard digits.
     * 10/3 bits per decimal digit conservatively determines 32-bit limbs. */
    uint32_t terms = (uint32_t)((digits + GUARD_DIGITS) / 14 + 1);
    size_t precision = (size_t)((((uint64_t)digits + GUARD_DIGITS) * 10 + 95) / 96);
    BigFloat pi = BIGFLOAT_INIT;
    int status = gamba(&pi, terms, precision);
    if (status != 0) {
        bigFloatDestroy(&pi);
        fprintf(stderr, "Chudnovsky calculation failed (bignums status: %d)\n", status);
        return(EXIT_FAILURE);
    }

    printf("Chudnovsky series with binary splitting (%u terms, %d decimal places):\n",
           (unsigned)terms, digits);
    status = printBigFloat(&pi, (size_t)digits);
    bigFloatDestroy(&pi);
    if (status != 0) {
        fprintf(stderr, "Could not print pi (bignums status: %d)\n", status);
        return(EXIT_FAILURE);
    }
    putchar('\n');
    if (fflush(stdout) == EOF || ferror(stdout)) {
        fprintf(stderr, "Could not write the result\n");
        return(EXIT_FAILURE);
    }
    return(0);
}
