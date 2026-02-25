#include <stdio.h>


/*This will be a short lecture about  how pointers/variables get used by different type of functions
1-printMemory takes an integer
2-printMemory2 takes an integer pointer
both does same thing prints their memory address 

*/

void printMemory(int a);
void printMemory2(int *a);

int main(void)
{
    int original = 5;
    printf("Address of original: %p\n",&original);
    printMemory(original);
    printMemory2(&original);
    return(0);
}


void printMemory(int a)
{
    printf("Address of the copied one: %p\n", (void *) &a);
}    

void printMemory2(int *a)
{
    printf("Guess what that's gonna be: %p\n", (void *) a); //a is a pointer already so, no '&' sign
}