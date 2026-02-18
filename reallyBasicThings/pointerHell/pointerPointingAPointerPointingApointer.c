#include <stdio.h>

/*
    This file just for to show how pointers that pointing antoher pointer that points a value 
    Man...writing this overwhelming
*/

int main(void)
{

    int x = 5;          //Basically if you point an int you can point anything don't need to overcomplicate shit (for now)
    int *ptr = &x;      //Ptr gets address of x
    int **ptrPtr = &ptr; //ptrPtr gets address of ptr which holding address of x

    //so basically 
    printf("%p\n",&x);      //Address of x 
    printf("%p\n",ptr);     //Value of ptr which is address of x
    printf("%p\n",*ptrPtr);  //Derefed once ptrPtr, which is value of ptr -> which is address of x
    /*All those will show the same value...I mean C'mon it's not rocket science
    (btw the value they'll print change every run since assigned memory ain't constant but those 3 print the same shit every time)
    */

    printf("%d\n",x); //Value of x = 5
    *ptr = 10;        //Derefed the first pointer and assigned x = 10 via ptr
    printf("%d\n",x);
    **ptrPtr = 20;   
/*
    Now the bat shit crazy part ptrPtr -> holding ptr's address -> holding x's addres. So first * gives you the address ptr holds,
    and the second asterisk is basically *(ptr) because *ptrPtr -> ptr 
*/
    printf("%d\n",x);
    //and this is called mutate by reference or shit IDK this is my 11th of coding

    //Here is the second part 
    int a = 5;      //This is a in a memory address like 0x7fffc5872324(don't worry that's just an example)
    int b = a;      //And this copies the VALUE of a (5) to another memory address like 0x7fffc5872328 (4 byte next let's say for now)
    int *ptrA = &a;  //this hold the address of a
    *ptrA = 10;
    printf("A:%d - B:%d\n",a,b);        //A got mutated via pointer and b stayed as the old a value because it's in an independent memory address 

    return(0);
}