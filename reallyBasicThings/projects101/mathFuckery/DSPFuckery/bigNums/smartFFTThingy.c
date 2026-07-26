#include "complexFFT.h"
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

static void bit_reverse(complexNum *x, int n) {
    int j = 0;
    for (int i = 1; i < n; i++) {
        int bit = n >> 1;
        while (j >= bit) {
            j -= bit;
            bit >>= 1;
        }
        j += bit;
        if (i < j) {
            complexNum tmp = x[i];
            x[i] = x[j];
            x[j] = tmp;
        }
    }
}

void fft(complexNum *x, int n, int inverse) {
    bit_reverse(x, n);

    for (int len = 2; len <= n; len <<= 1) {
        double angle = -2.0 * M_PI / len * (inverse ? -1.0 : 1.0);
        complexNum wlen = {cos(angle), sin(angle)};

        for (int i = 0; i < n; i += len) {
            complexNum w = {1.0, 0.0};
            for (int j = 0; j < len/2; j++) {
                complexNum u = x[i + j];
                complexNum v = {
                    x[i + j + len/2].re * w.re - x[i + j + len/2].im * w.im,
                    x[i + j + len/2].re * w.im + x[i + j + len/2].im * w.re
                };

                x[i + j].re = u.re + v.re;
                x[i + j].im = u.im + v.im;
                x[i + j + len/2].re = u.re - v.re;
                x[i + j + len/2].im = u.im - v.im;

                double t_re = w.re * wlen.re - w.im * wlen.im;
                double t_im = w.re * wlen.im + w.im * wlen.re;
                w.re = t_re;
                w.im = t_im;
            }
        }
    }

    if (inverse) {
        double inv_n = 1.0 / n;
        for (int i = 0; i < n; i++) {
            x[i].re *= inv_n;
            x[i].im *= inv_n;
        }
    }
}