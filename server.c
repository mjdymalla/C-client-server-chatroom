#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>
#include <pthread.h>

#define BACKLOG 10

int main(int argc, char *argv[]) {

    // THREAD ATTRIBUTES
    pthread_t client_thread;
    pthread_attr_t attr;

    // SERVER MESSAGE ON CONNECTIONS
    char server_message[256] = "you have reached the server\n\n";

    // DEFINE THE SERVER ADDRESS
    int server_socket, new_socket;
    struct sockaddr_in server_address;
    socklen_t sin_size;

    // DEFINE CONNECTORS ADDRESS INFORMATION
    struct sockaddr_in connector_address;

    // GET PORT NUMBER FROM COMMAND LINE TO LISTEN ON
    if (argc != 2) {
        fprintf(stderr, "usage: client port_number\n");
        exit(1);
    }

    // CREATE THE SERVER SOCKET
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    // GENERATE END POINT 
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(12345);
    server_address.sin_addr.s_addr = INADDR_ANY;

    // BIND THE SOCKET TO OUR SPECIFIED IP AND PORT
    if (bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address)) == -1) {
        perror("bind");
        exit(1);
    }

    // LISTEN FOR CONNECTIONS
    if (listen(server_socket, BACKLOG) == -1) {
        perror("listen");
        exit(1);
    }

    printf("server starts listening on port %d\n", server_address.sin_port);

    // CREATE MAIN ACCEPT LOOP
    while(1) {
        sin_size = sizeof(struct sockaddr_in);
        if ((new_socket = accept(server_socket, (struct sockaddr *)&connector_address, &sin_size)) == -1) {
            perror("accept");
            continue;
        }
        printf("server: got connection from %s\n", inet_ntoa(connector_address.sin_addr));

        
        
    }

    

    // CLOSE THE SOCKET
    close(new_socket);

    
}