#include <netinet/in.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>

//These ones here because Beej said so (and probably to get getaddrinfo())
#include <netdb.h> 
#include <sys/types.h>

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


            3- Man I am fucking confues AF...Beej's guide shows sin_family assignemnts... my cc -E source shows sa_family and the man example down below shows sun_family for the structs...

                Guess(may be way off) sa is short for socket address sin is for socket_internet? and sun for socket unix family...fuck...
        
    */
    int fd = socket(AF_INET,SOCK_STREAM,0 ); //fd's short for file descriptor  0 and IPPROTO_TCP for tcp(7) stream sockets that explains why I have 0 as protocol it is TCP as I want
    if(fd == -1) {perror("Socket, sucked it"); return(-1); }
    
    /*
             .sin_family is always set to AF_INET.  This is required; in Linux 2.2 most networking functions return EINVAL when this setting is missing.  .sin_port contains the port in network  byte
        order.   The  port numbers below 1024 are called privileged ports (or sometimes: reserved ports).  Only a privileged process (on Linux: a process that has the CAP_NET_BIND_SERVICE capa‐
        bility in the user namespace governing its network namespace) may bind(2) to these sockets.  Note that the raw IPv4 protocol as such has no concept of a port, they are implemented  only
        by higher protocols like tcp(7) and udp(7).

        .sin_addr  is  the IP host address.  The .s_addr member of the in_addr(3type) structure contains the host interface address in network byte order.  in_addr(3type) should be assigned one
        of the INADDR_* values (e.g., INADDR_LOOPBACK) using htonl(3) or set using the inet_aton(3), inet_addr(3), inet_makeaddr(3) library functions or directly with  the  name  resolver  (see
        gethostbyname(3)).
    
        Am I using wrong family for binding&naming
    

    */




    struct addrinfo hint = { 0 }; //They use memset for somereason but I'll stick with this 'till I get seg-assult which honestly if they're only 0 initilizing I won't get since this is the same thing
    struct addrinfo *result; //I tried sockaddr but getaddrinfo bitched about not using 'addrinfo' ergo, I am using addrinfo blindly
    
    hint.ai_family = AF_INET; //IPv4 
    hint.ai_socktype = SOCK_STREAM; //TCP stream
    hint.ai_flags = AI_PASSIVE;     //Beej says this is for 'fill my IP for me' 

    // bind(fd, const struct sockaddr *addr, socklen_t len) no clue what it does for now lol... 
    int res = getaddrinfo(NULL,"8080", &hint,&result); //8080 for non-administrive port (is non-administrive a word? I dunno you got the idea...I don't need to be admin to access basically )

    int bindStatus = bind(fd, result->ai_addr,result->ai_addrlen); //   Upon successful completion, bind() shall return 0; otherwise, -1 shall be returned and errno set to indicate the error. (man bind page)
    if (bindStatus == -1) {perror("Avoidant attachment issue, see a therapist ASAP\n\n"); return(-1); }

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
