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

    I already implemented the cos and sin approximations using taylor series (cos_and_sinThingy.c) so I'll just copy-paste it here...

    I won't be explaining the math the author of the blog and creator of the project is way better than me go check the blog posts

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
#define K2 5.0f     //This is for the distance of the donut from the observer

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


typedef struct{
    double rotation[2];
    double depth_buf[BUFFER_SIZE];
    char buf[BUFFER_SIZE];

}RenderData;

void creat_frame(RenderData *renderer);

void draw_shit(const char *buf);


int main(void)
{

    setvbuf(stdout, NULL, _IONBF, 0);
    RenderData renderer = { 0 };

    renderer.rotation[0] += 0.9L;
    renderer.rotation[1] += 0.9L;  

    
    while (1) {
        
        creat_frame(&renderer);
        draw_shit(renderer.buf);

        renderer.rotation[0] += 0.1L;
        renderer.rotation[1] += 0.05L;  //Fine-tuned by my ass

        usleep(7200);
        
    }
    return(0);
}



void creat_frame(RenderData *renderer)
{
    for (size_t i = 0; i < BUFFER_SIZE; i++) {
        renderer->buf[i] = ' ';
    }

    memset(renderer->depth_buf, 0, BUFFER_SIZE*sizeof(double));

    double sin_first = taylor_sin(renderer->rotation[0]);
    double cos_first = taylor_cos(renderer->rotation[0]); 
    
    double sin_second = taylor_sin(renderer->rotation[1]);
    double cos_second = taylor_cos(renderer->rotation[1]);

    for (double theta = 0; theta < TWO_PI; theta+=0.07) {
        //The nested loops always fucks with my imagination...
        for (double phi = 0; phi < TWO_PI; phi += 0.01) {
            double sin_phi = taylor_sin(phi);
            double cos_phi = taylor_cos(phi);

            double sin_theta = taylor_sin(theta);
            double cos_theta = taylor_cos(theta);
            
            double circ_x = R2 + R1 * cos_theta;
            double circ_y = R1 * sin_theta;
            
            double x = circ_x * (cos_second * cos_phi + sin_first * sin_second * sin_phi) - circ_y * cos_first * sin_second;
            double y = circ_x * (sin_second * cos_phi - sin_first * cos_second * sin_phi) + circ_y * cos_first * cos_second;

            double z = K2 + cos_first * circ_x * sin_phi + circ_y * sin_first;  //The z-axis is where my brain leaves...

            double flip_z = 1.0L / z;

            int xp = (int)((double)WIDTH/2 + 30 * flip_z * x);  //I've casted double on WIDTH but dunno if it fucks with the result in an unwanted way...
            int yp = (int)((double)HEIGHT/2 - 15 * flip_z * y);  //OG code didn't cast

            int position = xp + (WIDTH * yp);

            float lux = 0.7f * sin_phi * cos_theta * sin_second - 0.2f * cos_phi * cos_theta * cos_second;
            int lux_idx = (int)((lux + 1.0f) * 4);
            
            if (lux_idx < 0){ lux_idx = 0; }
            if (lux_idx > 8){ lux_idx = 8; }

            if (yp >= 0 && yp < HEIGHT && xp >= 0 && xp < WIDTH && position >= 0 && position < BUFFER_SIZE && flip_z > renderer->depth_buf[position]) {
                renderer->depth_buf[position] = flip_z;
                renderer->buf[position] = DOPE_CHARS[lux_idx];
            }
        }   
    }
}

void draw_shit(const char *buf)
{

    printf("\033[H");     
    //Well it worked but not in a way I've expected...
    //Second update it does work but now I gotta add RGB, SIGINT handler and shit to clear the terminal etc...
    for (int i = 0; i < HEIGHT; i++) {
        char line[WIDTH + 1];
        
        memcpy(line, &buf[i * WIDTH], WIDTH);
        
        line[WIDTH] = '\0';
        printf("%s\n", line);
    }

}