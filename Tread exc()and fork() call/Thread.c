#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

// Function executed by each thread
void *thread_function(void *arg) {
    printf("Thread %ld started (PID: %d)\n", (long)arg, getpid());
    sleep(2); // Simulate work

    if ((long)arg == 1) { // Let the first thread call fork()
        printf("Thread %ld calling fork()...\n", (long)arg);
        pid_t pid = fork();

        if (pid < 0) {
            perror("fork failed");
            pthread_exit(NULL);
        } else if (pid == 0) { // Child process
            printf("In child process after fork (PID: %d, Parent PID: %d)\n", getpid(), getppid());

            // Uncomment the line below to test exec() behavior immediately after fork()
             execlp("/bin/ls", "ls", NULL);

            sleep(1); // Simulate work in child
            printf("Child process terminating (PID: %d)\n", getpid());
            exit(0);
        } else {
            // Parent process waits for child to complete
            wait(NULL);
        }
    }

    // Let one thread call exec()
    if ((long)arg == 2) {
        printf("Thread %ld calling exec()...\n", (long)arg);
        execlp("/bin/echo", "echo", "Hello from exec!", NULL);
        // If exec succeeds, this line will not be printed
        perror("exec failed");
        pthread_exit(NULL);
    }

    printf("Thread %ld terminating (PID: %d)\n", (long)arg, getpid());
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[3];
    printf("Main process started (PID: %d)\n", getpid());

    // Create multiple threads
    for (long i = 0; i < 3; i++) {
        if (pthread_create(&threads[i], NULL, thread_function, (void *)i) != 0) {
            perror("Failed to create thread");
            exit(1);
        }
    }

    // Wait for all threads to complete
    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Main process terminating (PID: %d)\n", getpid());
    return 0;
}
