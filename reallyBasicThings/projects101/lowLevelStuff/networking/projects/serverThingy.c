/*


    'Sup? I've returned with yet another network fuckery (local network till I learn how to make this shit world-wide)
    So I present you the idea of To-Do server so yeah I am making a Fucking CRUD app despite being a low-level gremlin
    What's next? Puttig a tie and attending to meetings?
    
    at least I am not using Flask duh...


    So to sum up today's fuckery: 
        0- Get a local HTTP server running
        1- Make an index.html to serve 
        2- Let yourself create a to-do not for yourself
        3- Generate a subpage of that to-do thingy
        4- Store the html on storage
        5- Let yourself edit that shit (or delete)
        6- And turn this program to a system daemon so you can use this shit 7/24


        Eaiser said than done right?

        How hard can it be...


*/


//Headers that I know why here (at least for my initila draft)
#include <asm-generic/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
//Headers that I have no fucking idea about
#include <sys/socket.h>
#include <arpa/inet.h>


#define PORT 8080

int main(void)
{

    int server_sock = 0, client_sock = 0;
    struct sockaddr_in server_addr = { 0 }, client_addr = { 0 }; 

    socklen_t client_len = sizeof(client_addr);
    
    /*
    DESCRIPTION
        sockaddr_in
                Describes an IPv4 Internet domain socket address.

                .sin_port and .sin_addr are stored in network byte order.
                thx man...(pun intended) that helped fucking too much

        and yeah this program will a lot of man page copy-pastes

    */



    int opt = 1;

    mkdir("todoThingies", 0755);    //I guess that was the 'Fuck it everybody can touch' mode in octal

    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    //AF_INET = Internet as fuck
    //SOCK_STREAM = TCP

    if (server_sock == -1)
    {
        perror("Socket sucked it");
        exit(EXIT_FAILURE); // Macro for 1 just a fancy way to say 1
    }

    setsockopt(server_sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);
    //he htons() function converts the unsigned short integer hostshort from host byte order to network byte order.
    //I have no fucking idea what that implies...I think I shouldn't attempt to do this now but I need the to-do app I forget shit
    

    




    return(0);
}
