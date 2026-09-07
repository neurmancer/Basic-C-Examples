/*

    'Sup? still learning how to network?
    Again all the programs in here up until this point (sockets1 and this file) getting created back to back
    So there is contuinity or how tf u spell it

*/
/*
    Supposed to run at the same time with server&client (HTTP ones)

*/



#include <stdio.h>
#include <string.h>


#include <sys/socket.h>
#include <sys/types.h>

#include <netinet/in.h>
#include <unistd.h>

#define PORT 8080
int main(void)
{

    FILE *html = NULL;
    html = fopen("index.html", "r");
    if (!html) { return(-1); }
    char response[8192] = { 0 }; 
    
    char body[4096] = {0};
    size_t body_len = fread(body, 1, sizeof(body)-1, html);
    fclose(html);

    int response_len = snprintf(response, sizeof(response),
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html\r\n"
        "Content-Length: %zu\r\n"
        "Connection: close\r\n"
        "\r\n"
        "%s",
        body_len, body);
    

    int server = socket(AF_INET, SOCK_STREAM, 0);
    
    int opt = 1;
    setsockopt(server, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    
    struct sockaddr_in server_addr = { 0 };
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    int x = bind(server, (struct sockaddr *)&server_addr, sizeof(server_addr));

    if (x == -1) { return(-1); }

    listen(server, 5);

    while (1) {
        printf("listening rn\n");
        int cli_sock = accept(server, NULL, NULL);
        send(cli_sock, response, response_len, 0);
        close(cli_sock);
    }

    return(0);
}
