/*
    'Sup? This file where I declare that this is the season finale of this repo...For a long time and end of journey
    for me too... Next season will include the shells, bootloaders and vim clones I guess...(I hope it will) also
    I might finish ramanujan fuckery before dipping tho..

    Anyways what's today's CLI math fuckery?...well you know the ASCII donut right? it is the fuckery of today
    I remembered it's existence while fucking with raylib 3D cams and remembered this video: https://www.youtube.com/watch?v=sW9npZVpiMI&t=1s

    then found the original (I guess) donut.c creator's explanations... : https://www.a1k0n.net/2011/07/20/donut-math.html
    There are a few iterations of the donut.c since 2006 until 2021...They explain the math quite well so I'll be just following it 
    while impleneting a few different things too if I can without fucking the original concept...


    first idae is ditching the lib math since the original code (well an iteration of the original one does that so...why wouldn't I?)

    I already implemented the cos and sin approximations using taylor series so I'll just copy-paste it here...

*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
// #include <sys/ioctl.h> not yet tho...


#ifndef DBL_MAX
    #define DBL_MAX __DBL_MAX__  
#endif

//Math defines
#define PI (3.14159265358979323846)
#define TWO_PI (2.0 * PI)
#define HALF_PI (0.5 * PI)

//Chill defines
#define WIDTH 80
#define HEIGHT 24
#define BUFFER_SIZE (WIDTH*HEIGHT)  //Those are just place-holder I am planning to get the terminal x,y's with ioctl 

#define R1 1.0f     //Radiis? Radiuses? wtf is the plural of radius but anyways those r's are radiusS 
#define R2 2.0f
#define K2 3.0f     //This is for the distance of the donut from the observer

static double reduce_angle(double x){
    if (x != x) { return(x); } 
    if (x > DBL_MAX || x < -DBL_MAX) { return(x - x); } 
    if (x >= -PI && x <= PI) { return(x); }

    double magnitude = x < 0.0 ? -x : x;
    double period = TWO_PI;

    while (period <= magnitude / 2.0) { period *= 2.0; }
    
    while (period >= TWO_PI) {
        if (magnitude >= period) { magnitude -= period; }
        period *= 0.5;
    }

    if (magnitude > PI) { magnitude -= TWO_PI; }
    
    return(x < 0.0 ? -magnitude : magnitude);
}

double taylor_sin(double x){
    if (x == 0.0) { return(x); } //FYM negative zero tho (I'll leave this one)?

    x = reduce_angle(x);

    if (x > HALF_PI) { x = PI - x; }
    else if (x < -HALF_PI) { x = -PI - x; }

    double x_squared = x*x;
    double term = x;
    double sum = term;

    for (int n = 1; n <= 10; n++) {
        term *= -x_squared / ((2.0*n) * (2.0*n + 1.0));
        sum += term;
    }
    
    return(sum);
}

double taylor_cos(double x){
    x = reduce_angle(x);
    double sign = 1.0;
    if (x > HALF_PI) { x = PI - x; sign = -1.0; }
    else if (x < -HALF_PI) { x = -PI - x; sign = -1.0; }

    double x_squared = x*x;
    double term = 1.0;
    double sum = term;

    for (int n = 1; n <= 10; n++) {
        term *= -x_squared / ((2.0*n - 1.0) * (2.0*n));
        sum += term;
    }
    return(sign * sum);
}



const char DOPE_CHARS[] = " .:-=+*#@";  //I literally copied the same symbols from the code...


void creat_frame(float rotation_1, float rotation_2, char *buf, float *depth_buf);

void draw_shit(const char *buf);


int main(void)
{


    //well that's the initial draft...

    


    return(0);
}