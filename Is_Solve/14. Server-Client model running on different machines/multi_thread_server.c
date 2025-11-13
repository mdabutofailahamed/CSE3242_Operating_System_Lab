/*


    Server process (multi-threaded) tries to provide services to multiple client processes.


*/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>


#define PORT 8080
#define BUFFER_SIZE 1024


void *handle_client(void *client_socket)
{
    int socket = *(int *) client_socket;
    char buffer [BUFFER_SIZE] = {0};

    read(socket, buffer, BUFFER_SIZE);
    printf("Received : %s\n", buffer);

    send(socket, buffer, strlen (buffer), 0);
    printf("Echoed : %s\n", buffer);

    close(socket);
    free(client_socket);
    pthread_exit(NULL);
}


int main ()
{
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {

        perror("socket failed");

        exit(EXIT_FAILURE);

    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd,(struct sockaddr *)&address, sizeof(address)) < 0)
    {

        perror("bind failed");

        close(server_fd);

        exit(EXIT_FAILURE);

    }

    if (listen(server_fd, 3) < 0)
    {

        perror("listen failed");

        close(server_fd);

        exit(EXIT_FAILURE);

    }

    while (1)
    {

        printf("Waiting for a connection...\n");

        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
        {

            perror("accept failed");

            close(server_fd);

            exit(EXIT_FAILURE);

        }

        printf("Connection accepted\n");

        pthread_t thread_id;

        int *client_socket = malloc(sizeof(int));
        *client_socket = new_socket;

        if (pthread_create(&thread_id, NULL, handle_client, (void *) client_socket) != 0)
        {

            perror("pthread_create failed");

            close(new_socket);

            free(client_socket);

        }

    }

    close(server_fd);

    return 0;

}
