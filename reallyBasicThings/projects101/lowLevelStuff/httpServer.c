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
    if(fd == -1) {perror("Socket, sucked it"); return(-1); }
    
    struct sockaddr serverAdd = { 0 };
    
    serverAdd.sa_family = AF_INET;
    
    // bind(fd, const struct sockaddr *addr, socklen_t len) no clue what it does for now lol... 
    
    int bindStatus = bind(fd,(struct sockaddr *)&serverAdd,sizeof(serverAdd)); //   Upon successful completion, bind() shall return 0; otherwise, -1 shall be returned and errno set to indicate the error. (man bind page)
    if (bindStatus == -1) {perror("Binding to the socket has failed\n"); return(-1); }

    //since almost every server runs repeatetly 
    while (1) {
        printf("Working\n");
        sleep(1);
        //Do shit as recieved 

    }



    return(0);
}


/*

    Stole this from man 2 bind to learn how to fucking bind it's been fucking 20 minutes and I can't figure it out how to bind shit yet.


     #include <err.h>  unnecessary in my case for now
     #include <stdlib.h> 
     #include <string.h>
     #include <sys/socket.h>
     #include <sys/un.h>
     #include <unistd.h>

     #define MY_SOCK_PATH "/somepath"
     #define LISTEN_BACKLOG 50

     int
     main(void)
     {
         int                 sfd, cfd;
         socklen_t           peer_addr_size;
         struct sockaddr_un  my_addr, peer_addr;

         sfd = socket(AF_UNIX, SOCK_STREAM, 0);
         if (sfd == -1)
             err(EXIT_FAILURE, "socket");

         memset(&my_addr, 0, sizeof(my_addr));      I guess this is the 0 init 
         my_addr.sun_family = AF_UNIX;              I'll probably need to use AF_INET instead in my case
         strncpy(my_addr.sun_path, MY_SOCK_PATH,        Why do I need a path for my scocket ?
                 sizeof(my_addr.sun_path) - 1);         That's the data part ig

         if (bind(sfd, (struct sockaddr *) &my_addr,
                  sizeof(my_addr)) == -1)
             err(EXIT_FAILURE, "bind");

            ==== UNRELATED FOR NOW ======

         if (listen(sfd, LISTEN_BACKLOG) == -1)
             err(EXIT_FAILURE, "listen");

          Now we can accept incoming connections one
            at a time using accept(2).  

         peer_addr_size = sizeof(peer_addr);
         cfd = accept(sfd, (struct sockaddr *) &peer_addr,
                      &peer_addr_size);
         if (cfd == -1)
             err(EXIT_FAILURE, "accept");

         if (close(sfd) == -1)
             err(EXIT_FAILURE, "close");

         if (unlink(MY_SOCK_PATH) == -1)
             err(EXIT_FAILURE, "unlink");
     }

*/
