#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
    pid_t pid = fork();

    if (pid == 0) {
        execlp("./child_process", "child_process", NULL);
    }
    else {
        sleep(2);
        printf("Parent: Child Completed.\n");
    }
    return 0;
}