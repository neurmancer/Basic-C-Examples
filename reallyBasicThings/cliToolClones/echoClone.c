#include <stdio.h>
#include <string.h>

#define VERSION "Δ" //Well I'll put omega when I finish and Alpha is so 'A' looking-ass 
//(as if alpha isn't the etymologic origin of 'alphabet'...it comes from alpha et beta) so delta is cool           

/*
        Sup? What are doing today? Getting a bullet point done in futureShit.md (which is the most basic one because it's literally 4.44AM)
 
        Idea is building a echo clone and this hopefully teach me how to use CLI arguments with C so yeah no main(void) in this one

        sup...it's morning I took the wheels from here and I am renaming it 'Resonate' 
        
        Imma call this close enough for a echo clone...(yeah I don't really know how to parse strings and shit and coping with this)

        man...parsing argv is something too new 
*/

//This is where I believe in crt0.o supremacy since...yk I litearlly use CLI arguments for the first time


void printHelp(void);       


int main(int argc, char *argv[]) //Argv is what are the args and argc is how many arguments are there starting from 1 (the program itself)
{
    setvbuf(stdout, NULL, _IONBF, 0);   //so we don't buffer in case of getting flags like -n 

    int noNewline = 0;
    int firstText = 1;

    for (int i = 1; i < argc; i++) {
        if (firstText && strcmp(argv[i], "-n") == 0) {
            noNewline = 1;
            continue;
        }

        if (firstText && strcmp(argv[i], "--help") == 0) {
            printHelp();
            return(0);
            //Yeah strcmp returns 0 if equal 
        }

        if (firstText && strcmp(argv[i], "--version") == 0) {
            printf("Resonate Version: %s\n", VERSION);
            return(0);
        }

        firstText = 0; //The actual text starts here 

        if (i > 1 && strcmp(argv[i - 1], "-n") != 0)
            putchar(' ');

        fputs(argv[i], stdout);
    }

    if (!noNewline)
        putchar('\n');

    return(0);
}

void printHelp(void)
{

    //And I realized something sa I read the echo's man page to see those...
    // I should make a man clone too I mean it uses less to print shit and checks /etc/manpath.conf(or something 
    // I don't remember it's too late or too early) then format with troff (which I never used) then voila...I can build that
    const char *NAME = "Resonate - display a line of text";
    const char *SYNOPSIS = "Resonate [SHORT-OPTION]... [STRING]...\n";

    const char *DESCRIPTION = 
        "Resonate the STRING(s) to standard output.\n\n"
        "  -n     do not output the trailing newline\n"
        "If you want the rest of the list such as: "
        "  -e     enable interpretation of backslash escapes\n"
        "  -E     disable interpretation of backslash escapes (default)\n"
        "  --help     display this help and exit\n"
        "  --version  output version information and exit\n\n"
        "If -e is in effect, the following sequences are recognized:\n\n"
        "  \\\\     backslash\n"
        "  \\a     alert (BEL)\n"
        "  \\b     backspace\n"
        "  \\c     produce no further output\n"
        "  \\e     escape\n"
        "  \\f     form feed\n"
        "  \\n     new line\n"
        "  \\r     carriage return\n"
        "  \\t     horizontal tab\n"
        "  \\v     vertical tab\n"
        "  \\0NNN  byte with octal value NNN (1 to 3 digits)\n"
        "  \\xHH   byte with hexadecimal value HH (1 to 2 digits)\n\n"
        "Go fucking use echo...";

    const char *AUTHOR = "Neuro";  //Since it's GPL-3 I can type my name for my own clone right? I'm sure no one gonna DMCA me for a echo clone...right?
 
    printf("RESONATE(1)                  User Commands                  RESONATE(1)\n\n");
    printf("NAME\n");
    printf("     %s\n\n", NAME);
    
    printf("SYNOPSIS\n");
    printf("     %s\n\n", SYNOPSIS);
    
    printf("DESCRIPTION\n");
    printf("     %s\n\n", DESCRIPTION);
    
    printf("AUTHOR\n");
    printf("     %s\n\n", AUTHOR);
    
    printf("GPL-3.0 License.\n");
}

