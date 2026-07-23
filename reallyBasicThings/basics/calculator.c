#include <limits.h>
#include <stdio.h>


#define sumA(a, b) _Generic((a), \
    int: _Generic((b), \
        int: sum, \
        float: sumf \
    ), \
    float: _Generic((b), \
        int: sumf, \
        float: sumf \
    ) \
)(a, b)


#define subA(a, b) _Generic((a), \
    int: _Generic((b), \
        int: sub, \
        float: subf \
    ), \
    float: _Generic((b), \
        int: subf, \
        float: subf \
    ) \
)(a, b)

#define mulA(a, b) _Generic((a), \
    int: _Generic((b), \
        int: mul, \
        float: mulf \
    ), \
    float: _Generic((b), \
        int: mulf, \
        float: mulf \
    ) \
)(a, b)



/*
            Sup? I realized(or realised for UKians ) I never built a CLI basic calculator and here we are trying to build one....
            
            Supported shit:
            0-Addition
            1-Subtraction
            2-Division
            3-Multipication 
            and yeah I am purely doing this to see wtf is the _Generic thingy

            this is the shitties calc you can see, go buy a casio one they have fancy graphs and shit


            Here is a bug full-filled (by copy-paste shit) calculator implementation where I didn't evne try to run...
            This is an explanation why I don't do those kind of things...because I FUCKING CAN'T
*/


int sum(int a,int b);
float sumf(float a,float b);

int sub(int a,int b);
float subf(float a,float b);

int mul(int a,int b);
float mulf(float a,float b);

float divf(float a,float b);


int main(void)
{

    int ans = 0;
    printf("Tell me the operation you want bruh\1) +\n2) -\n3) *(or x if you fancy)\n4) /\n Gimme:");
    fflush(stdout);
    if(scanf(" %d", &ans) != 1)
    {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {/*Nothing to see bruh*/}
        printf("Bruh you fucked up pressing digits really?");
        return(-1);
    }

    printf("Gimme just TWO numbers: ");
    fflush(stdout);
    float a,b;
    if (scanf("%f %f",&a,&b) < 2)
    {
        int c; //c is int because EOF is fucking int for some reason...go ask Dennis for why
        while ((c = getchar()) != '\n' && c != EOF) {/*Nothing to see bruh*/}
        printf("Bruh you fucked up basic arithmatics\n");
        return(-2);
    }
    float res = 0;
    switch (ans) {
        case 1:
            res = sumA(a,b);
            break;
        case 2:
            res = subA(a, b);
            break;
        case 3:
            res = subA(a, b);
            break;
        case 4:
            res = divf(a, b);
            break;
        default:
            printf("Really bruh?");
    }

    printf("Your result in float bruh: %f",res);
    //And this file explains why I don't fucking do calculators and to-do apps I guess... 'CUZ I FUCKING CANT
    return(0);
}

int sum(int a,int b)
{
    return(a+b);
}

float sumf(float a,float b)
{
    return(a+b);
}

int sub(int a,int b)
{
    return(a-b);
}

float subf(float a,float b)
{
    return(a-b);
}

int mul(int a,int b)
{
    return(a*b);
}
float mulf(float a,float b)
{
    return(a*b);
}

float divf(float a,float b)
{
    if (!b) {
        return(INT_MIN);
    }
    else {
        return(a/b);
    }
}


