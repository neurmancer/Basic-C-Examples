#include <stdio.h>
/*
    This file is a basic pointer introduction
*/


int main(void)
{

    int a = 5;                  //This is an int variable 
    int *p= &a;                 //And this is a int * (pointer) the asterisk(*) both will be used in decleration for pointers of any data type. char,int,long,float and shit you can create with structs too. 
    /*
        The & before a variable means get the memory address this variable address existed in RAM and pointers hold that data 
    */
    printf("%p\n",&a); //Memory address of 'a'
    printf("%p\n",p);  //value of pointer which is also memory address of a. (Note:if you use &p it shows memmory address OF THE POINTER itself)
    //Notice how every execution the printed address will differ but wil be same for both &a and p
    printf("%ld\n",sizeof(p));              //Pointers are always 8 bytes independent of the data type came before them

    printf("%d\n",a);
    printf("%d\n",*p);                   //After declaration of pointer asterisk(*) is used to dereference the pointer which means show the VALUE in that memmory addres so it simply means *p = a = 5 in our case

    //Pointers can change the value of the a without using a because they hold the same memmory addres
    *p = 20; //Notice that I derefed pointer and changed the value at the memory address
    printf("%d\n",a); //Notice how a will be 20 without using a to change it 


    //Yeah I know that's not my usual fuck around and find out style of commenting but that's meant to help people if encountered 
    //But if you still wanna get bat shit crazy ideas try declaring a pointer without assigning to a value and deref it to see what value it holds (Welcome to UB city)

    return(0); //Yup still using () like the boomer I am by heart.
}