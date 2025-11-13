/*

	Write a C program to create a main process named parent_process having n child processes without any grandchildren processes.
	Child processes’ names are child_1, child_2, child_3, ..., child_n. Trace the position in the process tree. The number of child
	processes (n) and the names of child processes will be given in the CLI of Linux-based systems.

	Example:	$ ./parent_process 3 child_1 child_2 child_3

	Hint: fork(), exec(), fopen(), system()


*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {

    if (argc < 3) {

        fprintf(stderr, "Usage: %s <n> <child_1> <child_2> ... <child_n>\n", argv[0]);

        return 1;

    }

    int n = atoi(argv[1]);  // Number of child processes

    if (argc != n + 2) {

        fprintf(stderr, "Error: Please provide %d child names.\n", n);

        return 1;

    }


    printf("Parent Process (parent_process) PID: %d started.\n\n", getpid());


    for (int i = 0; i < n; i++) {

        pid_t pid = fork();

        if (pid < 0) {

            perror("Fork failed");
            exit(EXIT_FAILURE);

        } else if (pid == 0) {

            // Inside child process
            printf("Child Process: %s (PID: %d), Parent PID: %d\n", argv[i + 2], getpid(), getppid());
        sleep(10);
            // Replace child process image with another executable (if needed)
            // execlp(argv[i + 2], argv[i + 2], NULL);  // Uncomment if child is a separate executable

            exit(EXIT_SUCCESS);

        }
    }


    // Parent process waits for all child processes to finish
    for (int i = 0; i < n; i++) {

        wait(NULL);

    }


    printf("\nParent Process (parent_process) PID: %d has finished.\n", getpid());

    return 0;

}
