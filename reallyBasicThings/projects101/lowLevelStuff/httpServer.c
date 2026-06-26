#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>

//These ones here because Beej said so (and probably to get getaddrinfo())
#include <netdb.h> 
#include <sys/types.h>

#define BACKLOG 10 //this is not an overkill right?

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


    struct addrinfo hint = { 0 }; //They use memset for somereason but I'll stick with this 'till I get seg-assult which honestly if they're only 0 initilizing I won't get since this is the same thing
    struct addrinfo *result; //I tried sockaddr but getaddrinfo bitched about not using 'addrinfo' ergo, I am using addrinfo blindly
    
    hint.ai_family = AF_INET; //IPv4 
    hint.ai_socktype = SOCK_STREAM; //TCP stream
    hint.ai_flags = AI_PASSIVE;     //Beej says this is for 'fill my IP for me' 

    // bind(fd, const struct sockaddr *addr, socklen_t len) no clue what it does for now lol... 
    int res = getaddrinfo(NULL,"8080", &hint,&result); //8080 for non-administrive port (is non-administrive a word? I dunno you got the idea...I don't need to be admin to access basically )

    int fd = socket(AF_INET,SOCK_STREAM,0 ); //fd's short for file descriptor  0 and IPPROTO_TCP for tcp(7) stream sockets that explains why I have 0 as protocol it is TCP as I want
    if(fd == -1) {perror("Socket, sucked it"); return(-1); }

    int bindStatus = bind(fd, result->ai_addr,result->ai_addrlen); //   Upon successful completion, bind() shall return 0; otherwise, -1 shall be returned and errno set to indicate the error. (man bind page)
    if (bindStatus == -1) {perror("Avoidant attachment issue, see a therapist ASAP\n"); return(-1); }

    //Now since I've arrived to...yk acutal networking part I gotta listen() and accept() right...do I need fork()s? or is listen() a non-blocking function 

    //Listening test 
    int listenStatus = listen(fd,BACKLOG); 
    /*
        The  accept() system call is used with connection-based socket types (SOCK_STREAM, SOCK_SEQPACKET).  It extracts the first connection request on the queue of pending connections for the
        listening socket, sockfd, creates a new connected socket, and returns a new file descriptor referring to that socket.  The newly created socket is not in the listening state.  
        The original socket sockfd is unaffected by this call... so this explanation says me that I'll get a seperate fd (which is listeningStatus ig) after having a file waiting approvel from accept()
        Does it fork the process or memcpy the old data? IDK...and I guess that's point of using a fucking API


    */
    if (listenStatus == -1) {perror("Port is like Beethoven after 1817 rn fr\n"); return(-1);}

    struct sockaddr_storage clientAddr = { 0 };
    socklen_t clientAddrSize = sizeof(clientAddr);

    int clientFD = accept(fd, (struct sockaddr *)&clientAddr,&clientAddrSize); //As I thought blocks the shit 
    if (clientFD == -1) { perror("Failed proposal attempt\n"); return(-1); } //Yeah I am running out of error jokes slowly
    /*
        This shit will be needed for myself to not soft-lock myself 

    If no pending connections are present on the queue, and the socket is not marked as nonblocking, accept() blocks the caller until a connection is present.  If the socket is marked  non‐
     blocking and no pending connections are present on the queue, accept() fails with the error EAGAIN or EWOULDBLOCK.

     In  order to be notified of incoming connections on a socket, you can use select(2), poll(2), or epoll(7).  A readable event will be delivered when a new connection is attempted and you
     may then call accept() to get a socket for that connection.  Alternatively, you can set the socket to deliver SIGIO when activity occurs on a socket; see socket(7) for details.

     If flags is 0, then accept4() is the same as accept().  The following values can be bitwise ORed in flags to obtain different behavior:

     SOCK_NONBLOCK   Set the O_NONBLOCK file status flag on the open file description (see open(2)) referred to by the new file descriptor.  Using this flag saves extra calls to fcntl(2)  to
    achieve the same result.


    
    
    */


    //since almost every server runs repeatetly 
    while (1) {
        printf("Working\n");
        sleep(1);
        //Do shit as recieved 

    }



    return(0);
}

