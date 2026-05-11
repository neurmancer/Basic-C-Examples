#include <stdio.h>
#include <math.h>

//This file requires -lm as you compile


int isPrime(int val);


int main(void)
{

   for (int i = 0;i < 55;i++) {
        if (isPrime(i)) {
            printf("%d is prime bruh\n",i);
        }
   }



    return(0);
}


int isPrime(int val)
{

    if(val < 0)
    {
        printf("Bro enter something positive\n");
        return(-1);
    }

    if (val < 6) {
        switch (val) {
            case 2:
                return(1);
                break;
            case 3:
                return(1);
                break;
            case 5:
                return(1);
                break;

            default:
                return(0);
                break;
        }
    }
    if (val % 6 == 1 || val % 6 == 5) {

        int is_prime = 0;
        for (int i = 3; i <= val; i += 2) 
        {   
            is_prime = 1;
            int sqrt_i = (int)ceil(sqrt((double)i)+1);

            for (int j = 2; j < sqrt_i; j++) 
            {     
                if (i % j == 0) {
                    is_prime = 0;
                    break;
                }
            }
        }

        if (is_prime) {
            return(1);
        }
        else {
            return(0);
        }
    }

    else {
        return(0);
    }
    return(0);
}