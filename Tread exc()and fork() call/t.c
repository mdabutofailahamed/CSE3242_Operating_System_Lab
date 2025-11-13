#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

// Function executed by each thread
void *thread_function(void *arg) {
    long thread_id = (long)arg;
    printf("Thread %ld started (PID: %d)\n", thread_id, getpid());
    sleep(2); // Simulate some work

    // Part A: One thread calls fork()
    if (thread_id == 1) {
        printf("Thread %ld calling fork()...\n", thread_id);
        pid_t pid = fork();

        if (pid < 0) {
            perror("fork failed");
            pthread_exit(NULL);
        } else if (pid == 0) { // Child process
            printf("Child process created by fork (PID: %d, Parent PID: %d)\n", getpid(), getppid());

            // Sleep to observe the behavior
            sleep(2);

            // Check if other threads exist in the child process
            printf("Child process (PID: %d) checking if other threads are present...\n", getpid());
            sleep(2);
            printf("Child process (PID: %d) terminating...\n", getpid());
            exit(0);
        } else {
            // Parent process waits for child to complete
            wait(NULL);
        }
    }

    // Part B: Another thread calls exec()
    if (thread_id == 2) {
        printf("Thread %ld calling exec()...\n", thread_id);
        execlp("/bin/echo", "echo", "Hello from exec!", NULL);

        // If exec() succeeds, the following line will not be executed
        perror("exec failed");
        pthread_exit(NULL);
    }

    printf("Thread %ld terminating (PID: %d)\n", thread_id, getpid());
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
