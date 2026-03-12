/*
simple port scanner written in C
Made by ml0w6c65766c
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>



char hostname[100];     // var for ip
int start;             // var for start port
int end;               // var for end port
int open_ports = 0;



void ascii_banner() {
    printf(
        "\n"
        "       __  ___   ____             __  _____                                 \n"
        "      /  |/  /  / __ \\____  _____/ /_/ ___/_________ _____  ____  ___  _____\n"
        "     / /|_/ /  / /_/ / __ \\/ ___/ __/\\__ \\/ ___/ __ `/ __ \\/ __ \\/ _ \\/ ___/\n"
        "    / /  / /  / ____/ /_/ / /  / /_ ___/ / /__/ /_/ / / / / / / /  __/ /    \n"
        "   /_/  /_/  /_/    \\____/_/   \\__//____/\\___/\\__,_/_/ /_/_/ /_/\\___/_/     \n"
        "                                                                              \n"
        "   simple portscanner v0.1                                                                           \n"
        "   made by Github: https://github.com/ml0w6c65766c                                                 \n"
        "\n"
        "\n"
    );
}


void clear(){        // clear screen function
    system("@cls||clear");
}

int scan_port(int port) {
    int sock;                  //socket number (eg. 3)
    struct sockaddr_in target; // struct target includes sin_family,sin_port,sin_addr

    // Creates tcp,ipv4 socket
    sock = socket(AF_INET, SOCK_STREAM, 0);

    // Zieladresse konfigurieren
    target.sin_family = AF_INET;            // specifies the protocl in this case IPv4
    target.sin_port = htons(port);          // port in network byte order creates a network format every computer understands.
    inet_pton(AF_INET, hostname, &target.sin_addr); // convert ip so the socket understands it

    // 
    if (connect(sock, (struct sockaddr*)&target, sizeof(target)) == 0) { // connect has 3 parameters sock(eg. 3), the size and where to connect(ip + target) 
        close(sock);  // closes sock (eg. 3, view "var int sock")
        return 1; // Port open
    }

    close(sock);  // closes sock (eg. 3, view "var int sock")
    return 0; // Port closed
}


void main_menu() {


    ascii_banner();    //ascii banner
    printf("Enter target ip: \n");
    printf("> ");
    fgets(hostname, sizeof(hostname), stdin);
    hostname[strcspn(hostname, "\n")] = '\0';   //remove newline(/n)
    clear();
    printf("Enter start port: \n");
    printf("> ");
    scanf("%d", &start);
    while(getchar() != '\n');          // remove newline(/n)
    printf("\n\n");
    printf("Enter end port: \n");
    printf("> ");
    scanf("%d", &end);
    while(getchar() != '\n');    //remove newline(/n)
    clear();
    // Scan Info
    printf("Target IP: %s\n", hostname);
    printf("Port Range: %d - %d\n\n", start, end);
    printf("Scanning...\n\n");

}




int main() {
    main_menu();
    

    for(int i = start; i<= end; i++ ){     //runs the scan_port function until it reaches "end"
        if(scan_port(i)){
            printf("[OPEN] %d\n", i); // prints all open ports
            open_ports++;
            
        }
        
    }


    // scan summarys
    printf("Scan finished\n"); // print when scan is finished
    printf("Open Ports: %d\n", open_ports); // shows open ports (only number)
}
