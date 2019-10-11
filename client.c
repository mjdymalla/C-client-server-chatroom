#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char *argv[]) {
    
    // CREATE A SOCKET
    int network_socket;
    network_socket = socket(AF_INET, SOCK_STREAM, 0);

    // SPECIFYING THE ADDRESS FOR THE SOCKET - SERVER
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);
    server_address.sin_addr.s_addr = INADDR_ANY;

    // CONNECTION STATUS
    int connection_status = connect(network_socket, (struct sockaddr*) &server_address, sizeof(server_address));

    // CHECK FOR ERROR WITH THE CONNECTION
    if (connection_status== -1) {
        printf("There was an error making a connection to the remote socket \n\n");
    }

    // RECEIVE DATA FROM THE SERVER
    char server_response[256];
    recv(network_socket, &server_response, sizeof(server_response), 0);

    // PRINT OUT SERVERS RESPONSE
    printf("The server sent the data: %s\n\n", server_response);

    // AND THEN CLOSE THE SOCKET
    close(network_socket);

    return 0;
}