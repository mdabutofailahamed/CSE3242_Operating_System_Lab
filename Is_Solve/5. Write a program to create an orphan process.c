#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    pid_t pid;

    pid = fork();

    if (pid < 0) {

        perror("Fork failed");
        exit(EXIT_FAILURE);

    } 

    else if (pid > 0) {

        // Parent process
        printf("Parent process PID: %d is terminating.\n", getpid());
        exit(EXIT_SUCCESS);  // Parent process terminates

    }

    else {

        // Child process
        sleep(5);  // Sleep to ensure the parent terminates before the child

        printf("\nChild process PID: %d is now an orphan, adopted by init PID: 1\n", getpid());
        printf("Child process PID: %d is continuing execution.\n", getpid());

        // The child can perform other tasks or just terminate
        //sleep(2);  // Additional sleep to observe the orphan status

        printf("Child process PID: %d is terminating.\n", getpid());
	exit(EXIT_SUCCESS);

    }

    return 0;
}
