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
        return(0);
    }

    if (val <= 3) {
        switch (val) {
            case 2:
                return(1);
                break;
            case 3:
                return(1);
                break;
            default:
                return(0);
                break;
        }
    }
    if (val % 6 == 1 || val % 6 == 5) {

        int is_prime = 0;
        for (int i = 3; i <= (int )ceil(sqrt(val))+1; i += 2) 
        {   
            is_prime = 0;
            if (val % i == 0) {
                return(0);
            }
            else {
                is_prime = 1;
            }
        }
        if (is_prime) {
            return(1);
        }
    }


    return(0);
}