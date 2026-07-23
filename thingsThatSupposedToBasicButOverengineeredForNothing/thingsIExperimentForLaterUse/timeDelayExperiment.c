#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>


int main(void)
{

    time_t currentTime = time(NULL) ;
    struct tm *t = localtime(&currentTime);
    
    for (int i = 0; i < 10; i++)
    {
        currentTime = time(NULL) ;
        t = localtime(&currentTime);
        printf("%d\n",t->tm_sec);
        sleep(1);
    }
    


    return(0);
}