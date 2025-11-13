/*

	Write a program to create a named pipe using the mkfifo() system call.

*/


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>


int main() {
	
    const char *pipePath = "/home/israk/my_named_pipe";

    // Create the named pipe (FIFO)
    if (mkfifo(pipePath, 0666) == -1) {
		
        perror("mkfifo failed");
		
        exit(EXIT_FAILURE);
		
    }

    printf("Named pipe created at: %s\n", pipePath);

    return 0;
	
}