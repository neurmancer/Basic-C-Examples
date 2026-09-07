/*
        Continuity of sockets1client.c
        Server side 

*/


#include <stdio.h>


#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

#include <netinet/in.h>
#include <unistd.h>


#define PORT 5313
int main(void)
{
    //And yeah we have less commentary here I am lowkey exhausted...

    char *str = "'Sup?";

    int sd = socket(AF_INET, SOCK_STREAM, 0);
    if (sd == -1){ return(-1); }

    struct sockaddr_in server = { 0 };
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = INADDR_ANY;
    
    int x = bind(sd, (struct sockaddr *)&server, sizeof(server));
    //Btw don't handle errors like that for fuck sake use err (if you prefer BSD) or perror(if you prefer UNIX) try assert() etc...
    //I am keeping it simple to focus on the networking part
    if (x == -1) { return(-1); }

    if( listen(sd, 10) == -1) { return(-1); }

    int cli_sock = 0;
    cli_sock = accept(sd, NULL, NULL);  //Keeping it simple for client address


    send(cli_sock, str, strlen(str), 0);
    printf("Sent a msg to cli\n");
    if(close(sd) == -1) { perror("Close fucked..."); return(-1); }

    return(0);
}