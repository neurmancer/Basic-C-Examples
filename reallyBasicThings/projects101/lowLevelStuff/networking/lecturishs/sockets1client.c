/*

    'Sup? I need to study a little sockets before advancing with todo server things so here will be small programs 
    (or tests) before I move onto To-Do app repo to implement 


    And I am turning my learning into a fucking public service...You're fucking welcome 

    Sources: https://youtu.be/SrGyi0WOTBk?list=PLysdvSvCcUhbOBztd-CdB5fCXFrvwk107,
    https://beej.us/guide/bgnet/html/split/system-calls-or-bust.html#socket,
    man pages of functions used in here 
    and whatever I need 

*/

#include <inttypes.h>
#include <stdio.h>

#include <sys/socket.h>
#include <sys/types.h>

#include <netinet/in.h>
#include <unistd.h>

#define PORT 5313   
//Well for the first try I gave different ports for client and server and it messed everything up as expected

//this is client-sided btw
int main(void)
{

    int sd = 0; //sd for socket descripotor (like fd)

    sd = socket(AF_INET, SOCK_STREAM, 0);
    if (sd == -1) { close(sd); return(-1); }
    printf("Works till here\n");
    struct sockaddr_in server = { 0 };
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);  //Again network byte order is big-endian instead of little endian 
    server.sin_addr.s_addr = INADDR_ANY;
    
    if(connect(sd, (struct sockaddr *)&server, sizeof(server)) == -1) { return(-1); }
    printf("Works till here too\n");
    char buf[256] = { 0 };
    printf("Works till here\n");
    if(recv(sd, buf, sizeof(buf)-1, 0) == -1) { return(-1); }

    printf("Data: %s\n",buf);

    int x = close(sd);
    if (x == -1) {
        perror("Fuck...");
        return(-1);
    }

    return(0);
}