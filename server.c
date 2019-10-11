#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char *argv[]) {

    // SERVER MESSAGE ON CONNECTIONS
    char server_message[256] = "you have reached the server\n\n";

    // CREATE THE SERVER SOCKET
    int server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    //DEFINE THE SERVER ADDRESSu
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(12345);
    server_address.sin_addr.s_addr = INADDR_ANY;

    // BIND THE SOCKET TO OUR SPECIFIED IP AND PORT
    bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));

    // LISTEN FOR CONNECTIONS
    listen(server_socket, 5);

    int client_socket;
    client_socket = accept(server_socket, NULL, NULL);

    // SEND THE DEFINED MESSAGE
    send(client_socket, server_message, sizeof(server_message), 0);

    // CLOSE THE SOCKET
    close(server_socket);

    return 0;
}