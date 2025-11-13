#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;

    // Fork a child process
    pid = fork();

    if (pid < 0) { // Fork failed
        printf("Fork Failed\n");
    }
    else if (pid == 0) { // Child process
        printf("Child Process PID = %d\n", getpid());
        printf("Parent PID = %d\n", getppid());

	printf("Child process completed.\n");
    }
    else { // Parent process
        wait(NULL); // Parent waits for the child to complete
        printf("Parent Process PID = %d\n", getpid());
        printf("Child PID = %d\n", pid);

        printf("Parent process completed.\n");
    }

    return 0;
}
