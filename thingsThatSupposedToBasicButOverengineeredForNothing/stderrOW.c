#include <stdio.h>

int main(void)
{

    if (freopen("output.txt", "w", stdout) == NULL) {
        perror("freopen failed");
        return 1;
    }


    printf("Yet were I a flame I'd be still lighting your cigs on an abyss\n");
    
    // Stderr is never closed, so it still goes to your terminal Educational purpose only  
    //Please do not debug like that.
    fprintf(stderr, "Git Gut bro Segfault isn't C's fault\n");

    return 0;
}