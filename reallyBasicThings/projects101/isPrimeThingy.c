#include <stdio.h>


int isPrime(int val);


int main(void)
{

    for (int i = 10;i < 1000;i++) {
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

    if (val == 1){return(0);}

    if (val == 2 || val == 3) {return(1);}

    if (val % 6 == 1 || val % 6 == 5) {

        for (int i = 5; (i*i) <= val; i += 2) 
        {   
            if (val % i == 0) {
                return(0);
            }
        }
        return(1);
    }


    return(0);
}
