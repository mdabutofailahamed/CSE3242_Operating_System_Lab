#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>


#define BUFFER_SIZE 1024


void read_pipe() {

    char buffer[BUFFER_SIZE];

    char *pipe_path = "/home/israk/2ndPipe";

    ssize_t bytesRead;

    int pipe_fd = open(pipe_path, O_RDONLY);

    if (pipe_fd == -1) {

        perror("Failed to open named pipe for read -- Person 2");

        exit(EXIT_FAILURE);

    }

    printf("Reading from named pipe...\n");

    // Continuously read from the pipe and display the content
    while ((bytesRead = read(pipe_fd, buffer, BUFFER_SIZE - 1)) > 0) {

        buffer[bytesRead] = '\0';  // Null-terminate the string

        // Write the content to the standard output
        if (write(STDOUT_FILENO, buffer, bytesRead) == -1) {

            perror("Failed to write to standard output");

            close(pipe_fd);

            exit(EXIT_FAILURE);

        }

    }


    if (bytesRead == -1) {

        perror("Failed to read from named pipe");

    }


    // Close the named pipe
    //close(pipeFd);

    exit(0);

}


void write_pipe() {

    char buffer[BUFFER_SIZE];

    char *pipe_path = "/home/israk/1stPipe";

    // Open the named pipe for writing
    int pipe_fd = open(pipe_path, O_WRONLY);

    if (pipe_fd == -1) {
		
    	perror("Failed to open named pipe for writing -- Person 2");
		
       	exit(EXIT_FAILURE);
		
    }

    printf("Enter text (type 'exit' to quit):\n");

    // Read from keyboard and write to the pipe
    while (1) {
		
        // Read input from the keyboard
        if (fgets(buffer, BUFFER_SIZE, stdin) == NULL) {
			
            perror("Failed to read from keyboard");
			
            close(pipe_fd);
			
            exit(EXIT_FAILURE);
			
        }


        // Check for the "exit" command to break the loop
        if (strncmp(buffer, "exit", 4) == 0) {
            break;
        }

        // Write the input to the named pipe
        if (write(pipe_fd, buffer, strlen(buffer)) == -1) {
			
            perror("Failed to write to named pipe");
			
            close(pipe_fd);
			
            exit(EXIT_FAILURE);
			
        }
    }

    // Close the named pipe
    //close(pipeFd);

    exit(0);

}


int main() {

    pthread_t tid1, tid2;

    pthread_create(&tid1, NULL, (void*)read_pipe, NULL);
    pthread_create(&tid2, NULL, (void*)write_pipe, NULL);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    return 0;

}