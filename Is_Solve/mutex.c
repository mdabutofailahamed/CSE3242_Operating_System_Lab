

/*

	Write a multithreaded C program to perform some multithreaded tasks.
	The program should do the following:

	One thread gets numbers from the user. Then, a second thread orders those
	numbers using a sorting algorithm. And lastly, a third thread should print
	the sorted numbers.

*/


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int *numbers;
int size;

pthread_mutex_t lock;


void *get_numbers(void *param) {

    pthread_mutex_lock(&lock);

    printf("Enter the number of elements: ");
    scanf("%d", &size);

    numbers = (int *)malloc(size * sizeof(int));

    if (numbers == NULL) {

        fprintf(stderr, "Memory allocation failed\n");

        exit(EXIT_FAILURE);

    }

    printf("Enter %d numbers: ", size);
    for (int i = 0; i < size; i++) {
        scanf("%d", &numbers[i]);
    }

    pthread_mutex_unlock(&lock);
    pthread_exit(0);

}


void *sort_numbers(void *param) {

    pthread_mutex_lock(&lock); // Lock the mutex

    for (int i = 0; i < size - 1; i++) {

        for (int j = 0; j < size - i - 1; j++) {

            if (numbers[j] > numbers[j + 1]) {

                int temp = numbers[j];
                numbers[j] = numbers[j + 1];
                numbers[j + 1] = temp;

            }

        }

    }

    pthread_mutex_unlock(&lock); // Unlock the mutex
    pthread_exit(0);

}


void *print_numbers(void *param) {

    pthread_mutex_lock(&lock);

    printf("Sorted numbers: ");

    for (int i = 0; i < size; i++) {
        printf("%d ", numbers[i]);
    }

    printf("\n");

    pthread_mutex_unlock(&lock);
    pthread_exit(0);

}


int main() {

    pthread_t tid1, tid2, tid3;

    pthread_mutex_init(&lock, NULL);

    pthread_create(&tid1, NULL, get_numbers, NULL);
    pthread_join(tid1, NULL);

    pthread_create(&tid2, NULL, sort_numbers, NULL);
    pthread_join(tid2, NULL);

    pthread_create(&tid3, NULL, print_numbers, NULL);
    pthread_join(tid3, NULL);

    pthread_mutex_destroy(&lock);
    free(numbers);

    return 0;

}
