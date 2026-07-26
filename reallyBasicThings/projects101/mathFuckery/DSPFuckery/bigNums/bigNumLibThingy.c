/*
        Sup? this will have less commentary since this is more like a project side-quest for Tupper's self-referantial formula bullet-point
        Idea is simple make C stop bitching about big nums

        Important shit to know: 
        I'll be using Little-endian to store shit to make carry propagation natural
        I'll be using my own FFT (an enhanced version that's able to handle non-power-of-two)

*/

#include <string.h>     //For memset
#include <stdlib.h>     //For Dyanmic memory shit

#include "complexFFT.h"
#include "bignums.h"

#define MAX_LIMBS 64 // 64 * 32bits (int standard) = 2048 bits...hope that's gonna be enough


void bigIntZero(BigInt *a) {
    memset(a->limbs, 0, sizeof(a->limbs));
    a->size = 1;            // value 0 represented as 1 limb
}

void int_32ToBigInt(BigInt *a, uint32_t val) {
    bigIntZero(a);
    a->limbs[0] = val;
    a->size = 1;
}


int bigIntAddUInt_32(BigInt *a, uint32_t b) {
    uint64_t carry = b;
    for (int i = 0; carry > 0 && i < MAX_LIMBS; i++) {
        carry += a->limbs[i];
        a->limbs[i] = (uint32_t)carry;
        carry >>= 32;
    }
    // update size (largest index with non-zero limb)
    while (a->size > 1 && a->limbs[a->size-1] == 0)
        a->size--;
    if (carry) {
        if (a->size < MAX_LIMBS) {
            a->limbs[a->size] = (uint32_t)carry;
            a->size++;
        }
        else {
            return(-1);     //Overflow check
        }
    }
    return(0);
}


// a *= b, b is a 32-bit integer
int bigIntMulUInt_32(BigInt *a, uint32_t b) {
    uint64_t carry = 0;
    for (int i = 0; i < a->size; i++) {
        carry += (uint64_t)a->limbs[i] * b;
        a->limbs[i] = (uint32_t)carry;
        carry >>= 32;
    }
    while (carry > 0) {
        if (a->size < MAX_LIMBS) {        
            a->limbs[a->size++] = (uint32_t)carry;
            carry >>= 32;
        }
        else {
            return(-1); //Overflow check
        }
    }
    return(0);
}


// a = a / divisor; return remainder


int bigIntFromString(BigInt *a, const char *dec_str) {
    bigIntZero(a);
    while (*dec_str) {
        if(bigIntMulUInt_32(a, 10)) { return(-1); }
        if(bigIntAddUInt_32(a, *dec_str - '0')){ return(-1) ;}
        dec_str++;
    
    }
    return(0);
}


uint32_t bigIntModUInt32(const BigInt *a, uint32_t divisor) {
    uint64_t remainder = 0;
    for (int i = a->size - 1; i >= 0; i--) {
        remainder = (remainder << 32) | a->limbs[i];
        remainder %= divisor;
    }
    return((uint32_t)remainder);
}

uint32_t bigIntDivUInt32(BigInt *a, uint32_t divisor) {
    uint64_t remainder = 0;
    for (int i = a->size - 1; i >= 0; i--) {
        remainder = (remainder << 32) | a->limbs[i];
        a->limbs[i] = (uint32_t)(remainder / divisor);
        remainder %= divisor;
    }
    // trim leading zeros (I mean...please do)
    while (a->size > 1 && a->limbs[a->size-1] == 0)
        a->size--;
    return (uint32_t)remainder;
}


int bigIntGetBit(const BigInt *a, int bit_index) {
    int limb = bit_index / 32;
    int bit  = bit_index % 32;
    if (limb >= a->size) return 0;
    return (a->limbs[limb] >> bit) & 1;
}

/* smallest power of two >= n */
static int next_pow2(int n) {
    int p = 1;
    while (p < n) p <<= 1;
    return p;
}

