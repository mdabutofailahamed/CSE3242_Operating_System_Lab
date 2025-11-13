#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid;

    // Fork a child process
    pid = fork();

    if (pid < 0)
    {
	// Fork failed

        fprintf(stderr, "Fork Failed\n");
        return 1;
    }

    else if (pid == 0) { // Child process

	printf("Child Process: PID = %d, Parent PID = %d\n", getpid(), getppid());

        // Replace the child process image with a new executable
       // execlp("./child_program", "child_program", NULL);

        // If execlp() fails
      fprintf(stderr, "execlp() Failed\n");

	printf("Hello HI\n");

        return 1;
    }

    else { // Parent process

        printf("Parent Process: PID = %d, Child PID = %d\n", getpid(), pid);

        // Wait for the child process to complete
        wait(NULL);

        printf("Child process completed.\n");
    }

    return 0;
}
