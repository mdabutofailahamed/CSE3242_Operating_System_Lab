/*


    Server process (single-threaded) tries to provide services to multiple client processes with multiple child processes.


*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void handle_client(int client_socket) {

    char buffer[BUFFER_SIZE] = {0};

    read(client_socket, buffer, BUFFER_SIZE);
    printf("Received: %s\n", buffer);

    send(client_socket, buffer, strlen(buffer), 0);
    printf("Echoed: %s\n", buffer);

    close(client_socket);

}

int main() {

    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);


    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {

        perror("socket failed");

        exit(EXIT_FAILURE);

    }


    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);


    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {

        perror("bind failed");

        close(server_fd);

        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {

        perror("listen failed");

        close(server_fd);

        exit(EXIT_FAILURE);

    }


    while (1) {

        printf("Waiting for a connection...\n");

        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) {

            perror("accept failed");

            close(server_fd);

            exit(EXIT_FAILURE);

        }

        printf("Connection accepted\n");

        pid_t pid = fork();

        if (pid < 0) {

            perror("fork failed");

            close(new_socket);

        } else if (pid == 0) {

            close(server_fd);

            handle_client(new_socket);

            exit(0);

        } else {

            close(new_socket);

            waitpid(-1, NULL, WNOHANG);

        }
    }

    close(server_fd);

    return 0;
}
