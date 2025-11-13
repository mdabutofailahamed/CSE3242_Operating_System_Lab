#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(void) {
    pid_t child_pid, parent_pid;
    child_pid = fork(); // fork a child process

    if(child_pid < 0) { // error occured
        printf("Fork failed.\n");
        return 1;
    }
    else if(child_pid == 0) { // child process
        printf("I am a child, my pid is %d and parent pid is %d\n", getpid(), getppid());
    }
    else { // parent process
        printf("I am parent, my child pid is %d and my pid is %d\n", child_pid, getpid());
    }
}