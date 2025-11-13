#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>

// Function to handle the signal
void signal_handler(int sig) {
    if (sig == SIGUSR1) {
        printf("Thread %ld received SIGUSR1 signal!\n", pthread_self());
    }
}

// Thread function for the receiver thread
void *receiver_thread(void *arg) {
    // Set up the signal handler
    struct sigaction sa;
    sa.sa_handler = signal_handler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);

    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("sigaction failed");
        pthread_exit(NULL);
    }

    printf("Receiver thread (ID: %ld) is waiting for signals...\n", pthread_self());

    // Keep the thread alive to handle signals
    while (1) {
        pause(); // Wait for any signal to be delivered
    }

    pthread_exit(NULL);
}

// Thread function for the sender thread
void *sender_thread(void *arg) {
    pthread_t *receiver_tid = (pthread_t *)arg;
    sleep(2); // Simulate some work before sending the signal

    printf("Sender thread (ID: %ld) sending SIGUSR1 signal to receiver thread...\n", pthread_self());
    pthread_kill(*receiver_tid, SIGUSR1); // Send SIGUSR1 to the receiver thread

    pthread_exit(NULL);
}

int main() {
    pthread_t sender_tid, receiver_tid;

    // Create the receiver thread
    if (pthread_create(&receiver_tid, NULL, receiver_thread, NULL) != 0) {
        perror("Failed to create receiver thread");
        exit(1);
    }

    // Create the sender thread
    if (pthread_create(&sender_tid, NULL, sender_thread, (void *)&receiver_tid) != 0) {
        perror("Failed to create sender thread");
        exit(1);
    }

    // Wait for the sender thread to finish
    pthread_join(sender_tid, NULL);
    printf("Sender thread has finished.\n");

    // Optionally, cancel the receiver thread after demonstration
    pthread_cancel(receiver_tid);
    pthread_join(receiver_tid, NULL);
    printf("Receiver thread has been terminated.\n");

    return 0;
}
