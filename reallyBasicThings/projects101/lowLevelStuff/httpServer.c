#include <asm-generic/errno.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>

/*
    And here we are...I am diving head-first into networking as I code a fucking HTTP server...no idea what a HTTP server is for now...but I'll eventually learn on the way lol
    Yk...it's the whole fucking point of trying to code a HTTP server. where this idea came from you might ask...I was wandering on wikipedia and stumbled across HTTP page at 4AM then I saved the link
    (here it is btw)  https://en.wikipedia.org/wiki/HTTP for the nerds...and decided to build one myself to see if I get what it does and doesn't
    
    I'll be satisfied when this program will be able to hand an html file to a client from a port on a localhost probably...

        First, resources I use:
            - https://github.com/codecrafters-io/build-your-own-x/blob/master/README.md#build-your-own-network-stack the Beej's guide to networking that I saw from 'Build-your-X' repo (which is a beast on it's own)
                -And I'll be looking to this guide to find out what functions do what, (if you wanna learn from scratch it is a perfect guide but I am starting from the Chapter 5)
                (theory part has not been my strong suit anyways)

        Btw since I am on the topic I am using man pages as primary source to get intel on the libs I am using and if you don't know how, here is how to use man: man <lib_name> works most of the time if you have 
        man-pages on your system (pacman -S man-pages for Arch but dunno for others)

*/


int main(void)
{
    /*
        Important shit to know:
            
            1- AF_INET is IPv4 domain define in the socket.h (at least man says lol...I'm still Terry Davis'ing my way to knowledge)
            2- SOCK_STREAM is the one we use for TCP protocal 
        
    */
    int fd = socket(AF_INET,SOCK_STREAM,0 ); //fd's short for file descriptor 

    // bind(fd, const struct sockaddr *addr, socklen_t len) no clue what it does for now lol... 
    
    if(fd == -1) {perror("Socket, sucked it"); return(-1); }

    //since almost every server runs repeatetly 
    while (1) {
        printf("Working\n");
        sleep(1);
        //Do shit as recieved 

    }



    return(0);
}