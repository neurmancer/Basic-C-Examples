/*
        Sup? what's today's fuckery?
        Forcing machine into thinking in short...

        Long version: We're trying to build a Machine Learning algorithm (probably it's backpropagation and shit) so I can split labors with it lulz
    
        the unofficial title for this file's training my last brain cell

        Since this shit is new to me I am following the path of tsoding daily ML playlist
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

float randFloat(void);
float cost(float w, float b);

float train[][2] = {
    {0, 0},
    {1, 2},
    {2, 4},
    {3, 6},
    {4, 8}
};

#define DATA_SIZE sizeof(train)/sizeof(train[0])

int main(void)
{
    srand(time(NULL)^ getpid());
    //Y = x*w input times paramter thingy
    float rate = 1e-3; //Learining rate for the machine(Honestly it would be fucking easier to send it to University bruh)
    float eps = 1e-3;   //Time to auotmate this with more calculus!!!
    float bias = 5.0f;

    float w = randFloat()*15.0f;

    for (size_t i = 0;i < 1000000; i++) {
        float c = cost(w, bias);
        float dW = (cost(w+eps,bias)-c)/eps;    //You 'member the definition of derivative right? That's kinda it lol you can call it just slope, finite differance etc.
        float dB = (cost(w,bias+eps)-c)/eps;
        w -= dW*rate;
        bias -= rate*dB;
        printf("cost: %f\tW:%f\tB:%f\n ",cost(w, bias),w,bias);
    }   //Damn it gets smarter

    printf("%f\n",w);
    

    return(0);
}

float randFloat(void)
{
    return((float)rand() / RAND_MAX);
}

float cost(float w,float b)
{   
    float result = 0.0f;
    for(size_t i = 0;i < DATA_SIZE; i++)
    {
        float x = train[i][0];
        float y = x*w + b;  //w is the tuning paramter type shit dunno yet...
        float offset = y - train[i][1];
        result += offset*offset;
            /*
            Two reasons to use offset^2 
            First = negative handling 
            Second = it gets huge. fast.AF. No mistake has forgiven.
        */
        //printf("Actual Y:%f\t expected Y: %f\n",y, train[i][1]);
    }    
    
    result /= (float)DATA_SIZE;
    return(result);
}