#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h> 
#include <string.h> 
#include <netdb.h> 

// DEFAULT PORT 
#define default_port 12345

#define MAXDATASIZE 100

int main(int argc, char *argv[]) {
    
    // CREATE A SOCKET
    int network_socket, port;
    char buffer[MAXDATASIZE];
    struct hostent *he;
    
    // CHECK COMMAND LINE ARGUMENTS
    if (argc < 2) {
        fprintf(stderr, "usage: client hostname\n");
        exit(1);
    }

    if (argc > 2) {
        port = atoi(argv[2]);
    } else port = default_port;

    if ((he=gethostbyname(argv[1])) == NULL) {
        herror("gethostbyname");
        exit(1);
    }

    // CHECK SOCKET CREATION
    if ((network_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    // SPECIFYING THE ADDRESS FOR THE SOCKET - SERVER
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);
    server_address.sin_addr = *((struct in_addr *)he->h_addr);

    // CONNECTION STATUS
    if (connect(network_socket, (struct sockaddr *)&server_address, \
    sizeof(struct sockaddr)) == -1) {
        perror("connect");
        exit(1);
    }

    // RECEIVE DATA FROM THE SERVER
    char server_response[256];
    recv(network_socket, &server_response, sizeof(server_response), 0);

    // PRINT OUT SERVERS RESPONSE
    printf("The server sent the data: %s\n", server_response);

    // AND THEN CLOSE THE SOCKET
    close(network_socket);

    return 0;
}