#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#define VERSION "Ω"
#define BUFFER_SIZE 8192        //Yup 2 page worth of bytes lol

void printHelp(void);
void printKitty(void);

int main(int argc, char **argv)
{
    srand(time(NULL));
    setvbuf(stdout, NULL, _IONBF, 0);

    int numberNonEmptyLines = 0;
    int showEnds = 0;
    char *filePath = NULL;

    for (int i = 1; i < argc; i++) {

        if (strcmp(argv[i], "--help") == 0) {
            if (rand() % 10 == 3) { printKitty(); }
            else { printHelp(); }

            return(0);
        }

        if (strcmp(argv[i], "--version") == 0) {
            printf("Kitty Version: %s\n", VERSION);
            return(0);
        }

        if (strcmp(argv[i], "-E") == 0) {
            showEnds = 1;
            continue;
        }

        if (strcmp(argv[i], "-b") == 0) {
            numberNonEmptyLines = 1;
            continue;
        }

        if (filePath == NULL)
            filePath = argv[i];
    }

    if (filePath == NULL) {
        fprintf(stderr, "kitty: no input file\n");
        return(13);
    }

    FILE *fp = fopen(filePath, "rb");

    if (!fp) {
        perror(filePath);
        return(-13);
    }

    char buffer[BUFFER_SIZE] = { 0 };
    int bytesRead = 0;


    if (!numberNonEmptyLines && !showEnds) {

        while ((bytesRead = fread(buffer, 1, BUFFER_SIZE, fp)) > 0)
            fwrite(buffer, 1, bytesRead, stdout);

        fclose(fp);
        return(0);
    }


    int line = 1;
    int atLineStart = 1;

    while ((bytesRead = fread(buffer, 1, BUFFER_SIZE, fp)) > 0) {

        for (int i = 0; i < bytesRead; i++) {

            char c = buffer[i];

            if (atLineStart) {

                if (numberNonEmptyLines && c != '\n')
                    printf("%6d\t", line++);

                atLineStart = 0;
            }

            if (c == '\n') {

                if (showEnds)
                    putchar('$');

                putchar('\n');
                atLineStart = 1;
            }
            else {
                putchar(c);
            }
        }
    }

    if (ferror(fp)) {
        perror("fread");
        fclose(fp);
        return(-13);
    }

    fclose(fp); //Close the file bruh
    return (0);
}

void printHelp(void)
{
    puts("kitty - tiny cat clone");
    puts("");
    puts("Usage:");
    puts("    kitty [OPTION]... FILE");
    puts("");
    puts("Options:");
    puts("    -b          number non-blank output lines");
    puts("    -E          display $ at end of each line");
    puts("    --help      for I got you bruh' ");
    puts("    --version   display version bruh");
}

void printKitty(void)
{
    const char *kitty = 
"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⠇⠀⠀⠀⠀\n"
"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡐⠅⠀⠀⠀⠀\n"
"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡐⠀⠈⣆⡤⠀⠀\n"
"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⠋⠁⠉⡝⡄⠀⠀⠀\n"
"⠀⡖⡀⠀⠀⠀⠀⠀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠀⠀⠀⠀\n"
"⠀⠑⡇⠀⠀⠀⠀⠀⡏⢷⡀⠀⠀⠀⠀⠀⠀⡀⣀⢀⠀⠀⠀⠀⠀⠀⠀⢀⣠⣶⣟⠀⠀⠀⠀⠀⠀⠀\n"
"⢀⣘⡈⢒⠖⠂⠀⠀⡇⠀⠙⢗⢄⣤⣔⡏⠟⠯⠙⠙⠋⠛⠙⢷⣤⣀⡴⠕⠁⢸⡕⠀⠀⠀⠀⠀⠀⠀\n"
"⠋⠀⢱⠁⠀⠀⠀⠀⡇⠀⠀⠈⠻⡍⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⠛⠁⠀⠀⣸⠅⠀⠀⠀⠀⠀⠀⠀\n"
"⠀⠀⠀⠀⠀⠀⠀⣠⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⡷⡀⠀⠀⠀⠀⠀⠀\n"
"⠀⠀⠀⠀⠀⠀⢀⡏⠀⠀⠀⠀⢠⡆⠀⠀⠀⠀⠀⠀⠀⠀⠀⡴⣇⠀⠀⠀⠀⠊⢗⡇⠀⠀⠀⠀⠀⠀\n"
"⠀⠀⠀⠀⠀⠀⢸⠁⠀⠀⠀⠀⣾⠅⠀⠀⠀⠀⢠⠀⠀⠀⠀⣿⡇⠀⠀⠀⠀⠀⠸⡇⠀⠀⠀⠀⠀⠀\n"
"⠀⠀⠈⠐⠒⠒⠺⠗⠒⠀⠀⠀⠈⠁⠀⣀⠀⠀⣺⠀⠀⢀⠀⠻⠇⠀⠀⠀⠉⠁⢙⠏⠈⠈⠁⠉⠁⠀\n"
"⠀⠀⠀⠀⡄⠄⠼⡇⡊⠈⠀⠀⠀⠀⠀⢾⣄⣠⡟⣇⣀⡼⠀⠀⠀⠀⠀⠀⠂⠲⠗⡇⠐⠐⠄⡀⠀⠀\n"
"⠀⠀⠀⠠⡀⡀⠄⠵⡆⡂⠂⠀⠀⠀⠀⠀⠉⠉⠀⠉⠛⠁⠀⠀⠀⠀⠀⢀⡗⣛⠒⠅⣀⠀⠀⠀⠀⠀\n"
"⠀⠀⠀⠀⠀⠀⠀⠀⠉⠻⡶⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣷⣿⡁⠀⠀⠀⠉⠀⠀⠀⠀\n"
"⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⣟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⣃⠇⠡⠀⠀⠀⢀⠄⡒⠄\n"
"⠀⠀⠀⣨⠀⠀⠀⠀⠀⢸⡯⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠞⠅⠂⠀⣠⠒⠩⠙⡷\n"
"⠀⠀⠀⠷⡀⠀⠀⠀⠀⢐⣋⠀⠀⠀⢠⡇⠀⠀⠀⠀⡄⠀⠀⠀⢀⢀⠀⠀⠀⠀⡑⡁⠰⠁⠠⠁⡀⢏\n"
"⠀⢀⠞⡍⢹⡲⠒⠀⠀⠸⢍⠀⠀⠀⢸⠂⠀⠀⠀⠀⣇⠀⠀⠀⢟⡅⠀⠀⠀⠀⢘⣨⠁⠌⠀⣀⠘⠂\n"
"⠀⠀⠀⢱⠇⠃⠀⠀⠀⠐⡇⡄⠀⠀⢈⠆⠀⠀⠀⠀⢆⠀⠀⠀⢇⠆⠀⠀⠀⠀⣨⡏⠌⠀⡠⢀⠁⠀\n"
"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠐⡣⡆⠀⠀⢀⠆⠀⠀⠀⠀⡅⠀⠀⢀⡒⠄⠀⠀⠀⠀⡜⣯⠀⠄⠒⠂⠀⠀\n"
"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠐⠊⢘⠄⠀⢈⠄⠀⠀⠀⠀⡈⠀⠀⠠⠬⠀⠀⠀⠀⠀⡷⢥⢦⠟⠁⠀⠀⠀\n";

    printf("%s",kitty);

}
