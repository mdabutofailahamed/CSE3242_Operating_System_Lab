#define _GNU_SOURCE
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>
//#include <sys/sysctl.h>
#include <sys/types.h>

int num_cores;  // To store the number of cores
int num_processes; // Number of processes to create

// Function to get the number of CPU cores
int get_num_cores() {
    // Linux or Unix-like systems: using sysctl
    return sysconf(_SC_NPROCESSORS_ONLN);
}

// Function to get the CPU core the thread is currently running on
void get_cpu() {
    cpu_set_t cpuset;
    int cpu;

    pthread_t current_thread = pthread_self();
    pthread_getaffinity_np(current_thread, sizeof(cpu_set_t), &cpuset);

    // Find the CPU the thread is running on
    for (cpu = 0; cpu < num_cores; cpu++) {
        if (CPU_ISSET(cpu, &cpuset)) {
            printf("Thread is running on core: %d\n", cpu);
            return;
        }
    }
}

// Function to set the CPU affinity for the current thread
void set_cpu(int core_id) {
    cpu_set_t cpuset;

    CPU_ZERO(&cpuset);
    CPU_SET(core_id, &cpuset);

    // Set the CPU affinity of the current thread
    int result = pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpuset);
    if (result != 0) {
        perror("Error setting CPU affinity");
        exit(EXIT_FAILURE);
    }
}

// Thread function
void* thread_function(void* arg) {
    int thread_num = *((int*)arg);
    int core_id = thread_num % num_cores;  // Distribute threads across available cores

    set_cpu(core_id);  // Set the thread to the designated core
    get_cpu();  // Check which core it has been set to

    printf("Thread %d started on core %d\n", thread_num, core_id);
    return NULL;
}

// Process function
void* process_function(void* arg) {
    int process_num = *((int*)arg);
    pthread_t threads[3];
    int thread_nums[3];

    printf("Process %d started\n", process_num);

    // Create 3 threads for each process
    for (int i = 0; i < 3; i++) {
        thread_nums[i] = process_num * 3 + i;  // Assign unique thread numbers
        pthread_create(&threads[i], NULL, thread_function, &thread_nums[i]);
    }

    // Wait for all threads to finish
    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }

    return NULL;
}

int main() {
    num_cores = get_num_cores();  // Get the number of CPU cores
    num_processes = num_cores + 4;  // Create 4 more processes than the number of cores

    printf("System has %d CPU cores\n", num_cores);

    pthread_t processes[num_processes];

    // Create processes and assign threads to cores
    for (int i = 0; i < num_processes; i++) {
        pthread_create(&processes[i], NULL, process_function, &i);
    }

    // Wait for all processes to finish
    for (int i = 0; i < num_processes; i++) {
        pthread_join(processes[i], NULL);
    }

    return 0;
}
