#include <stdio.h>
#include <math.h>
#include <limits.h>

int main(void) {
    int count;
    printf("How many primes do you want starting from 2? ");
    if (scanf("%d", &count) != 1 || count < 1) {
        printf("Bro enter a positive number, come on...\n");
        return 1;
    }

    printf("2\n");
    int found = 1;           

    for (int i = 3; found < count; i += 2) 
	{   
        int is_prime = 1;
        int sqrt_i = (int)ceil(sqrt((double)i));

        for (int j = 2; j < sqrt_i; j++) 
		{     
            if (i % j == 0) {
                is_prime = 0;
                break;
            }
        }

        if (is_prime) {
            printf("%d\n", i);
            found++;
        }
    }

    return 0;
}