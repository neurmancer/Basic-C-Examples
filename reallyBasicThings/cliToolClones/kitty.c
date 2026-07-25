#include <stdio.h>
#include <string.h>


    /*
        Sup? Continuing to reinvent the wheel yk... this one's a cat clone. I mean isn't it just fopen?
        and yeah these clones not about perfect replication but a little concept attempts I usally don't get into lots of flags only a few
    */

#define VERSION "Ω" //Yeah this time I'll use Ω

void printHelp(void);

int main(int argc, char** argv)
{
    
    setvbuf(stdout, NULL, _IONBF, 0);

    int fileName = 1;   //Same parsing logic with echo clone(resonate) since I didn't learn much after it
    int numberLines = 0;
    int showEnds = 0;

    for (int i = 1;i < argc;i++) {
        if (fileName && strcmp(argv[i], "--help") == 0) {
            printHelp();
            return(0);
        }
        if (fileName && strcmp(argv[i], "--version") == 0) {
            printf("Kitty Version: %s\n",VERSION);
            return(0);
        }

        if (fileName && strcmp(argv[i], "-E") == 0) {
            showEnds = 1;
            continue;
        }

        if (fileName && strcmp(argv[i], "-b") == 0) {
            numberLines = 1;
            continue;
        }

    }
    
    




    return(0);
}

void printHelp(void)
{
    printf("Boilerplate\n");
}