/*
    Contuning with HTTPClient


    //Usage 1: select a random public IP (google answers I tried)
    ping the ip using ping google.com 
    then use the public ip with ./bin xxx.xxx.xxx

    then it'll dump you random-ass HTML
*/


#include <inttypes.h>
#include <stdio.h>

#include <sys/socket.h>
#include <sys/types.h>

#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080

int main(int argc, char *argv[])
{

    setvbuf(stdout, NULL, _IONBF, 0);
    
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <ip>\n", argv[0]);
        return(-1);
    }
    
    char *address = argv[1];

    int cli_sock = socket(AF_INET, SOCK_STREAM, 0);

    if (cli_sock == -1) { return(-1); }
    
    struct sockaddr_in remote_addr = { 0 };

    remote_addr.sin_family = AF_INET;
    remote_addr.sin_port = htons(80);   //Most common HTTP port
    if (inet_aton(address, &remote_addr.sin_addr) == 0) {
        fprintf(stderr, "Invalid address: %s\n", address);
        close(cli_sock);
        return(-1);
    }

    if (connect(cli_sock, (struct sockaddr *)&remote_addr, sizeof(remote_addr)) == -1) {
        perror("connect");
        close(cli_sock);
        return(-1);
    }

    //BRUH I FUCKING SWEAR THE HARD PART ISN'T THE SOCKETS OR SHIT IT'S THE FUCKING HTTP PAPERWORK
    char req[512];
    snprintf(req, sizeof(req),
             "GET / HTTP/1.1\r\n"
             "Host: %s\r\n"
             "Connection: close\r\n"
             "\r\n",
             address);

    send(cli_sock, req, sizeof(req), 0);
    
    //Error handling left for the reader as an exercise (nah I am just too lazy to do it rn...)
    //But take my word for it not my actions
    
    char response[4096] = {0};
    ssize_t n = recv(cli_sock, response, sizeof(response) - 1, 0);
    if (n == -1) {
        perror("recv");
        close(cli_sock);
        return(-1);
    }

    response[n] = '\0';
    printf("Serv: %s\n", response);

    close(cli_sock);
    printf("Serv: %s\n",response);

    close(cli_sock);

    return(0);
}