

/*

    Sup? This one will about logic gates so go study some gates before dropping by lol

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DATA_SIZE ((float)sizeof(train)/(sizeof(train[0])))

//OR gate thingy
float train[][3] = {
    {0,0,0},
    {1,0,1},
    {0,1,1},
    {1, 1,1},
};

float cost(float w1, float w2);
float randFloat(void);

int main(void)
{
    srand(1368953);

    float w1 = randFloat();
    float w2 = randFloat();
    float eps = 1e-3;
    float rate = 1e-3;

    for (size_t i = 0;i < 2200;i++) {    
        printf("w1 = %f\tw2 = %f\t\n",w1,w2);
        float c = cost(w1,w2);
        printf("Cost: %f\n",c);

        float dW1 = (cost(w1+eps, w2) - c)/eps;
        float dW2 = (cost(w1+eps, w2) - c) / eps;
        w1 -= rate*dW1;
        w2 -= rate*dW2;
    }
    


    return(0);
}


float cost(float w1 , float w2 )
{   
    float result = 0.0f;
    for(size_t i = 0;i < DATA_SIZE; i++)
    {
        float x1 = train[i][0];
        float x2 = train[i][1];
        float y = x1*w1 + x2*w2;
        float offset = y - train[i][2];
        result += offset*offset;
    }    
    
    result /= (DATA_SIZE);
    return(result);
}

float randFloat(void)
{
    return((float)rand() / RAND_MAX);
}