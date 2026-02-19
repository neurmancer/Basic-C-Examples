#include <stdio.h>
#include <string.h>

int main(void)
{
    //A basic format showcase file

    for (int i = 0; i < strlen("Hello"); i++)
    {
        printf("%.*s\n",i+1,"Hello");
    }


    return(0);
}