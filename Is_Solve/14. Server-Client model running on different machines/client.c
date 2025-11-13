


/*   Client Code    */



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>


#define PORT 8080
#define BUFFER_SIZE 1024


int main() {

    int sock = 0;

    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE] = {0};


    //char *message = "Hello from client";
	char message[100];
	//scanf("%s",message);
	fgets(message, sizeof(message), stdin);

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {

        perror("Socket creation error");

        return -1;

    }


    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);


    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {

        perror("Invalid address / Address not supported");

        return -1;

    }


    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {

        perror("Connection failed");

        return -1;

    }


    send(sock, message, strlen(message), 0);
    printf("Message sent: %s\n", message);

    int valread = read(sock, buffer, BUFFER_SIZE);
    printf("Server response: %s\n", buffer);

    close(sock);

    return 0;

}
