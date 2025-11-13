#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void main()
{
    pid_t pid = fork();
    if(pid == 0) {
        printf("I have a parent, my parent's PID is %d\n", getppid());
        sleep(2); // If you want to see them in pstree, increase the sleep time
        printf("Now I am an orphan and adopted by a process having PID %d\n", getppid());
    }
    else {
        sleep(1); // If you want to see them in pstree, increase the sleep time
    }
}