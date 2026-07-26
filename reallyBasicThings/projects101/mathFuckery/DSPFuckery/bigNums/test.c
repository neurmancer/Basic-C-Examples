#include <stdio.h>
#include "bignums.h"



/*
        Sup? this is a test clause for my fresh big num lib and it seemed like it fucking passed the TEST...
        This subfolder won't have commentary more than it needs to since...it was a hell even for the creator(me lulz)
        
        So what I've done so far:
            Implemented:
                0- bignum zero init
                1- bignum+int
                2- bignum * int
                3- int to bignum
                4- string to bignum
                5- bignum mod and division
                6- bignum get bit
                7- bignum mul with FFT 
                


*/



/* helper to print a BigInt in hex (most-significant limb first) */

void bigIntPrintHex(const BigInt *a);

int main(void) {
    BigInt a, b, res, copy;
    uint32_t rem;

    /* ---------- 1. string conversion & add ---------- */
    printf("=== Test: string conversion & addition ===\n");
    bigIntFromString(&a, "123456789");
    bigIntFromString(&b, "987654321");
    printf("a = "); bigIntPrintHex(&a);
    printf("b = "); bigIntPrintHex(&b);

    // add b to a (we'll just do it manually with a loop of adds)
    // or we can implement a full add; for now we test single-word add.
    bigIntAddUInt_32(&a, 1);
    printf("a + 1 = "); bigIntPrintHex(&a);

    /* ---------- 2. mul/div/mod by uint32 ---------- */
    printf("\n=== Test: mul/div/mod by 32-bit ===\n");
    bigIntFromString(&a, "1000000000000");   // 10^12
    printf("a = "); bigIntPrintHex(&a);

    bigIntMulUInt_32(&a, 12345);
    printf("a * 12345 = "); bigIntPrintHex(&a);

    copy = a;   // keep a copy for modulo test
    rem = bigIntDivUInt32(&a, 1000);
    printf("after div by 1000: "); bigIntPrintHex(&a);
    printf("remainder = %u\n", rem);

    rem = bigIntModUInt32(&copy, 1000);
    printf("mod 1000 of original = %u\n", rem);

    /* ---------- 3. get bit ---------- */
    printf("\n=== Test: get bit ===\n");
    bigIntFromString(&a, "128");  // binary: 10000000
    printf("a = "); bigIntPrintHex(&a);
    printf("bit 0 = %d\n", bigIntGetBit(&a, 0));   // 0
    printf("bit 7 = %d\n", bigIntGetBit(&a, 7));   // 1
    printf("bit 8 = %d\n", bigIntGetBit(&a, 8));   // 0

    /* ---------- 4. FFT multiplication ---------- */
    printf("\n=== Test: FFT multiplication ===\n");

    // multiply two medium numbers
    bigIntFromString(&a, "12345678901234567890");
    bigIntFromString(&b, "98765432109876543210");
    printf("a = "); bigIntPrintHex(&a);
    printf("b = "); bigIntPrintHex(&b);

    if (bigIntMulFFT(&res, &a, &b) == 0) {
        printf("a * b = "); bigIntPrintHex(&res);
    } else {
        printf("FFT multiplication overflowed!\n");
    }

    // multiply by zero
    bigIntFromString(&a, "0");
    bigIntFromString(&b, "99999999999999999999");
    if (bigIntMulFFT(&res, &a, &b) == 0) {
        printf("0 * big = "); bigIntPrintHex(&res);  // should be 0x0 size 1
    }

    // multiply with result that fits in one limb
    bigIntFromString(&a, "65536");     // 2^16
    bigIntFromString(&b, "65536");
    if (bigIntMulFFT(&res, &a, &b) == 0) {
        printf("2^16 * 2^16 = "); bigIntPrintHex(&res);  // 0x100000000 (2^32)
    }

    // test that carry propagation works
    bigIntFromString(&a, "4294967295");     // 2^32 - 1
    bigIntFromString(&b, "4294967295");
    if (bigIntMulFFT(&res, &a, &b) == 0) {
        printf("(2^32-1)^2 = "); bigIntPrintHex(&res);
        // expected: 0xFFFFFFFE00000001
    }

    return(0);
}


void bigIntPrintHex(const BigInt *a) {
    printf("0x");
    for (int i = a->size - 1; i >= 0; i--) {
        printf("%08x", a->limbs[i]);
    }
    printf("  (size=%d)\n", a->size);
}