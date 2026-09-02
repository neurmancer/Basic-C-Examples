/*


    'Sup? I've returned with yet another network fuckery 
    (local network till I learn how to make this shit world-wide but on the bright side: You can't get hacked if you are not on the internet)
    So I present you the idea of To-Do server so yeah I am making a Fucking CRUD app despite being a low-level gremlin
    What's next? Puttig a tie and attending to meetings?
    
    at least I am not using fucking Flask duh...


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


        I need this server since my ideas keep getting bigger and bigger and I need a fucking tracker of those
        What's next coding my own issue-tracker? (tho that would work...AND THIS IS THE REASON THAT I NEED A TO-DO APP)

        and I'll be using snake_case to feel like a real C programmer this time

        Started working on this at: 3 September 2026 00.42AM - Planned Due Date:Hopefully before 2027  
*/


//Headers that I know why here (at least for my initila draft)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <sys/errno.h>
#include <err.h>
//Headers that I have no fucking idea about
#include <sys/socket.h>
#include <arpa/inet.h>


#define PORT 8080
#define BACKLOG 10 //This time I know this isn't overkill for bind lol


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
                Yeah and I checked wtf is 'network-byte-order' apparently it is 
                stored in big-endian unlike most of modern CPU architecture using little-endian...
                What that implies? No fucking clue

    */



    int opt = 1;

    mkdir("todoThingies", 0755);    //I guess that was the 'Fuck it everybody can see it but only I CAN touch it' mode in octal
    //For Future Neuro: This shit will use getenv to get $HOMe then crate .folder (invisible) so I don't get distracted by 218937218 html files
    //But first let serve a fucking html 

    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    //AF_INET = Internet as fuck
    //SOCK_STREAM = TCP

    if (server_sock == -1)
    {
        perror("Socket sucked it");
        exit(EXIT_FAILURE); // Macro for 1 just a fancy way to say 1
    }

    setsockopt(server_sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    
    //Poor man's getaddrinfo()
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);
    //he htons() function converts the unsigned short integer hostshort from host byte order to network byte order.
    //I have no fucking idea what that implies...I think I shouldn't attempt to do this now but I need the to-do app I forget shit
    //Just learned what this does: It converts the host byte-order to network-byte-order for 16bit ints
    //Berkley nerds of the past...WTF?
    //Besides beej had said getaddrinfo() fills those for me...Did I just peel another abstraction layer by accident?

    if ((bind(server_sock, (struct sockaddr *)&server_addr,sizeof(server_addr)) == -1)) {
        perror("Future me use err() with acutal error code for these shits...IT'S GONNA LOOK FANCY in JournalCTL logs(I hope it won't fail tho)");
        exit(EXIT_FAILURE);
    }

    if(listen(server_sock, BACKLOG) == -1)
    {
        perror("Mwah    OwO");
        close(server_sock); //Yk...sockets are file descriptors so we close it as we open them
        exit(1);
    }

        printf("Server is running on http://localhost:%d\n", PORT);
    /*
    while (1) {
      This is where I need to read more shit...man I need a fucking Ouija Board and talk with Dennis for a few mins 
    }
    */


    return(0);
}
