#include <stdio.h>

int main(void)
{
    // freopen closes the old stdout and opens output.txt in its place
    // This is the "clean" way that fixes the errors in your screenshots
    if (freopen("output.txt", "w", stdout) == NULL) {
        perror("freopen failed");
        return 1;
    }

    // This will now successfully write to output.txt
    printf("Yet were I a flame I'd be still lighting your cigs on an abyss\n");
    
    // Stderr is never closed, so it still goes to your terminal
    fprintf(stderr, "Git Gut bro Segfault isn't C's fault\n");

    return 0;
}