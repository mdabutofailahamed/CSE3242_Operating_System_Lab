/*

	4. Write a C program to create a main process named parent_process having 3 child processes without any grandchildren processes.
	Trace parent and child processes in the process tree. Show that child processes are doing addition, subtraction, and multiplication
	on two variables initialized in the parent_process.


*/



#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    pid_t pid1, pid2, pid3;
    int a = 10, b = 5;
    int result;

    printf("Parent process PID: %d started.\n", getpid());

    pid1 = fork();

    if (pid1 < 0) {

        perror("Fork failed");
        exit(EXIT_FAILURE);

    } else if (pid1 == 0) {

        // First child process
        printf("Child-1 PID: %d: Performing addition.\n", getpid());

        result = a + b;

        printf("Child-1 PID: %d: %d + %d = %d\n\n", getpid(), a, b, result);

        exit(EXIT_SUCCESS);
    }


    pid2 = fork();

    if (pid2 < 0) {

        perror("Fork failed");
        exit(EXIT_FAILURE);

    } else if (pid2 == 0) {

        // Second child process
        printf("Child-2 PID: %d: Performing subtraction.\n", getpid());

        result = a - b;

        printf("Child-2 PID: %d: %d - %d = %d\n\n", getpid(), a, b, result);

        exit(EXIT_SUCCESS);
    }


    pid3 = fork();

    if (pid3 < 0) {

        perror("Fork failed");
        exit(EXIT_FAILURE);

    } else if (pid3 == 0) {

        // Third child process
        printf("Child-3 PID: %d: Performing multiplication.\n", getpid());

        result = a * b;

        printf("Child-3 PID: %d: %d x %d = %d\n\n", getpid(), a, b, result);

        exit(EXIT_SUCCESS);
    }


    // Parent process waits for all child processes to finish
    wait(NULL);
    wait(NULL);
    wait(NULL);


    printf("Parent process PID: %d finished.\n", getpid());

    return 0;
}
