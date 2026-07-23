#include <stdio.h>

#define UPPER 500


int main(void)
{
	for(int i = 1; i <= UPPER;i++)
	{
		if (i % 3 == 0)
		{
			if (i % 5 == 0)
			{
				printf("%d : FizzBuzz!\n",i);
			}
			else {printf("%d : Fizz!\n",i);}
		}

		else if (i % 5 == 0)
		{
			printf("%d : Buzz!\n",i);
		}
	}


	return(0);
}
