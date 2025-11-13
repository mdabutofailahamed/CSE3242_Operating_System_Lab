/*
Two threads are proforming different operation on the
global array numbers, their outputs may interleave
each other because both are running parallely
*/
#include <stdio.h>
#include <pthread.h>

int numbers[5] = {2, 3, 4, 5, 6};

void* square() {
    for(int i = 0; i < 5; i++) {
        printf("Thread 1: %d^2 = %d\n", numbers[i], numbers[i] * numbers[i]);
    }
}

void* negative() {
    for(int i = 0; i < 5; i++) {
        printf("Thread 2: %d\n", -numbers[i]);
    }
}

void main() {
    pthread_t tid1, tid2;
    pthread_create(&tid1, NULL, square, NULL);
    pthread_create(&tid2, NULL, negative, NULL);
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
}