#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SAMPLE_SIZE 128


static double inline defArccos(double val)
{
    return(acos(val));
}
#define PI defArccos(-1.0) /*Yeah the reason I did this is typing #define acos(-1) would make the program caluclate for
             PI over and over instead of giving the value on compile time(or first seconds of running lol) if you don't forget -O2*/

             /*This is a intro for myself to remember (or learn) some math and get to the point where I can wield FFT efficently for future project ideas
                'But Neuro it's O(n^2) that's inefficient!'...First stfu you meatloaf I don't even know the Bachmann–Landau (Order) nation yet. Second so what? Can you implement a DFT tho? I think the same 
                so shut up and learn mwah(affectionately or how tf u spell it). 
             */

typedef struct {
    double re;
    double im; 
    /*Basically a data type for az+bi (where a and b are multipliers) 
    I do fucking now the correct notation for complex numbers is z = a+bi which a is the real part and bi is the imaginary but it's fucking too late for me to care about it. 
    and yeah I am writing this of an essay to prove that I am qualified enough to do that rather than fixing it...Deal with it!

    */
}complexNum; //to prevent complex.h to conjure for fuck's sake VS Code let me code alone I don't ned your hand holding


double *fill(int sampleSize);

int main(void)
{

    double *x = NULL; 
    x = fill(SAMPLE_SIZE);
    complexNum *X =(complexNum *) malloc(SAMPLE_SIZE*sizeof(complexNum)); 
    if (X == NULL) {return(-1);}

    for (int k = 0;k < SAMPLE_SIZE;k++) {
        complexNum temp = { 0 }; //Zero-Init, isn't necessary but just an habit of mine to code defensive 
        for (int n = 0;n < SAMPLE_SIZE;n++) {
            temp.re += x[n] * cos(2.0*PI * (double) k * (double) n/(double) SAMPLE_SIZE);
            temp.im += x[n] * (-sin(2.0*PI * (double) k * (double) n/(double) SAMPLE_SIZE));
        }
        X[k] = temp;
    }
    double mag = 0.0;
    for (int i = 0;i < SAMPLE_SIZE;i++) {
        printf("%2.5lf + (%.5lfi)\n",X[i].re,X[i].im);
        printf("Mag: %2.2lf\n",sqrt((X[i].re*X[i].re)+(X[i].im*X[i].im)));
        mag += sqrt((X[i].re*X[i].re)+(X[i].im*X[i].im));
    }
    printf("%2.2lf\n",mag);

    free(x);
    free(X);

    return(0);
}


double *fill(int sampleSize)
{
    double *x = (double *)malloc(sampleSize*(sizeof(double)));
    if (x == NULL) {return(NULL);}
    for (int n = 0;n < sampleSize;n++) {
        x[n] = cos(2.0*PI * 4.0 * (double)n/(double)sampleSize); 
    }

    return(x);
}