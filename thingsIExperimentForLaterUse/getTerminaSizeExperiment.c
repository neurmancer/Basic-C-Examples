#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>


int main (void)
{
    struct winsize window; //A winsize window obj
 
    for (int i = 0; i < 100; i++)
    {
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &window);  //In loop it gets dynamically FUCK YES I SOLVED SHIT AND YES I AM OVER HYPED ABOUT 10 LINES OF CODE GO CRY 'BOUT IT.
        printf ("lines %d\n", window.ws_row);
        printf ("columns %d\n", window.ws_col);
        sleep(1);
    }
    
    return(0);
}