#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>


#define BUFFER_SIZE 1024


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
    fflush(stdout);


    // Read input from the keyboard
    if (fgets(buffer, BUFFER_SIZE, stdin) == NULL) {
		
        perror("Failed to read from keyboard");
		
        close(pipe_fd);
		
        exit(EXIT_FAILURE);
		
    }


    // Write the input to the named pipe
    if (write(pipe_fd, buffer, strlen(buffer)) == -1) {
		
        perror("Failed to write to named pipe");
		
        close(pipe_fd);
		
        exit(EXIT_FAILURE);
		
    }


    // Check for the "exit" command
    if (strncmp(buffer, "exit", 4) == 0) {
		
        close(pipe_fd);
		
        exit(EXIT_SUCCESS);
		
    }


    close(pipe_fd);
	
}


void read_pipe() {
	
    char buffer[BUFFER_SIZE];
	
    char *pipe_path = "/home/israk/2ndPipe";


    // Open the named pipe for reading
    int pipe_fd = open(pipe_path, O_RDONLY);
	
    if (pipe_fd == -1) {
		
        perror("Failed to open named pipe for reading -- Person 2");
		
        exit(EXIT_FAILURE);
		
    }


    printf("Reading from named pipe...\n");
	
    fflush(stdout);
	

    // Read from the pipe and display the content
    ssize_t bytesRead = read(pipe_fd, buffer, BUFFER_SIZE - 1);
	
    if (bytesRead > 0) {
		
        buffer[bytesRead] = '\0'; // Null-terminate the string
		
        printf("Received: %s", buffer);
		
        fflush(stdout);
		

        // Check if the received message is "exit"
        if (strncmp(buffer, "exit", 4) == 0) {
			
            close(pipe_fd);
			
            exit(EXIT_SUCCESS);
			
        }
		
    } 
	
	else if (bytesRead == -1) {
		
        perror("Failed to read from named pipe");
		
    }


    close(pipe_fd);
	
}


int main() {
	
    while (1) {
		
        read_pipe();
		
        write_pipe();
		
    }
	
    return 0;
	
}
