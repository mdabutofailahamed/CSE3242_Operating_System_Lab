/*
Run the code with and without calling wait()
and observe the output
*/

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    pid_t child_pid = fork();
    int n;
    if(child_pid == 0) {
        n = 1;
    }
    else {
        n = 6;
        // wait(NULL);
    }
    for(int i = n; i < n + 5; i++) {
        printf("%d ", i);
    }
    printf("\n");
}