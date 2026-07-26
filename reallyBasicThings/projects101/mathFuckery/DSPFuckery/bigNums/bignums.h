#ifndef BIGNUM_H          //They say this indef thingy is a 'guard'
#define BIGNUM_H

#include <stdint.h>       // for uint32_t, uint64_t

#define MAX_LIMBS 64

typedef struct {
    uint32_t limbs[MAX_LIMBS];
    int size;
} BigInt;


void bigIntZero(BigInt *a);

void int_32ToBigInt(BigInt *a, uint32_t val);

uint32_t bigIntModUInt32(const BigInt *a, uint32_t divisor);

uint32_t bigIntDivUInt32(BigInt *a, uint32_t divisor);

int bigIntAddUInt_32(BigInt *a, uint32_t b);

int bigIntMulUInt_32(BigInt *a, uint32_t b);

int bigIntFromString(BigInt *a, const char *dec_str);

int bigIntGetBit(const BigInt *a, int bit_index);

int bigIntMulFFT(BigInt *result, const BigInt *a, const BigInt *b);

int bigIntCmp(const BigInt *a, const BigInt *b);

int bigIntSub(BigInt *result, const BigInt *a, const BigInt *b);

#endif