#include <stdio.h>

#define VERSION "Δ" //Well I'll put omega when I finish and Alpha is so 'A' looking-ass 
//(as if alpha isn't the etymologic origin of 'alphabet'...it comes from alpha et beta) so delta is cool           

/*
        Sup? What are doing today? Getting a bullet point done in futureShit.md (which is the most basic one because it's literally 4.44AM)
 
        Idea is building a echo clone and this hopefully teach me how to use CLI arguments with C so yeah no main(void) in this one

*/

//This is where I believe in crt0.o supremacy since...yk I litearlly use CLI arguments for the first time


void printHelp(void);       //As a template for morning yeah...I am this tired to parse arguments now

int main(int argc,char *argv[]) //Argv is what are the args and argc is how many arguments are there starting from 1 (the program itself)
{
    setvbuf(stdout, NULL, _IONBF, 0); //so we don't buffer in case of getting flags like -n 
    if (argc == 1) {
        printf("\n"); //Standard echo behaviour giving an empty line
    }
    
    else{
        
        for (int i = 1;i < argc ;i++) {
            printf("%s\n",argv[i]);
        }
        printf("\n");
    }


    return(0);
}



void printHelp(void)
{
    const char *NAME = "";      //I am not even gonna try to finish this but let's try to format this 'man like'
    const char *SYNOPSIS = "";
    const char *DESCRIPTION = "";
    const char *AUTHOR = "Neuro";       //Since it's GPL-3 I can type my name for my own clone right? I'm sure no one gonna DMCA me for a echo clone...right?

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