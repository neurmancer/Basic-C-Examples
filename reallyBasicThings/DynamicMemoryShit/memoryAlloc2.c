#include <stdio.h> //Standard IO
#include <stdlib.h> //Where the malloc and free exists

/*
In this file I'll show how to dynamically allocate an array 
*/


int main(void)
{
 
    int *ptr = NULL;        //assing to something but not just declare even a segfault is better than UB 
    // printf("%d\n",*ptr); and for fuck sake don't deref a null pointer
    int userInput = 0; //assing shit even tho will get overwritten by scanf right after
    printf("How many number you'll enter: ");
    fflush(stdout);  //FFlush before scanf
    if(scanf(" %d",&userInput) != 1)
    {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {c++;/*Nothing to see here just clearing input buffer*/ }
        printf("Try again next time with actual nums yk\n.");
        return(-13);
    }
    int byteSize = sizeof(int)*userInput; //too reduce confusion in malloc parameters
    ptr = (int *) malloc(byteSize); //int * for changing the malloc's (void *) return value to int *
    int *ptr2 = ptr;            //since I'll use the ptr to assign values with array decay it'll be useless without backup 
    while (userInput > 0)
    {
        printf("input: ");
        fflush(stdout);     //buffer sux so we flush
        if(scanf(" %d",ptr) != 1) //The address that the pointer holding 
        {
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {c++;/*Really...nothing to see here just clearing input buffer UnU*/ }
            printf("Try again next time with actual nums idiot\n.");
            return(-53);        //Yeah I love primes ends with 3 so what?
        }        
        ptr++; //Shifting pointer to next index
        userInput--;
    }

    for (int *p = ptr2; p < ptr2+byteSize/sizeof(int);p++)
    {
        printf("%d \n",*p);
    }

    free(ptr2); //since the ptr which we allocated decayed long ago in first loop we free the allocated address by using ptr2 still pointing the entry point


    return(0);      //I ain't giving up my booomer parens;
}