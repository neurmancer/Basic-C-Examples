#include <stdio.h>
#include <stdlib.h>

/*
    Malloc() -> Memory allocation
    Realloc() -> Reallocation
    Calloc() -> Cler allocation (assigns 0)
*/


int main(void)
{

    int numCount = 0;
    puts("Input element count: ");
    scanf(" %d",&numCount);

    int *arr = (int *)calloc(numCount,sizeof(int));
    
    for (int *ptr = arr; ptr < arr+numCount; ptr++)
    {
        printf("%p\t%d\n",ptr,*ptr);
    }

    puts("Input new element count: ");
    scanf(" %d",&numCount);

    arr = realloc(arr,numCount*sizeof(int)); //after calloc part (numCount) if you deref it'll just dox garbage data.
                                                  //To prevent it assign shit like that.
    for (int *ptr = arr; ptr < arr+numCount; ptr++)
    {
        *ptr = 1;
    }

    for (int *ptr = arr; ptr < arr+numCount; ptr++)
    {
        printf("%p\t%d\n",ptr,*ptr); //starts from same addres and extends to the new count
    }


    free(arr); //Always free your shit 



    return(0);
}