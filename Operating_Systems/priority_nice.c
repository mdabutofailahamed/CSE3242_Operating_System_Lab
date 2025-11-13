#define _GNU_SOURCE
#include <stdio.h>
#include <sched.h>
#include <unistd.h>
#include <sys/resource.h>

void main() {
    int core = sched_getcpu();
    int priority = getpriority(PRIO_PROCESS, 0);
    printf("Core: %d, Priority: %d\n", core, priority);

    setpriority(PRIO_PROCESS, 0, 2);
    nice(15); // priority should be (2 + 15) or 17
    priority = getpriority(PRIO_PROCESS, 0);
    printf("Core: %d, Priority: %d\n", core, priority);

    setpriority(PRIO_PROCESS, 0, 19); // Or you can directly change it
    priority = getpriority(PRIO_PROCESS, 0);
    printf("Core: %d, Priority: %d\n", core, priority);

    // This part tries to reduce priority value, but failed
    nice(-14);
    priority = getpriority(PRIO_PROCESS, 0);
    printf("Core: %d, Priority: %d\n", core, priority);
}

/* Output may look like this
Core: 2, Priority: 0
Core: 2, Priority: 17
Core: 2, Priority: 19
Core: 2, Priority: 19
*/