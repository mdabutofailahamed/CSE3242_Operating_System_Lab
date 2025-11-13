/*

	Server process (single-threaded) tries to provide services to multiple client processes.

*/

//Including Headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>

//Constants and Function
#define PORT 8080
#define BUFFER_SIZE 1024


void handle_client(int client_socket) {

	char buffer [BUFFER_SIZE] = {0};

	read(client_socket, buffer, BUFFER_SIZE);
	printf("Received : %s\n", buffer);

//Flags for the transmission. 0 indicates no special options are set.
	send(client_socket, buffer, strlen(buffer), 0);
	printf("Echoed : %s\n", buffer);

	close(client_socket);
}


int main() {

	int server_fd, new_socket;
	struct sockaddr_in address;
	int addrlen = sizeof(address);
//Creating the Server Socket
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
		perror("socket failed");
		exit(EXIT_FAILURE);
	}
//Configuring the Server Address
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);
//Binding the Socket
	if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
		perror("bind failed");
		close(server_fd);
		exit(EXIT_FAILURE);
	}
// Listening for Connections
//3, specifies the maximum number of pending connections
	if (listen(server_fd, 3) < 0) {
		perror("listen failed");
		close(server_fd);
		exit(EXIT_FAILURE);
	}

	while(1) {

		printf("Waiting for a connection...\n");
// Accepting Connections
		if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
			perror("accept failed");
			close(server_fd);
			exit(EXIT_FAILURE);
		}

		printf("Connection accepted\n");
//Handling Clients with fork()
		pid_t pid = fork();

		if (pid < 0) {

			perror("fork failed");
			close(new_socket);

		} else if (pid == 0) {
//Child Process: Handling the Client
			close(server_fd);
			handle_client(new_socket);
			exit(0);

		} else {
//parent process closes the client's socket
			close(new_socket);
//ensures that finished child processes are reaped
			waitpid(-1, NULL, WNOHANG);

		}
	}

	close(server_fd);
	return 0;

}
