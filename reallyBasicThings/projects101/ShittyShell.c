/*Sup? gotta build a shell as I promised so here we are... I am (kinda) following a tutorial but we'll divert ofc yk...me being me*/


/* WTF a shell does? 
    First - Init the shell...a normal shell would read and executes it's configs and those are what changes its behaviours
    Second - Interpret well...it's a shell you gotta read shit (probably stdin) ten terminate 

    That's what a shell does esentially
*/


#include <stdio.h>
#include <stdlib.h>

#define BUFF_SIZE 1024


void shelltyLoop(void);

char *shelltyReadLine(void);

int main(int argc,char **argv)
{


    shelltyLoop(); //That's what's gonna get executed as we run the terminal (and yeah 'Shellty is a conjured word made with Shitty + Shell = Shellty)



    return(0); //or just use EXIT_SUCCESS if you feel fancy lmfao 
}





void shelltyLoop(void)
{
    char *line;
    char **args;

    int stat; 

    do {
        printf("OwO > ");
        line = shelltyReadLine();
        args = shelltyParseLine(line);
        stat = shelltyExec(args);

        free(line);
        free(args); //Always free your shit (since...yk I haven't done a garbage collector yet)

    
    }while (stat);

}


char *shelltyReadLine(void)
{
    int bufsize = BUFF_SIZE;
    int pos = 0;

    char *buffer = (char *) malloc(sizeof(char)* bufsize);
    int c = 0; // btw why int for a char? cuz first ASCII is just gaslighted integers and second EOF is -1 so if you wanna or need it you have to use int not cha

    if (buffer == NULL) {
        fprintf(stderr,"Shitty Shell just got shittier UnU...\n");
        exit(EXIT_FAILURE); //Yup I do feel fancy this time
    }

    while (1) {
        //Read char (I mean you have to know if you are looking a fucking shell script...)
        c = getchar();

        //IF we hit jackpot (EOF duh...) replace it with '\0' and return
        if (c == EOF || c == '\n') {
            buffer[pos] = '\0';
            return(buffer);
        }

        buffer[pos] = c;
        pos++;

        if (pos >= bufsize) {
            bufsize += BUFF_SIZE; //Reallocate so we won't overflow
            buffer = realloc(buffer,bufsize);

            if (buffer == NULL) {
                fprintf(stderr, "your OS says NO! UwU ");
                exit(1);
            }
        
        }

    }
    


}