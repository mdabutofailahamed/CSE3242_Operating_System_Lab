#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int main()
{
    pid_t pid = fork();
    if(pid == 0) {
        printf("I have finished my work and now I am zombie\n");
    }
    else { // You can find the zombie process using ps aux | grep ’Z’ command
        sleep(100);
    }
    wait(NULL);
}