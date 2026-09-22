/*

    'Sup? This gonna be quicky I'll make my own sin and cos implementation using Taylor series and shit so I can use them for my
    spinning ASCII Donut and just to try I'll be writing the math in LaTeX lol...


*/


#ifndef DBL_MAX
    #define DBL_MAX __DBL_MAX__
#endif

#define PI (3.14159265358979323846)
#define TWO_PI (2.0 * PI)
#define HALF_PI (0.5 * PI)

/*
    Inputs are in radians (duh...). Reduce to [-PI, PI] by subtracting decending
    powers-of-two multiples of TWO_PI then use symmetry to reach
    [-PI/2, PI/2], where the Taylor series converges much faster

    This simple reduction uses a rounded TWO_PI, so accuracy degrades for
    very large angles. Keep animation angles bounded for best results.
*/

static double reduce_angle(double x){
    if (x != x) { return(x); } 
    if (x > DBL_MAX || x < -DBL_MAX) { return(x - x); } //Infinity -> NaN.
    if (x >= -PI && x <= PI) { return(x); }

    double magnitude = x < 0.0 ? -x : x;
    double period = TWO_PI;

    //Scale up without overflow then halve down
    while (period <= magnitude / 2.0) { period *= 2.0; }
    
    while (period >= TWO_PI) {
        if (magnitude >= period) { magnitude -= period; }
        period *= 0.5;
    }

    if (magnitude > PI) { magnitude -= TWO_PI; }
    
    return(x < 0.0 ? -magnitude : magnitude);
}

double taylor_sin(double x){
    if (x == 0.0) { return(x); } //FYM negative zero tho?

    x = reduce_angle(x);

    if (x > HALF_PI) { x = PI - x; }
    else if (x < -HALF_PI) { x = -PI - x; }

    double x_squared = x*x;
    double term = x;
    double sum = term;

    //Math
    //t_n = -t_(n-1) * x^2 / ((2n)(2n+1)); through x^21/21!. (not exclamation mark it's factorial)
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

    //Math:
    //t_n = -t_(n-1) * x^2 / ((2n-1)(2n)); through x^20/20!.
    for (int n = 1; n <= 10; n++) {
        term *= -x_squared / ((2.0*n - 1.0) * (2.0*n));
        sum += term;
    }
    return(sign * sum);
}
