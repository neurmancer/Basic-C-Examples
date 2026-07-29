/*
        Sup? Today's CLI Fuckery is man clone...since I've been using it since I've started coding and now I wanna 
        pay my respects to it

        Thought about calling it 'boy' since yk...man is a grown-ass one and mine is just a clone but calling it 
        my man would be funnier like 'tell me what setvbuf does my man' like a stoner

        and I won't add flags for man pages this time I'll just display the man pages in man-db or something 


        and for reference this is how I replicate man x on bash zcat signal.2.gz | groff -Tutf8 -mandoc | less -R
*/


#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>     //For fork() dup2() etc...


int main(int argc, char **argv)
{

    const char* testPath = "/usr/share/man/man2/signal.2.gz";
    
    int zcat_groff[2];
    int groff_less[2];

    if(pipe(zcat_groff) == -1 || pipe(groff_less) == -1){ return(-13); }


    int pid = fork();
    if (pid == -1) { return(-13); }

    if (pid == 0) {
        if(dup2(zcat_groff[1],STDOUT_FILENO) == -1){ return(-13); } //To redirect the output to pipe instead of terminal
        close(zcat_groff[0]);
        close(zcat_groff[1]);
        
        if(execlp("zcat", "zcat",testPath,NULL) == -1) { return(-13); }
        
    }

    int pid2 = fork();
    if (pid2 == -1) { 
        kill(pid, SIGKILL);
        waitpid(pid,NULL , 0);
        return(-13);
    }
    
    if (pid2 == 0) {
        if(dup2(zcat_groff[0],STDIN_FILENO) == -1){ return(-13); }
        if(dup2(groff_less[1],STDOUT_FILENO) == -1){ return(-13); }
        
        close(zcat_groff[1]);
        close(zcat_groff[0]);
        

        close(groff_less[1]);
        close(groff_less[0]);

        if(execlp("groff", "groff" , "-Tutf8", "-mandoc",NULL) == -1){ return(-13); }
    }

    int pid3 = fork();
    if (pid3 == -1) {
        kill(pid, SIGTERM);
        kill(pid2, SIGTERM);
        waitpid(pid, NULL, 0);
        waitpid(pid2, NULL, 0);
        return(-13);
    }

    if (pid3 == 0) {
        if(dup2(groff_less[0],STDIN_FILENO) == -1){ return(-13); }
        

        close(zcat_groff[1]);
        close(zcat_groff[0]);

        close(groff_less[1]);
        close(groff_less[0]);

        execlp("less","less","-R",NULL);
    }


    close(zcat_groff[1]);
    close(zcat_groff[0]);

    close(groff_less[1]);
    close(groff_less[0]);

    waitpid(pid, NULL, 0);
    waitpid(pid2, NULL, 0);
    waitpid(pid3, NULL, 0);


    return(0);
}

