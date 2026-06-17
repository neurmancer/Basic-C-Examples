#include <stdio.h>


int isPrime(int val);

/* May the Satan take the wheels, forgive me cc for what I've sinned -Wa(ll)men.*/
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
        /* 
            Three things here...
            1-I do fucking know that using a stdio function in a purely mathametical function is stupid but so is asking if a negative prime or not
            2-I could've used abs() to make it positive then allow 
            or made the func unsigned int to eleminate this if block entirely OR just could've done val*=-1 which obviously I didn't
            3-EVEN IF I were to flip the negative to positive I would've done it like val = (~val+1) just for love of the game 
        */
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
