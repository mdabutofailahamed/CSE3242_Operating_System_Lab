#define _GNU_SOURCE
#include <stdio.h>
#include <sched.h>
#include <unistd.h>

void main() {
    // Print number of cores
    int cores = sysconf(_SC_NPROCESSORS_ONLN);
    printf("Number of cores: %d\n", cores);

    // Print which core the process is running on
    int cpu_id = sched_getcpu();
    printf("Currently running on: %d\n", cpu_id);

    // Get the affinity that is on which core the process is allowed to run
    cpu_set_t mask;
    sched_getaffinity(0, sizeof(cpu_set_t), &mask);
    printf("Before changing affinity: ");
    for(int i = 0; i < cores; i++) {
        printf("%d ", CPU_ISSET(i, &mask));
    }
    printf("\n");
    // Output may look like '1 1 1 1' in a core i3 or '1 1 1 1 1 1 1 1' in a core i5 processor
    // that means the process is allowed to run all the processing core

    // Set the process to a specific core
    CPU_ZERO(&mask); // Clear the mask
    CPU_SET(2, &mask); // core 2 is allowed for the process to run
    sched_setaffinity(0, sizeof(cpu_set_t), &mask); // 0 means this process

    // Print if the setaffinity is successful
    sched_getaffinity(0, sizeof(cpu_set_t), &mask);
    printf("After changing affinity : ");
    for(int i = 0; i < cores; i++) {
        printf("%d ", CPU_ISSET(i, &mask));
    }
    printf("\n");
    // Output may look like '0 0 1 0' in a core i3 or '0 0 1 0 0 0 0 0  ' in a core i5 processor
    // that means the process is allowed to run only on core 2

    // Let's check if it is true
    cpu_id = sched_getcpu();
    printf("Currently running on: %d\n", cpu_id);
}

/* An illustrative output for core i3 processor
Number of cores: 4
Currently running on: 1
Before changing affinity: 1 1 1 1 
After changing affinity : 0 0 1 0 
Currently running on: 2
*/