/*
        'Sup? Today's episode of 'How to disappoint Ghost of Dennis Ritchie' we're fucking with JournalCTL...
        Reason is simple...My dwm was able to spit primes but my hyprland setup doesn't play nice with X11. 
        But it has a fancy screen to show journalctl -n 200 -auto-refresh thingies...so let's put primes in there

        Well my original idea was using  <systemd/sd-journal.h> to do stupid shit that I haven't even decided yet but 
        I found an easier way which is making a deamon with a .service file and let the kernel carry the burden of my Shitty Deamon


        Shit I know: 
            I will be using signals (SIGINT and SIGTERM to be specific) then We'll figure it out

        On Stand-by: 'Cuz I haven't decided what to fuck with yet

        Fuck it let's put prime numbers lol

        Now...I gotta put this to somewhere in /usr/local/bin or something and make a .service file...man...THAT'S LITERALLY PAPERWORK
        anyways let me learn what to do in /etc/systemd/prime_deamon.service



        here is the .service file will get into /etc/sytemd/yourShit.service



    [Unit]
    Description=Prime Number Daemon (because why not)
    After=network.target

    [Service]
    Type=simple
    ExecStart=/usr/local/bin/prime_daemon
    Restart=on-failure
    RestartSec=5
    StandardOutput=journal
    StandardError=journal

    [Install]
    WantedBy=multi-user.target

    and then let the systemd handle the rest

    btw I am confident to put those in my own filesystem because...well I created the fucking thing but from another person's POV: DO NOT FUCKING COPY-PASTE THOSE
    SUDO SHIT WITHOUT INSPECTING THE CODE YOURSELF

    ```bash
    sudo systemctl daemon-reload
    sudo systemctl enable prime_daemon
    sudo systemctl start prime_daemon
    journalctl -u prime_daemon -f
    ``` (yeah I am using markdown formatting in a C comment I lost my mind)
*/


#include <stdio.h>
#include <unistd.h>
#include <signal.h>

#define SECOND 1000000

#ifndef UINT_MAX
    #define UINT_MAX (~0u)
#endif

volatile sig_atomic_t flag = 1;
// 'Signal-safe' type for these type of shit + volatile (so CPU can't gaslight us about cached value)


static void sigThingy(int sigNum);

int isPrime(unsigned int x);

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
    unsigned int allegedlyPrime = 0;
    while (flag && allegedlyPrime < UINT_MAX ) {
        if (isPrime(allegedlyPrime)) {
            printf("Here is your prime bruh: %u\n",allegedlyPrime);
        }
        allegedlyPrime++;
        usleep(SECOND*0.5);
    }

    printf("Daemon expulsus est.");

    //_longjmp(struct __jmp_buf_tag *, int) wtf this does? (yeah I am getting distracted by man sigaction.3 page) (Uuuu...this fucks the stack too bad if I fuck with it (not as much as gets() tho)

    return(0);
}


int isPrime(unsigned int x)
{
    if (x == 1){return(0);}

    if (x == 2 || x == 3) {return(1);}

    if (x % 6 == 1 || x % 6 == 5) {

        for (int i = 5; i <= x/i; i += 2) 
        {   
            if (x % i == 0) {
                return(0);
            }
        }
        return(1);
    }
    return(0);
}


static void sigThingy(int sigNum)
{
    flag = 0;
    return;
}