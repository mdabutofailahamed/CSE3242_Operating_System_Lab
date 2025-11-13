#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    // Main process
    pid_t pid1, pid2, pid3;

    printf("Parent Process: PID = %d\n", getpid());

    // Creating the first child
    pid1 = fork();

    if (pid1 < 0) {
        // Fork failed
        perror("Fork failed for child_1");
        exit(1);
    } else if (pid1 == 0) {
        // This is child_1 process
        printf("Child_1: PID = %d, Parent PID = %d\n", getpid(), getppid());
        exit(0); // End child_1 process
    } else {
        // Creating the second child
        pid2 = fork();

        if (pid2 < 0) {
            // Fork failed
            perror("Fork failed for child_2");
            exit(1);
        } else if (pid2 == 0) {
            // This is child_2 process
            printf("Child_2: PID = %d, Parent PID = %d\n", getpid(), getppid());
            exit(0); // End child_2 process
        } else {
            // Creating the third child
            pid3 = fork();

            if (pid3 < 0) {
                // Fork failed
                perror("Fork failed for child_3");
                exit(1);
            } else if (pid3 == 0) {
                // This is child_3 process
                printf("Child_3: PID = %d, Parent PID = %d\n", getpid(), getppid());
                exit(0); // End child_3 process
            }
        }
    }

    // Wait for all child processes to finish
    wait(NULL);
    wait(NULL);
    wait(NULL);

    printf("Parent Process PID = %d is terminating.\n", getpid());

    return 0;
}

