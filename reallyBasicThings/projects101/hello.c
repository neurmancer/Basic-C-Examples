#include <stdio.h>
#include <string.h>

int main(void)
{
    //A basic format showcase file 
    /*If an asshole interviewer asks you to loop a word to print something like this as a casual intro question you can do that
    Lol...
    */

    for (int i = 0; i < strlen("Hello"); i++)
    {
        printf("%.*s\n",i+1,"Hello");
    }


    return(0);
}