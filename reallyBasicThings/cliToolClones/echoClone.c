#include <stdio.h>
#include <string.h>

#define VERSION "Δ" //Well I'll put omega when I finish and Alpha is so 'A' looking-ass 
//(as if alpha isn't the etymologic origin of 'alphabet'...it comes from alpha et beta) so delta is cool           

/*
        Sup? What are doing today? Getting a bullet point done in futureShit.md (which is the most basic one because it's literally 4.44AM)
 
        Idea is building a echo clone and this hopefully teach me how to use CLI arguments with C so yeah no main(void) in this one

        sup...it's morning I took the wheels from here

*/

//This is where I believe in crt0.o supremacy since...yk I litearlly use CLI arguments for the first time


void printHelp(void);       
int stringLen(char *str);


int main(int argc, char *argv[])
{

    setvbuf(stdout, NULL, _IONBF,0); //The prayer (Honestly? I only know flags and io streams the NULL and 0 is me YOLOing (zero is probably buffer size but still vibez))

    int noNewline = 0;
    int firstText = 1;

    for (int i = 1; i < argc; i++) {
        if (firstText && strcmp(argv[i], "-n") == 0) {
            noNewline = 1;
            continue;
        }

        if (firstText && strcmp(argv[i], "--help") == 0) {
            printHelp();
            return 0;
        }

        if (firstText && strcmp(argv[i], "--version") == 0) {
            printf("echoClone %s\n", VERSION);
            return 0;
        }

        firstText = 0;

        if (i > 1 && strcmp(argv[i - 1], "-n") != 0)
            putchar(' ');

        fputs(argv[i], stdout); //Feeling ~~fancy~~ (nah just to not type \n and \0 to terminal for no reason)
    }

    if (!noNewline)
        putchar('\n');

    return(0);
}



void printHelp(void)
{
    const char *NAME = "";      //I am not even gonna try to finish this but let's try to format this 'man like'
    const char *SYNOPSIS = "";
    const char *DESCRIPTION = "";
    const char *AUTHOR = "Neuro";       //Since it's GPL-3 I can type my name for my own clone right? I'm sure no one gonna DMCA me for a echo clone...right?

}   



int stringLen(char *str)
{
    int count = 0;
    char *strC = str;
    while (*strC != '\0') {
        count++;
        strC++;
    }

    return(count);
}

/*
        Here is the fucking man page of echo for reference (I can steal with no problem since it's GPL-3 lol)

        ECHO(1)                                                                                  User Commands                                                                                 ECHO(1)

NAME
     echo - display a line of text

SYNOPSIS
     echo [SHORT-OPTION]... [STRING]...
     echo LONG-OPTION

DESCRIPTION
     Echo the STRING(s) to standard output.

     -n     do not output the trailing newline

     -e     enable interpretation of backslash escapes

     -E     disable interpretation of backslash escapes (default)

     --help
            display this help and exit

     --version
            output version information and exit

     If -e is in effect, the following sequences are recognized:

     \\     backslash

     \a     alert (BEL)

     \b     backspace

     \c     produce no further output

     \e     escape

     \f     form feed

     \n     new line

     \r     carriage return

     \t     horizontal tab

     \v     vertical tab

     \0NNN  byte with octal value NNN (1 to 3 digits)

     \xHH   byte with hexadecimal value HH (1 to 2 digits)

     Your shell may have its own version of echo, which usually supersedes the version described here.  Please refer to your shell's documentation for details about the options it supports.

*/