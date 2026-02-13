#include <stdio.h>
#include <math.h>
#include <limits.h>

int main(void)
{
	int count;
	printf("How many primes you want to see starting from 2:");
	fflush(stdout);
	scanf("%d",&count);
	int isPrime = 1;
	int iter = 0;
	printf("2\n");
	for(int i = 3;i < INT_MAX;i++)
	{
		for (int j = 2;j < ceil(sqrt((double) j)) ;j++)
		{
			if (i % j == 0)
			{
				isPrime = 0;
				break;
			}
		}	
		if (isPrime)
		{
			printf("%d\n",i);
			iter++;
		}
		
		if(iter == count-1)
		{
			break;
		}	
		i++;
	}
	return(0);

}
