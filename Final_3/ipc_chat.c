#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

#define BUFFER_SIZE 100

int main()
{
    int pipe1[2], pipe2[2];
    pid_t pid;
    char buffer[BUFFER_SIZE];
    char message[BUFFER_SIZE];

    // Create two pipes
    if (pipe(pipe1) == -1 || pipe(pipe2) == -1)
    {
        perror("Pipe creation failed");
        exit(1);
    }

    // Fork to create a child process
    pid = fork();

    if (pid < 0)
    {
        perror("Fork failed");
        exit(1);
    }

    if (pid > 0)   // Parent Process
    {
        close(pipe1[0]); // Close reading end of pipe1
        close(pipe2[1]); // Close writing end of pipe2

        while (1)
        {
            // Parent sends a message to child
            printf("Parent: Enter a message: ");
            fgets(message, BUFFER_SIZE, stdin);//use input device so use stdin ,standared input stream
            message[strcspn(message, "\n")] = '\0'; // Remove newline character,string complement span
            write(pipe1[1], message, strlen(message) + 1);/* because the null terminator (\0)
                                                         of the string needs to be written to the pipe. */

            // Break the loop if "GoodBye" is sent
            if (strcmp(message, "GoodBye") == 0)
            {
                break;
            }

            // Parent waits for a message from child
            read(pipe2[0], buffer, BUFFER_SIZE);
            printf("Parent received: %s\n", buffer);

            // Break the loop if "GoodBye" is received
            if (strcmp(buffer, "GoodBye") == 0)
            {
                break;
            }
        }

        close(pipe1[1]);
        close(pipe2[0]);

    }

    else   // Child Process
    {
        close(pipe1[1]); // Close writing end of pipe1
        close(pipe2[0]); // Close reading end of pipe2

        while (1)
        {
            // Child waits for a message from parent
            read(pipe1[0], buffer, BUFFER_SIZE);
            printf("Child received: %s\n", buffer);

            // Break the loop if "GoodBye" is received
            if (strcmp(buffer, "GoodBye") == 0)
            {
                break;
            }

            // Child sends a response message
            printf("Child: Enter a message: ");
            fgets(message, BUFFER_SIZE, stdin);
            message[strcspn(message, "\n")] = '\0'; // Remove newline character using null value
            write(pipe2[1], message, strlen(message) + 1);

            // Break the loop if "GoodBye" is sent
            if (strcmp(message, "GoodBye") == 0)
            {
                break;
            }
        }

        close(pipe1[0]);
        close(pipe2[1]);
    }

    return 0;
}
