#include <stdio.h>
#include <stdlib.h>




int main(void)
{


    int *ptr = NULL;
    ptr = (int *) malloc(sizeof(int));
    printf("%p\n",(void *) ptr); //printing address of pointer
    *ptr = 15; //Gave 15 value to allocated memory 
    printf("%p\t%d\n",(void *)ptr,*ptr);
    free(ptr); //always free the memory (and for fuck sake don't use the pointer after freeing it if you don't want segfault/UB)

    return(0);
}