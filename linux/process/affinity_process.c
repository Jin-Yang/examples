#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // _SC_NPROCESSORS_CONF
#define __USE_GNU   /* to use CPU_SET() */
#include "sched.h"

// gcc main.c -o runatcpu
int main(int argc, char* argv[])
{
    unsigned int i, j, which_cpu, cpu_all;
    cpu_set_t cpu_set;

    if ( 2 != argc ) {
        printf( "Usage:\n$ ./runatcpu cpu_number\n" );
        return -1;
    }

    cpu_all = sysconf(_SC_NPROCESSORS_CONF); // cpu is 0~(cpu_all-1)
    printf("Notice: current system has %i CPU(s).\n", cpu_all);
    which_cpu = atoi(argv[1]);        // which cpu

    CPU_ZERO(&cpu_set);               // clear the cpu set.
    CPU_SET(which_cpu, &cpu_set);     // set the cpu
    // CPU_CLR(which_cpu, &cpu_set);  // or clear
    // int sched_setaffinity(pid_t pid, size_t cpusetsize, cpu_set_t *mask);
    if (-1 == sched_setaffinity(0, sizeof(cpu_set), &cpu_set))
        printf( "!!! Error: bind current process to specified CPU failed !!!\n" );
    /* OR ************
     * unsigned long mask = 7; // processors 0, 1, and 2
     * unsigned int len = sizeof(mask);
     * if (sched_setaffinity(0, len, &mask) < 0)  perror("xx");
     */

    for ( j = 0; j < 10; j++ ) {
        CPU_ZERO(&cpu_set); // clear cpu set

        // int sched_getaffinity(pid_t pid, size_t cpusetsize, cpu_set_t *mask);
        if (-1 == sched_getaffinity(0, sizeof(cpu_set), &cpu_set))
            printf( "!!! Error: get current process was bound which CPU failed !!!\n" );

        for ( i = 0; i < cpu_all; i++ )
            if (CPU_ISSET(i, &cpu_set)) // test if the process on this cpu
                printf( "Current process is running at %d CPU\n", i );
        usleep(10000);
    }
    return 0;
}


