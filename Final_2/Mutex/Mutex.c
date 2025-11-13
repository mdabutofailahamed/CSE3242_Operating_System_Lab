#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_ITERATIONS 1000000

int counter = 0;               // Global variable
pthread_mutex_t counter_mutex;  // Mutex for protecting counter

void* increment_without_mutex(void* arg) {
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        counter++;  // Increment counter without mutex protection
    }
    return NULL;
}

void* increment_with_mutex(void* arg) {
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        pthread_mutex_lock(&counter_mutex);  // Lock the mutex
        counter++;                           // Increment counter with mutex protection
        pthread_mutex_unlock(&counter_mutex);  // Unlock the mutex
    }
    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    // Demonstrate data inconsistency without mutex
    printf("Demonstrating data inconsistency without mutex:\n");
    counter = 0;  // Reset counter
    pthread_create(&thread1, NULL, increment_without_mutex, NULL);
    pthread_create(&thread2, NULL, increment_without_mutex, NULL);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    printf("Expected counter value: %d\n", NUM_ITERATIONS * 2);
    printf("Actual counter value without mutex: %d\n", counter);

    // Demonstrate consistency with mutex
    printf("\nDemonstrating data consistency with mutex:\n");
    counter = 0;  // Reset counter
    pthread_mutex_init(&counter_mutex, NULL);  // Initialize mutex
    pthread_create(&thread1, NULL, increment_with_mutex, NULL);
    pthread_create(&thread2, NULL, increment_with_mutex, NULL);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    printf("Expected counter value: %d\n", NUM_ITERATIONS * 2);
    printf("Actual counter value with mutex: %d\n", counter);

    pthread_mutex_destroy(&counter_mutex);  // Destroy mutex
    return 0;
}
