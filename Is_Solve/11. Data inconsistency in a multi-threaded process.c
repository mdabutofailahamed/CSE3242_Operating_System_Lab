
/*

	Write a C program to show how data inconsistency arises in a multi-threaded process.

*/


#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>


//int x = 10;

int balance = 500;

void thread1_controller(){
	
	balance = balance - 200;
	printf("Withdrawn 200 tk, new balance %d tk\n", balance);

	/*int temp = x;
	printf("Thread-1 :: temp = %d || current X = %d\n",temp,x);

	temp = temp + 1;
	printf("Thread-1 :: temp = %d || current X = %d\n",temp,x);

	x = temp;
	printf("Thread-1 :: temp = %d || current X = %d\n",temp,x);*/
}

void thread2_controller(){

	balance = balance - 350;
	printf("Withdrawn 350 tk, new balance %d tk\n", balance);

	/*int temp = x;
	printf("Thread-2 :: temp = %d || current X = %d\n",temp,x);

	printf("Thread-2 :: temp = %d || current X = %d\n",temp,x);
	temp = temp - 1;

	printf("Thread-2 :: temp = %d || current X = %d\n",temp,x);
	x = temp;*/
}


int main(){

	pthread_t thread1, thread2;
	
	pthread_create(&thread1, NULL, (void*)thread1_controller, NULL);
	pthread_create(&thread2, NULL, (void*)thread2_controller, NULL);
	
	
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

	//sleep(5);

	//printf("Final X : %d\n",x);
}
