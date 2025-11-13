#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
    pid_t pid;

    pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process
        printf("Child process PID: %d is terminating.\n", getpid());
        exit(EXIT_SUCCESS);  // Child process terminates, becoming a zombie
    } else {
        // Parent process
        printf("Parent process PID: %d is sleeping.\n", getpid());
        sleep(10);  // Parent process sleeps, not collecting child's status
        printf("Parent process PID: %d is waking up.\n", getpid());

        // Collecting the child's exit status, removing it from zombie state
        wait(NULL);

        printf("Parent process PID: %d finished.\n", getpid());
    }

    return 0;
}
