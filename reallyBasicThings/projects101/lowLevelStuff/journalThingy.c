/*
        'Sup? Today's episode of 'How to disappoint Ghost of Dennis Ritchie' we're fucking with JournalCTL...

        Well my original idea was using  <systemd/sd-journal.h> to do stupid shit that I haven't even decided yet but 
        I found an easier way which is making a deamon with a .service file and let the kernel carry the burden of my Shitty Deamon


        Shit I know: 
            I will be using signals (SIGINT and SIGTERM to be specific) then We'll figure it out

        On Stand-by: 'Cuz I haven't decided what to fuck with yet
*/



#include <stdio.h>
#include <unistd.h>
#include <signal.h>


volatile sig_atomic_t flag = 1;
// 'Signal-safe' type for these type of shit + volatile (so CPU can't gaslight us about cached value)


static void sigThingy(int sigNum);

int main(void)
{

    setvbuf(stdout, NULL, _IONBF, 0);

    struct sigaction sa = { 0 };    // Stolen from man 3 sigaction

    sa.sa_handler = sigThingy;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;   

    if (sigaction(SIGTERM, &sa, NULL) == -1 || sigaction(SIGINT, &sa, NULL) == -1 ) { return(-1); }

    //No buffer = Life good!
    printf("Daemon irrumpens");
    while (flag) {
        //Still...Do Shit...
    }

    printf("Daemon expulsus est.");

    //_longjmp(struct __jmp_buf_tag *, int) wtf this does? (yeah I am getting distracted by man sigaction.3 page) (Uuuu...this fucks the stack too bad if I fuck with it (not as much as gets() tho)

    return(0);
}



static void sigThingy(int sigNum)
{
    flag = 0;
    return;
}