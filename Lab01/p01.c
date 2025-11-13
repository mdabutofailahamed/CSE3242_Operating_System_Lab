#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    pid_t pid;

    // Fork a child process
    pid = fork();

    if (pid < 0) { // Fork failed
        printf("Fork Failed\n");
    }
    else if (pid == 0) { // Child process
        printf("Child Process PID = %d\n",getpid());
        printf("Parent PID = %d\n",getppid());
    }
    else { // Parent process
        printf("Parent Process PID = %d\n",getpid());
        printf("Child PID = %d\n",pid);

        printf("Child process completed.\n");
    }

    //printf("Out of Parent/Child process\n"); //This will be called by both Parents and Child

    return 0;
}
