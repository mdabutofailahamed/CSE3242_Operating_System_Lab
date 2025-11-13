#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    printf("Parent process (parent_process, PID: %d) started.\n", getpid());

    for (int i = 1; i <= 3; i++) {
        pid_t pid = fork(); // Create a new process

        if (pid < 0) {
            perror("Fork failed");
            exit(EXIT_FAILURE);
        } else if (pid == 0) { // Child process
            printf("Child_%d (PID: %d, Parent PID: %d) started.\n", i, getpid(), getppid());
            //sleep(2); // Simulate work in child
            printf("Child_%d (PID: %d) is terminating.\n", i, getpid());

            exit(0); // Terminate child process
        }
        // Parent process continues the loop to create the next child
    }

    // Parent waits for all child processes to finish
    for (int i = 1; i <= 3; i++) {
        wait(NULL);
    }

    printf("Parent process (parent_process, PID: %d) terminating.\n", getpid());
    return 0;
}
