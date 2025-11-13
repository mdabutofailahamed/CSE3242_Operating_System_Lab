/*

	Write a program to write to a named pipe what is read from the keyboard using open(), read(), and write() system calls.
	
	
	
	Check the messages written to the pipe in a different terminal using : cat /home/israk/my_named_pipe

*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define BUFFER_SIZE 1024


int main() {
	
    const char *pipePath = "/home/israk/my_named_pipe";
	
    char buffer[BUFFER_SIZE];
    int pipeFd;


    // Open the named pipe for writing
    pipeFd = open(pipePath, O_WRONLY);
	
    if (pipeFd == -1) {
		
        perror("Failed to open named pipe");
		
        exit(EXIT_FAILURE);
		
    }


    printf("Enter text (type 'exit' to quit):\n");


    // Read from keyboard and write to the pipe
    while (1) {
		
        // Read input from the keyboard
        if (fgets(buffer, BUFFER_SIZE, stdin) == NULL) {
			
            perror("Failed to read from keyboard");
			
            close(pipeFd);
			
            exit(EXIT_FAILURE);
			
        }


        // Check for the "exit" command to break the loop
        if (strncmp(buffer, "exit", 4) == 0) {
            break;
        }

        // Write the input to the named pipe
        if (write(pipeFd, buffer, strlen(buffer)) == -1) {
			
            perror("Failed to write to named pipe");
			
            close(pipeFd);
			
            exit(EXIT_FAILURE);
			
        }
    }


    // Close the named pipe
    close(pipeFd);
	
    return 0;
	
}
