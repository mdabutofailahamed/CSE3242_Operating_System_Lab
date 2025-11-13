#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>

void signal_handler(int signal) {
    if(signal == SIGUSR1) {
        printf("Thread 1: I have received the SIGUSR1 signal. Terminating gracefully.\n");
        sleep(1);
        for(int i = 0; i < 3; i++) {
            printf("Thread 1: Terminating...\n");
            sleep(1);
        }
        printf("Thread 1: Terminated.\n");
        pthread_exit(NULL);
    }
}

void* thread_handler1() {
    signal(SIGUSR1, signal_handler);

    // Waiting for the signal
    for(int i = 0; i < 100; i++) {
        printf("Thread 1: Waiting...\n");
        sleep(2);
    }

}

void* thread_handler2(void *arg) {
    pthread_t *pid = (pthread_t*) arg;
    printf("Thread 2: Sending a SIGUSR1 signal to Thread 1.\n");
    sleep(2);
    for(int i = 0; i < 3; i++) {
        printf("Thread 2: Sending...\n");
        sleep(2);
    }
    printf("Thread 2: Signal Sent.\n");
    pthread_kill(*pid, SIGUSR1);
}

void main() {
    pthread_t tid1, tid2;
    pthread_create(&tid1, NULL, thread_handler1, NULL);
    pthread_create(&tid2, NULL, thread_handler2, &tid1); // Send tid1 as argumant
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
}

/* Output:
Thread 2: Sending a SIGUSR1 signal to Thread 1.
Thread 1: Waiting...
Thread 2: Sending...
Thread 1: Waiting...
Thread 2: Sending...
Thread 1: Waiting...
Thread 1: Waiting...
Thread 2: Sending...
Thread 2: Signal Sent.
Thread 1: Waiting...
Thread 1: Waiting...
Thread 1: I have received the SIGUSR1 signal. Terminating gracefully.
Thread 1: Terminating...
Thread 1: Terminating...
Thread 1: Terminating...
Thread 1: Terminated.
*/
