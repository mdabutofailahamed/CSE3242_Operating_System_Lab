#define _GNU_SOURCE
#include <stdio.h>
#include <pthread.h>
#include <sched.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

void get_cpu_info(char *process_type, char *thread_type) {
    int core_id;
    for(int i = 0; i < 10; i++) {
        core_id = sched_getcpu();
        printf("%s, %s, Core ID: %d\n", process_type, thread_type, core_id);
    }
}

void sub_thread(char *process_type) {
    get_cpu_info(process_type, "Sub Thread");
}

void main() {
    // Get how many cores are there in the system
    int cores = sysconf(_SC_NPROCESSORS_ONLN);
    printf("There are %d cores in the system\n", cores);

    // fork a child
    pid_t pid = fork();

    if(pid == 0) { // Child process
        pthread_t tid;
        pthread_create(&tid, NULL, (void*)sub_thread, "Child");
        get_cpu_info("Child", "Main Thread");
        pthread_join(tid, NULL);
    }
    else { // Parent process
        pthread_t tid;
        pthread_create(&tid, NULL, (void*)sub_thread, "Parent");
        get_cpu_info("Parent", "Main Thread");
        pthread_join(tid, NULL);
    }
}

/* Output which shows that core is changed at runtime
There are 4 cores in the system
Parent, Main Thread, Core ID: 0
Parent, Main Thread, Core ID: 0
Parent, Main Thread, Core ID: 0
Parent, Main Thread, Core ID: 0
Parent, Main Thread, Core ID: 0
Parent, Main Thread, Core ID: 0
Parent, Main Thread, Core ID: 0
Parent, Main Thread, Core ID: 0
Parent, Main Thread, Core ID: 0
Parent, Main Thread, Core ID: 0
Parent, Sub Thread, Core ID: 3
Parent, Sub Thread, Core ID: 3
Parent, Sub Thread, Core ID: 3
Parent, Sub Thread, Core ID: 3
Parent, Sub Thread, Core ID: 3
Parent, Sub Thread, Core ID: 3
Parent, Sub Thread, Core ID: 3
Parent, Sub Thread, Core ID: 3
Parent, Sub Thread, Core ID: 3
Child, Main Thread, Core ID: 2
Parent, Sub Thread, Core ID: 3
Child, Main Thread, Core ID: 2
Child, Main Thread, Core ID: 2
Child, Main Thread, Core ID: 2
Child, Sub Thread, Core ID: 0
Child, Sub Thread, Core ID: 0
Child, Sub Thread, Core ID: 0
Child, Sub Thread, Core ID: 0
Child, Sub Thread, Core ID: 0
Child, Sub Thread, Core ID: 0
Child, Sub Thread, Core ID: 0
Child, Sub Thread, Core ID: 0
Child, Sub Thread, Core ID: 0
Child, Sub Thread, Core ID: 0
Child, Main Thread, Core ID: 2 // Main thread of Chlid is migrated
Child, Main Thread, Core ID: 0 // from core 2 to 0
Child, Main Thread, Core ID: 0
Child, Main Thread, Core ID: 0
Child, Main Thread, Core ID: 0
Child, Main Thread, Core ID: 0
*/