/*
    FFT-based multiplication: result = a * b.
    Splits each 32-bit limb into two 16-bit digits to stay inside double precision.
    Returns 0 on success, -1 if the result would need > MAX_LIMBS limbs.
    This is my first API design duh...

    DEV NOTES: FUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUCK My brain is getting squishy

*/
int bigIntMulFFT(BigInt *result, const BigInt *a, const BigInt *b) {
    int la = a->size;
    int lb = b->size;

    /* 1. Convert each limb into TWO 16-bit digits (low, high) */
    int digitsA = la * 2;
    int digitsB = lb * 2;
    int convLen = digitsA + digitsB - 1;     // linear convolution length
    int N = next_pow2(convLen);              // still pad to power-of-2 for speed
                                              // (fft_arbitrary will just call the fast path)

    /* 2. Allocate zero-padded complex arrays */
    complexNum *A = calloc(N, sizeof(complexNum));
    complexNum *B = calloc(N, sizeof(complexNum));
    if (!A || !B) {
        free(A); free(B);
        return(-1);
    }

    // Fill A (little-endian 16-bit digits)
    for (int i = 0; i < la; i++) {
        uint32_t limb = a->limbs[i];
        A[2*i].re     = (double)(limb & 0xFFFF);
        A[2*i + 1].re = (double)((limb >> 16) & 0xFFFF);
    }
    // Fill B
    for (int i = 0; i < lb; i++) {
        uint32_t limb = b->limbs[i];
        B[2*i].re     = (double)(limb & 0xFFFF);
        B[2*i + 1].re = (double)((limb >> 16) & 0xFFFF);
    }

    /* 3. Forward FFT */
    if (fft_arbitrary(A, N, 0) != 0 || fft_arbitrary(B, N, 0) != 0) {
        free(A); free(B);
        return(-1);
    }

    /* 4. Pointwise multiply */
    for (int i = 0; i < N; i++) {
        double re = A[i].re * B[i].re - A[i].im * B[i].im;
        double im = A[i].re * B[i].im + A[i].im * B[i].re;
        A[i].re = re;
        A[i].im = im;
    }

    /* 5. Inverse FFT */
    if (fft_arbitrary(A, N, 1) != 0) {
        free(A); free(B);
        return(-1);
    }

    /* 6. Temp buffer for rounded convolution + carry room */
    uint64_t *temp = calloc(convLen + 2, sizeof(uint64_t));
    if (!temp) {
        free(A); free(B);
        return(-1);
    }

    /* 7. Round (numbers are positive so +0.5 is fine) */
    for (int i = 0; i < convLen; i++) {
        // defensive: clamp tiny negative noise from floating-point error
        double v = A[i].re;
        if (v < 0.0) v = 0.0;
        temp[i] = (uint64_t)(v + 0.5);
    }

    /* 8. Carry propagation base 2^16 (one forward pass is enough) */
    for (int i = 0; i < convLen + 1; i++) {
        if (temp[i] >= 0x10000ULL) {
            temp[i + 1] += temp[i] >> 16;
            temp[i] &= 0xFFFFULL;
        }
    }

    // Find highest non-zero digit
    int lastDigit = convLen + 1;
    while (lastDigit > 0 && temp[lastDigit - 1] == 0)
        lastDigit--;

    /* Product is zero */
    if (lastDigit == 0) {
        bigIntZero(result);
        free(temp); free(A); free(B);
        return(0);
    }

    /* 9. Pack two 16-bit digits → one 32-bit limb */
    int outSize = (lastDigit + 1) / 2;
    if (outSize > MAX_LIMBS) {
        free(temp); free(A); free(B);
        return(-1);      // overflow
    }

    memset(result->limbs, 0, sizeof(result->limbs));
    for (int i = 0; i < lastDigit; i += 2) {
        uint32_t low  = (uint32_t)(temp[i] & 0xFFFF);
        uint32_t high = (i + 1 < lastDigit) ? (uint32_t)(temp[i + 1] & 0xFFFF) : 0;
        result->limbs[i / 2] = low | (high << 16);
    }

    result->size = outSize;
    while (result->size > 1 && result->limbs[result->size - 1] == 0)
        result->size--;

    free(temp);
    free(A);
    free(B);
    return(0);
}

/* Compare a and b. Returns -1 if a < b, 0 if a == b, 1 if a > b. don't expect better API guidline than that */
int bigIntCmp(const BigInt *a, const BigInt *b) {
    if (a->size != b->size)
        return((a->size > b->size) ? 1 : -1);

    for (int i = a->size - 1; i >= 0; i--) {
        if (a->limbs[i] != b->limbs[i])
            return (a->limbs[i] > b->limbs[i]) ? 1 : -1;
    }
    return(0);  // equal
}


/*
 * result = a - b
 * Returns 0 on success.
 * Returns -1 if b > a (subtraction would be negative).
 * Safe when result aliases a (in-place a = a - b), but NOT when result aliases b.
 */

int bigIntSub(BigInt *result, const BigInt *a, const BigInt *b) {
    // Only allow a >= b
    if (bigIntCmp(a, b) < 0)
        return(-1);

    // If result is not the same as a, copy a into result first
    if (result != a)
        memcpy(result->limbs, a->limbs, a->size * sizeof(uint32_t));

    int maxSize = a->size;
    uint64_t borrow = 0;

    // Subtract b's limbs
    for (int i = 0; i < b->size; i++) {
        uint64_t sub = (uint64_t)result->limbs[i] - (uint64_t)b->limbs[i] - borrow;
        result->limbs[i] = (uint32_t)sub;
        borrow = (sub >> 32) != 0;   // borrow if underflow occurred
    }

    // Propagate borrow through remaining limbs of a (if any)
    for (int i = b->size; borrow && i < maxSize; i++) {
        uint64_t sub = (uint64_t)result->limbs[i] - borrow;
        result->limbs[i] = (uint32_t)sub;
        borrow = (sub >> 32) != 0;
    }

    // Set size and trim leading zeros
    result->size = maxSize;
    while (result->size > 1 && result->limbs[result->size - 1] == 0)
        result->size--;

    return(0);
}