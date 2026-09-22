/*

    'Sup? This gonna be quicky I'll make my own sin and cos implementation using Taylor series and shit so I can use them for my
    spinning ASCII Donut and just to try I'll be writing the math in LaTeX lol...


*/


#define PI  3.141592653589793238L
#define TWO_PI 6.283185307179586476L


double taylor_sin(double x){
    while (x > PI) { x -= TWO_PI; }
    while (x < -PI) { x += TWO_PI; }

    double x_cubed = x*x*x;
    double x_raised_to_fifth = x_cubed*x*x;
    double x_raised_to_seventh = x_raised_to_fifth*x*x;

    return(x - (x_cubed/6.l) + (x_raised_to_fifth/120.l) - (x_raised_to_seventh/5040.l));
}

double taylor_cos(double x){
    while (x > PI) { x -= TWO_PI; }
    while (x < -PI) { x += TWO_PI; }

    double x_squared = x*x;
    double x_raised_to_forth = x_squared*x*x;
    double x_raised_to_sixth = x_raised_to_forth*x*x;

    return(1.l - (x_squared/2.l) + (x_raised_to_forth/24.l) - (x_raised_to_sixth/ 720.l));
}

//They look correct tho... now here is the one part: Explanation in LaTeX


