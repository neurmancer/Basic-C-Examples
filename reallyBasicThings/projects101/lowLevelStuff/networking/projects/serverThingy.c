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

        Scope creep section:
            1-Get rid of the html storage idea and use a .db to store addresses
            2-Createa a 'template.html' and fill it with the context from database
            3-Suffer while thinking about why I am doing this without jinja-templates
            4-Markdown style rendering (since it's easier to read and shit yk...I got used to it too fast)
            5-



        Eaiser said than done right?

        How hard can it be...


        I need this server since my ideas keep getting bigger and bigger and I need a fucking tracker of those
        What's next coding my own issue-tracker? (tho that would work...AND THIS IS THE REASON THAT I NEED A TO-DO APP)
        And ladies and gentlemen...this is how I am gonna end up with a git clone at 4AM one night

        and I'll be using snake_case to feel like a real C programmer this time

        Started working on this at: 3 September 2026 00.42AM - Planned Due Date:Hopefully before 2027  

        AND FIRST TO-DO IN THE LIST will be 'Make your own web-framework' 
        this shit is getting out of hand


*/


//Headers that I know why here (at least for my initila draft)
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <sys/errno.h>  
#include <err.h>    //Yeah now we're in BSD territory
//Headers that I have no fucking idea about
#include <sys/socket.h>
#include <arpa/inet.h>


#define PORT 8080
#define BACKLOG 10 //This time I know this isn't overkill for bind lol
#define BUF_SIZE 8192   //Two-pages of bytes are good yk...

#define TODO_DIR "todoThingies" //Yeah I am future-proofing my typos

//These gonna bite me in the ass when I wanna change the infrastructure to .db
void send_404(int client_socket);
void send_homepage(int client_socket);
void send_todo_page(int client_socket, const char *filename);

//Handlers
void handle_update(int client_socket, char *body);
void handle_delete(int client_socket, char *body);
void handle_post(int client_socket, char *body);

//Todo
void create_todo_file(const char *content);


//Helpers
void url_decode(char *str);


int main(void)
{

    int server_sock = 0, client_sock = 0;
    struct sockaddr_in server_addr = { 0 }, client_addr = { 0 }; 

    const int TODO_DIR_LEN = sizeof(TODO_DIR);
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

    mkdir(TODO_DIR, 0755);    //I guess that was the 'Fuck it everybody can see it but only I CAN touch it' mode in octal
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
    while (1) {
        client_sock = accept(server_sock, (struct sockaddr *)&client_addr, &client_len);
        if (client_sock == -1) {
            perror("Faith has spoken");
            continue;
        }
        char buf[BUF_SIZE] = { 0 };
        ssize_t bytes = recv(client_sock, buf, sizeof(buf)-1, 0);
    
    /*
        RETURN VALUE
            Upon  successful  completion, recv() shall return the length of the message in bytes. If no
            messages are available to be received and the  peer  has  performed  an  orderly  shutdown,
            recv() shall return 0. Otherwise, -1 shall be returned and errno set to indicate the error.
                
            so...I gotta handle both 0 and -1 I guess
    */

        if (bytes <= 0 ) {
            close(client_sock);
            continue;
        }
        
        char method[16] = { 0 };
        char path[512] = { 0 };
        sscanf(buf, "%15s %511s", method, path);    
        //I mean you should know this at this point but %is means scanf reads i bytes and prevents overflow

        printf("Request: %s %s\n", method, path);

        if (strcmp(method, "POST") == 0)  {
            char *body = strstr(buf, "\r\n\r\n");
            /*
            DESCRIPTION
    
                strstr() finds the first occurrence of the substring needle in the string haystack.
                Brooo...haystack? Needle? which cursed person chose the names? 
                This is way shitpostier than my names
            */   
            if (body) {
                body += 4;
                //This is where I need to make the helper funcitons

                if (strcmp(path, "/update") == 0) { handle_update(client_sock, body); }
                else if (strcmp(path, "/delete") == 0) { handle_delete(client_sock, body); }
                else { handle_post(client_sock, body); }
            }
        }

        else if (strcmp(path, "/") == 0 || strcmp(path, "/index.html") == 0) {
            send_homepage(client_sock);
            //yeah this could've been just an after thougt like an @app.route decorator...
            //Had I known Python instead of C... 
        }

        else if (strncmp(path, "/"TODO_DIR"/", TODO_DIR_LEN+2) == 0) {
            send_todo_page(client_sock,path+TODO_DIR_LEN+2); //if I forget those slashes that's gonna fuck me bad
        }

        else {
            send_404(client_sock);
        }

        close(client_sock);
    }


    close(server_sock);
    return(0);
}


void send_404(int client_socket)
{
        const char *msg =
        "HTTP/1.1 404 Not Found\r\n"
        "Content-Type: text/html\r\n"
        "Connection: close\r\n\r\n"
        "<h1 style='font-family:sans-serif; color:#ff5555;'>404 -You Lost Lulz</h1>"
        "<a href='/' style='color:#4CAF50;'>Go back home</a>";
        send(client_socket, msg, strlen(msg), 0);
}


void send_homepage(int client_socket)
{
    const char *header =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html\r\n"
        "Connection: close\r\n\r\n";
    send(client_socket, header, strlen(header), 0);

    const char *top =
        "<!DOCTYPE html>\n"
        "<html lang=\"en\">\n"
        "<head>\n"
        "  <meta charset=\"UTF-8\">\n"
        "  <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n"
        "  <title>Todo App</title>\n"
        "  <style>\n"
        "    body { font-family: sans-serif; background: #111; color: #eee; max-width: 700px; margin: 40px auto; padding: 20px; }\n"
        "    input[type=text] { width: 70%%; padding: 12px; font-size: 16px; border: none; border-radius: 6px; }\n"
        "    button { padding: 12px 20px; font-size: 16px; background: #4CAF50; color: white; border: none; border-radius: 6px; cursor: pointer; }\n"
        "    .card { background: #222; padding: 16px 20px; margin: 12px 0; border-radius: 8px; display: block; text-decoration: none; color: #eee; transition: 0.15s; }\n"
        "    .card:hover { background: #333; transform: translateY(-2px); }\n"
        "    h1 { color: #4CAF50; }\n"
        "    h2 { margin-top: 40px; color: #aaa; font-size: 18px; }\n"
        "  </style>\n"
        "</head>\n"
        "<body>\n"
        "  <h1>Neuro's Cyberspace™</h1>\n"
        "  <form action=\"/\" method=\"POST\">\n"
        "    <input type=\"text\" name=\"todo\" placeholder=\"What do you need to do?\" required>\n"
        "    <button type=\"submit\">Create</button>\n"
        "  </form>\n"
        "  <h2>Your todos</h2>\n";

    DIR *dir = opendir(TODO_DIR);
    //Again will swap with $HOME/.todo 
    
    if (dir) {
        struct dirent *entry;
        int count = 0;


        while ((entry = readdir(dir)) != NULL) {
            //probably this search will be O(n) if I don't organize shit to use binary-search
            if (entry->d_name[0] == '.') { continue; }
            if (strstr(entry->d_name, ".html") == NULL) { continue; }

            char fpath[512] = { 0 };
            snprintf(fpath, sizeof(fpath), TODO_DIR"/%s", entry->d_name);
            
            char title[512] = { 0 };    //This is an overflow waiting to happen(stack vars are the last thing I trust)
            FILE *file = fopen(fpath, "r"); //Should I use read-binary? No clue
            if (file) {
                fread(title, 1,  sizeof(title)-1, file);
                fclose(file);
            }

            if (title[0] == '\0') {
                strncat(title, entry->d_name, sizeof(title)-1);
            }

            char card[1024] = { 0 }; 
            snprintf(card, sizeof(card), 
            "<a class=\"card\" href=\"/todos/%s\">%s</a>\n",
            entry->d_name, title);

            send(client_socket, card, strlen(card), 0);
            count++;
            //Been gone to get cigs I'll continue when I return
        }
        closedir(dir);

        if (!count) {
            const char *empty = "<p style=\"color:#666;\">No todos yet. Create one above.</p>\n";
            send(client_socket, empty, strlen(empty), 0);
            //WTF can the send 'flags' be
        }
    }

    const char *bottom = "</body>\n</html>\n";  //Bruh hand-rolling HTMLL is fucking exhausting
    send(client_socket, bottom, strlen(bottom), 0);
}

void handle_update(int client_socket, char *body)
{
    //How should I get unique IDs... let's say id=filename.html&content=new+text

    char *id_start = strstr(body, "id=");
    char *content_start = strstr(body, "content=");

    if (!id_start || !content_start) {
        send_homepage(client_socket);
        return;
    }

}

//I wonder what happens if I put [[gnu::noreturn]] instead of void lol
void handle_post(int client_socket, char *body)
{
    char *todo_begins = strstr(body, "todo=");
    //Yeah this is a Batman Begins joke
    if (!todo_begins) {
        send_homepage(client_socket);
        return;
    }

    todo_begins += 5;
    char *todo_returns = strpbrk(todo_begins, "&\r\n");
    
    /*
    The  strpbrk() function locates the first occurrence in the string s of any of the bytes in
        the string accept.
    */

    if (todo_returns) { *todo_returns = '\0'; }

    url_decode(todo_begins);

    printf(">>> New shit dropped: %s\n",todo_begins);
    create_todo_file(todo_begins);

    const char *redirect =
        "HTTP/1.1 303 See Other\r\n"
        "Location: /\r\n"
        "Connection: close\r\n\r\n";
    
    send(client_socket, redirect, strlen(redirect), 0);

}






void url_decode(char *str)
{
    char *src = str;
    char *dst = str;    //classic <string.h> notation

    while (*src) {
        if (*src == '+') {
            *dst++ = ' ';
            src++;
        }

        else if(*src == '%' && src[1] && src[2]) {
            char hex[3] = {src[1], src[2], '\0'};
            *dst++ = (char)strtol(hex, NULL, 16); //Hexadecimal
            src += 3;
        }

        else { *dst++ = *src++; }  
    }
    *dst = '\0'; //U forget that = U fuked
}