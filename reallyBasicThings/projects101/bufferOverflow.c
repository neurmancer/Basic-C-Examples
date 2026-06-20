#include <stdio.h>
#include <string.h>

/*
        Welcome to another file where I fuck with the computer's interals and today we're going overflow the buffer so you can protect this in your production ready code
        Yeah this approach is like giving birth to emphisine importance of condom lol
        
        Shit to know:
            1- This file requries additional flags : -fno-stack-protector -z execstack -no-pie -O0 what those do? 
                1- -fno-stack-protector: Modern compilers anticipate user fuckery and put canaries to the stack and this flags flips the bird lol
                2- -z execstack is basically makes the stack executable (Nx bit is turned on) and that disables it and makes you enable to write to stack
                3- -no-pie This is a saint flag against Gluttony...nah I am just fucking with you it disables the ASLR
                4- -O0 means 'I know what I've typed compiler shut up and execute don't try to outsmart me'
                5-For those reasons you gotta compile it with those flags for this to work
            
            2-What we're doing here? 
                1-Overflowing the buffer duh?...nah basically showing you the sins unsecured input may cause
                2- Idea simple write shit till the input varabiles buffer gets full then write something to the next variable to switch it too

            3- And yeah if you type something slightly longer this file will segfault which is the whole fucking point duh... protect your inputs

            Password is my github nick's short version : Neuro

*/


int main(void)
{
    char buffer[4] = {0}; // A small buffer that will overflow
    int overflow = 0;

    printf("Password: ");
    fflush(stdout); //Don't forget to flush
    scanf("%s", buffer);  //A desparete, unwrapped,deplorable scanf that will read anything from stdin without limitation and checks     

    if (strcmp(buffer,"Neur") && overflow == 111) {
        //first half of the if statement is checking the buffer's inside whether the first 4 letter of the password is correct or not then the second half is the other variable which is 0 right?
        //Nah when you type Neuro and hit enter the last 'o' will overflow to the variable and change the value to 111 or 'o' on ASCII table
        printf("Welcome to the world of buffer fuckery!\n");
    } 

    else {
        printf("Still ain't cool enough\n");
    }

    return(0);
}