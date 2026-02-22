#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*      This program compare 1 bits in two number if a has more returns positive value otherwise negative and 0 if same*/

int cmp_popCounts(int a,int b)
{
    int countA = 0;
    int countB = 0;
    while (a)
    {
        a&=(a-1);
        countA++;
    }
    while (b)
    {
        b&=(b-1);
        countB++;
    }
    return(countA-countB);
}


int main(void)
{

    srand(time(NULL));
    int a,b;
    for (size_t i = 0; i < 10; i++)
    {
        a = rand() % 101;
        b = rand() % 101;
        printf("A:%d\tB:%d\tRes:%d\n",cmp_popCounts(a,b));
    }
    return(0);
}