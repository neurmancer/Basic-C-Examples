#include <stdio.h>
#include <string.h>

int main(void)
{
    //A basic format showcase file 
    /*If an interviewer asks you to loop a word to print something like this as a casual intro question you can do that
    Lol...
    */

    for (int i = 0; i < strlen("Hello"); i++) //I know using strlen on a const is stupid but I am not promising you that I am the best coder on Earth lol
    {
        printf("%.*s\n",i+1,"Hello");
    }


    return(0);
}