#include <stdio.h>
#include <stdlib.h>
#include <time.h>       //I know I am using rand() too much but it's making boring shit slightly better

int main(void)
{
        //This will be just and introduction with only an integer array
    srand(time(NULL));  //Our prayer to RNGsus 

    int array[5] = { }; //assignes all tha values in array to 0, you can use {0} or in modern systems gcc auto-does it but never trust a computer   -Sun Tzu (or Linus Torvalds IDK)

    //int *ptr = array or int *ptr = array[0] they're same address and pointers all about memory not fucking cyber-sorcery
    for (int *ptr = array ; ptr < array+(sizeof(array)/sizeof(array[0]));ptr++) //with pointer aritmathics(or how tf u spell it) ptr++ goes n bytes where the n is the sizeof(data type) 1 for char,4 for int etc. 
    { 
        //We'll assing random values to elements using the pointer
        *ptr = rand() % 101; //asterisk(*) means deref pointer and then assign a value between 0-100
    }
    
    for (int *ptr = array ; ptr < array+(sizeof(array)/sizeof(array[0]));ptr++)
    {
        printf("%p\t%2d\n",ptr,*ptr); //to show the value and memory address notice how each element is seperated by 4 bytes 
    }

    char *s = "Am I gay tho";           //Two notes here. First: Do not fucking try to mutate char constants they're .rodata (read-only) and it'll segfault your ass use char s[] = "" if you'll mutate
                                        //Second: Notice how memory address move byte by byte instead of 4bytes at a time with char
    while (*s != '\0') //'\0' is an escape char C puts automatically end of a string to indicate it ended printf(%s) reads 'till '\0' if you don't have welcome to UB-land
    {
        printf("%c",*s);     //Basically prints the pointer value and goes to next char and it'll be buffered till '\n' if you don't want use fflush(stdout)
        s++;
    }
    printf("\n");
    //last note if you try to use same char pointer after moving pointer's position like s++; it'll dox garbage data...can summon cthulhu or dox your mom's number
    //To move past '\0'

    return(0);
}