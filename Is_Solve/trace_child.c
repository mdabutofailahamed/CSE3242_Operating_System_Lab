/*


	Write a C program to create a main process named parent_process having 3 child processes without any grandchildren processes.
	Child processes’ names are child_1, child_2, child_3. Trace the position in the process tree.

	pstree -p

*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{

    pid_t pid1, pid2, pid3;

    printf("Parent Process (parent_process) PID: %d\n\n", getpid());

    // Create first child process
    pid1 = fork();

    if (pid1 < 0)
    {

        perror("Fork failed for child_1");
        exit(EXIT_FAILURE);

    }
    else if (pid1 == 0)
    {

        // Inside child_1 process
        printf("Child Process: child_1 (PID: %d), Parent PID: %d\n", getpid(), getppid());

        sleep(10);

        exit(EXIT_SUCCESS);

    }


    // Create second child process
    pid2 = fork();

    if (pid2 < 0)
    {

        perror("Fork failed for child_2");
        exit(EXIT_FAILURE);

    }
    else if (pid2 == 0)
    {

        // Inside child_2 process
        printf("Child Process: child_2 (PID: %d), Parent PID: %d\n", getpid(), getppid());
        sleep(10);
        exit(EXIT_SUCCESS);

    }


    // Create third child process
    pid3 = fork();

    if (pid3 < 0)
    {

        perror("Fork failed for child_3");

        exit(EXIT_FAILURE);

    }
    else if (pid3 == 0)
    {

        // Inside child_3 process
        printf("Child Process: child_3 (PID: %d), Parent PID: %d\n", getpid(), getppid());
        sleep(10);
        exit(EXIT_SUCCESS);

    }


    // Parent process waits for all child processes to finish
    wait(NULL);  // Waiting for child_1
    wait(NULL);  // Waiting for child_2
    wait(NULL);  // Waiting for child_3


    printf("\nParent Process (parent_process) PID: %d has finished.\n", getpid());

    return 0;

}
