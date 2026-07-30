/*
    Sup this is a little niche one since it'll mostly gonna be for myself 
    What are we going to do today?
    DWM statusbar spitting prime numbers for just fun...

    here is the flags you need to compile this one because I wanna go in all C without fucking with .xinitrc as less as possible

    gcc -O3 -o dwm-status mstatus.c -lX11
    -O3 for optimization -lX11 for linking X11server 

    I'll be using my naive approach to primes from isPrimeThingy.c no drive-by sieve this time 

    just compile and if you use dwm add the binary to your .xinitrc with 'path/to/binary/ &' ampersand for  background process Crucial detail btw 
*/


#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <X11/Xlib.h>

#ifndef UINT_MAX
    #define UINT_MAX (~0u)  //Sets all bits to 1
#endif

int isPrime(unsigned int val);

int main(void) {
    

    Display *dpy;
    Window root;
    char status[256];

    if (!(dpy = XOpenDisplay(NULL))) {
        fprintf(stderr, "ERROR: Could not open display!\n");
        return(-13);
    }
    
    root = DefaultRootWindow(dpy);
    unsigned int currentPrime = 2;
    unsigned int iter = 3;
    // 3. Start our infinite status loop!
    while (iter < UINT_MAX) {
        if (isPrime(iter)) {
            currentPrime = iter;
        }

        time_t t = time(NULL);
        struct tm *tm_info = localtime(&t);
        char time_str[64];
        strftime(time_str, sizeof(time_str), "%H:%M", tm_info);

        
        snprintf(status, sizeof(status), "Here is your prime bruh: %u | Time: %s ",currentPrime, time_str); 
        
        XStoreName(dpy, root, status);
        XSync(dpy, False); 
        iter++;

        sleep(1);
    }

    // Clean up (though we never really reach here lol)
    XCloseDisplay(dpy);
    return(0);
}


int isPrime(unsigned int val)
{
    if (val == 1 || val == 0) { return(0); }
    if (val == 2 || val == 3) { return(1); }

    if ((val % 3) == 0 || (val % 2) == 0) {
        return(0);
    }

    for (int i = 5;i <= (val/i) ; i+=2) 
    {
        if (val % i == 0) {
            return(0);
        }
    }
    return(1);
}