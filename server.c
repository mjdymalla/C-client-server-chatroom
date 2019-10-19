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

void *thread_data(void *vargp) {
    printf("Server: thread created for client connection \n\n");
    return NULL;    
}

int main(int argc, char *argv[]) {

    // THREAD ATTRIBUTES
    pthread_t client_thread; 
    pthread_attr_t attr;

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
    server_address.sin_port = htons(atoi(argv[1]));
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

    printf("Server: listening on port %d\n\n", server_address.sin_port);

    // CREATE MAIN ACCEPT LOOP
    while(1) {
        sin_size = sizeof(struct sockaddr_in);
        new_socket = accept(server_socket, (struct sockaddr *)&connector_address, &sin_size);
        pid_t current_process;
        if (new_socket == -1) {
            perror("accept");
            continue;
        }

        printf("Server: got connection from %s\n\n", inet_ntoa(connector_address.sin_addr));
        
        // CREATE NEW PROCESS FOR CLIENT
        if ((current_process = fork()) == -1)
        {
            close(new_socket);
        }
        else if (current_process == 0) {  
            int id = getpid(); 
            printf("New client process - ID: %d - Server: %d\n\n", id, getppid()); 
            char message[256] = "Welcome to the server! Your Client ID is: \n\n";
            write(new_socket, &message, sizeof(message)); 
            while (current_process == 0) {
                char client_message[2000] = "";
                recv(new_socket, &client_message, sizeof(client_message), 0);
                printf("message from Client %d - %s\n", id, client_message);
                if (client_message == "exit") {
                    close(new_socket);
                    break;
                }
            }  
        }
        
        
        
        
        
        
            
        
        // CREATE A THREAD FOR CLIENT
        //pthread_attr_t attr;
        //pthread_attr_init(&attr);
        //pthread_create(&client_thread, &attr, send_data, &new_socket);
        //pthread_join(client_thread, NULL);
        
        
        
        

        
    }

    return 0;
    
      
}