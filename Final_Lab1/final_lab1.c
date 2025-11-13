#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
 if (argc != 4) {
    printf("Error: Incorrect number of arguments.\n");
    printf("Usage: %s <name> <num1> <num2>\n", argv[0]);
    exit(EXIT_FAILURE);
}

    // Extracting command line arguments
    char *name = argv[1];
    int num1 = atoi(argv[2]);
    int num2 = atoi(argv[3]);
    int result = 0;

    printf("result = %d\n", result);

    pid_t pid1, pid2;

    // Create the first child process for addition
    pid1 = fork();
    if (pid1 < 0) {
        perror("Fork failed for addition");
        exit(EXIT_FAILURE);
    } else if (pid1 == 0) {
        // Child process for addition
        result = num1 + num2;
        printf("ChildProcess-%d: addition_result = %d\n", getpid(), result);
        exit(EXIT_SUCCESS);
    }

    // Create the second child process for subtraction
    pid2 = fork();
    if (pid2 < 0) {
        perror("Fork failed for subtraction");
        exit(EXIT_FAILURE);
    } else if (pid2 == 0) {
        // Child process for subtraction
        result = num1 - num2;
        printf("ChildProcess-%d: subtraction_result = %d\n", getpid(), result);
        exit(EXIT_SUCCESS);
    }

    // Parent process waiting for both child processes to finish
    int status;
    pid_t child_pid;

    child_pid = wait(&status);
    if (child_pid > 0) {
        printf("Child %d successfully finished.\n", child_pid);
    }

    child_pid = wait(&status);
    if (child_pid > 0) {
        printf("Child %d successfully finished.\n", child_pid);
    }

    return 0;
}
