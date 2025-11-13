#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s <number_of_children> <child_name_1> <child_name_2> ... <child_name_n>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]); // Convert the first argument to an integer for the number of children

    // Check if the number of child processes matches the count of names provided
    if (argc != n + 2) {
        printf("Error: Number of child process names provided does not match the specified count.\n");
        return 1;
    }

    printf("Parent process (PID: %d) started.\n", getpid());

    for (int i = 0; i < n; i++) {
        pid_t pid = fork(); // Create a new process

        if (pid < 0) {
            perror("fork failed");
            exit(EXIT_FAILURE);
        } else if (pid == 0) { // Child process
            printf("Child process %s (PID: %d, Parent PID: %d) started.\n", argv[i + 2], getpid(), getppid());

            // The child process can perform its own task here or simply terminate.
            // For this implementation, we're not using exec since the children are not running different programs.

            // For example, the child can use sleep to simulate some work:
            sleep(2); // Simulate some work with sleep

            printf("Child process %s (PID: %d) is terminating.\n", argv[i + 2], getpid());
            exit(0); // Terminate the child process
        } else {
            // Parent process continues to the next iteration
            // Optionally, we can wait for each child to terminate (synchronously):
            wait(NULL);
        }
    }

    // If waiting for all children to finish, use this loop:
    for (int i = 0; i < n; i++) {
        wait(NULL); // Wait for all child processes to complete
    }
    sleep(10);
    printf("Parent process (PID: %d) terminating.\n", getpid());

    return 0;
}
