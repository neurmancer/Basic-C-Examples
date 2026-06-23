#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SAMPLE_SIZE 128 //Mandatory

/*      Here we are implementing FFT out of blue as I promised... in the DFT file...first don't fucking expect descriptions 
        Even I don't even fucking know how tf I've achieved this but I did...

        and yeah I am using the same fill function from dftThingy.c and SAMPE_SIZE macro and shit all the same after all this is still Fourier Transform
        just cursed AF

        important shit to know:
        1-This is fast af if you compare with DFT 
        2-This shit requires SAMPLE_SIZE to be a power of 2 
        3-The 'Fast as fuck' part can be calculated with O(n*log(n)) which if you know how graph-calculators work is close to a linear function for huge samples 
        with the side of log(n) diversion
*/


typedef struct {
    double re;
    double im;
} complexNum; //YK the beef with IDE if you've seen dftThingy.c

#define PI acos(-1.0) //I am not wrapping that this time since I can't be bothered by it (note to future self: STOP PUTTING ';'s on defines FOR FUCK SAKE )

void bit_reverse(complexNum *X, int N); //The index swapper thingy
void iterative_fft(complexNum *X, int N);

double *fill(int sampleSize);

int main(void) {
    double *x = fill(SAMPLE_SIZE);
    if (x == NULL){return(-1);}
    complexNum *X = (complexNum *)malloc(SAMPLE_SIZE * sizeof(complexNum));

    if (X == NULL){return(-1);} //Yeah in my universe every malloc error returns -1 so I can suffer in peace as I debug afterwards


    for (int i = 0; i < SAMPLE_SIZE; i++) {
        X[i].re = x[i];
        X[i].im = 0.0;
    }

    iterative_fft(X, SAMPLE_SIZE);

    double mag = 0.0;
    for (int i = 0; i < SAMPLE_SIZE; i++) {
        printf("%2.5lf + (%.5lfi)\n", X[i].re, X[i].im);
        double m = sqrt(X[i].re*X[i].re + X[i].im*X[i].im);
        printf("Mag: %2.2lf\n", m);
        mag += m;
    }
    printf("Mag Total(still no idea what mag is but calculating for the vibes): %2.5lf\n", mag);

    free(x);
    free(X); //Always free your shit 
    return(0);


    /*
    
        And here is my memory-safe certificate for the nerds
             
    ==502495== HEAP SUMMARY:
    ==502495==     in use at exit: 0 bytes in 0 blocks
    ==502495==   total heap usage: 3 allocs, 3 frees, 4,096 bytes allocated
    ==502495== 
    ==502495== All heap blocks were freed -- no leaks are possible
    ==502495== 
    ==502495== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
    [neuromancer@ARA-ARA projects101]$ 
    
    
    */
}

/* Bit reversal permutation thingy crucial for iterative FFT (at least that's what I told lol) 
    Simply seperating the the odds and evens so the inner butterfly shit happens (I AM NOT A MATHAMATICIAN OK?)
*/ 

void bit_reverse(complexNum *X, int N) {
    int j = 0;
    for (int i = 1; i < N; i++) {
        int bit = N >> 1;
        while (j >= bit) {
            j -= bit;
            bit >>= 1;
        }
        j += bit;
        if (i < j) { 
            //What this does basically swaps two indexs 
            complexNum temp = X[i];
            X[i] = X[j];
            X[j] = temp;
        }
    }
}

void iterative_fft(complexNum *X, int N) {
    bit_reverse(X, N);

    //That's where I lost control...verbose begins
    for (int len = 2; len <= N; len <<= 1) {           
        double angle = -2.0 * PI / len;                 
        complexNum wlen = {cos(angle), sin(angle)};    

        for (int i = 0; i < N; i += len) {             
            complexNum w = {1.0, 0.0};                 

            for (int j = 0; j < len/2; j++) {          // butterfly (or intersection idk. Tho it really looks like a street intersection if you look it up going like the fancy S we used to draw on the notebooks)
                complexNum u = X[i + j];
                complexNum v = {X[i + j + len/2].re * w.re - X[i + j + len/2].im * w.im,
                                X[i + j + len/2].re * w.im + X[i + j + len/2].im * w.re};
                X[i + j].re = u.re + v.re;
                X[i + j].im = u.im + v.im;
                X[i + j + len/2].re = u.re - v.re;
                X[i + j + len/2].im = u.im - v.im;

                // w*wlen for next butterfly
                double t_re = w.re * wlen.re - w.im * wlen.im;
                double t_im = w.re * wlen.im + w.im * wlen.re;
                w.re = t_re;
                w.im = t_im;
            }
        }
    }
}


//Same experimental function from dftThingy.c since I even forgot how the fuck I coded it but changed the freq to 7Hz to make it closer to 7.83Hz (For the vibez...iykyk)
double *fill(int sampleSize)
{
    double *x = (double *)malloc(sampleSize*(sizeof(double)));
    if (x == NULL) {return(NULL);}
    for (int n = 0;n < sampleSize;n++) {
        x[n] = cos(2.0* PI * 7.0 * (double)n/(double) sampleSize); 
    }

    return(x);
}