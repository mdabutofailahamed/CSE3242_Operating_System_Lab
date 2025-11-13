/*


	Write a multithreaded program that calculates various statistical values for a list of numbers.
	This program will be passed a series of numbers on the command line and will then create three
	separate worker threads:

	>	One thread will determine the average of the numbers.

	>	The second will determine the maximum value.

	>	The third will determine the minimum value.



*/


#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>


float average;
int minimum;
int maximum;

int count = 0;
int *values;

void thread1_controller(){
	average = 0;

	for(int i=0;i<count;i++){
		average += values[i];
	}

	average = average/count;
}

void thread2_controller(){
	minimum = 99999999;
	for(int i=0;i<count;i++){
		if(minimum > values[i]){
			minimum = values[i];
		}
	}
}

void thread3_controller(){
	maximum = 0;
	for(int i=0;i<count;i++){
		if(maximum < values[i]){
			maximum = values[i];
		}
	}
}


int main(int argc, char* argv[]){

	count = argc - 1;

	values = (int*) malloc(count * sizeof(int));

	for (int i=0;i<count;i++){
		values[i] = atoi(argv[i+1]);//argv[i + 1] refers to the command-line arguments passed by the user, starting from the first argument (not the program name).
		//The atoi() function converts a string (C-style) to an integer. It takes a const char* (a string) as an argument and returns an integer
	}

	pthread_t thread1, thread2, thread3;

	pthread_create(&thread1, NULL, (void*)thread1_controller, NULL);//A pointer to a pthread_t variable where the new thread’s ID will be stored
	pthread_create(&thread2, NULL, (void*)thread2_controller, NULL);//Passing NULL means the default attributes will be used. stack size null
	pthread_create(&thread3, NULL, (void*)thread3_controller, NULL);//This is the argument that will be passed to the thread function (thread1_controller).
	// Here, NULL is passed, indicating that no arguments will be passed to the thread function.


	pthread_join(thread1, NULL);//ensuring that the main thread (or any calling thread) waits for the created thread to finish its task
	pthread_join(thread2, NULL);//If the thread does not return any value or if you don't care about the return value, you can pass NULL.
	pthread_join(thread3, NULL);


	printf("Averages: %.2f\n", average);
	printf("Minimum: %.d\n", minimum);
	printf("Maximum: %.d\n", maximum);
}
