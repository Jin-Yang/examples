#include <stdio.h>
#include <unistd.h>  /* _SC_NPROCESSORS_CONF */
#define __USE_GNU    /* use macros like CPU_SET() */
#include <sched.h>
#include <pthread.h>

// gcc main.c -o runatcpu -lpthread
void* get_cpu_affinity( void* which )
{
    unsigned int which_cpu = *((char*)which);
    unsigned int i, j, cpu_all;
    cpu_set_t cpu_set;

    cpu_all = sysconf( _SC_NPROCESSORS_CONF );
    printf( "Notice: current system has %i CPU(s). ~ thread: %lu\n",
            cpu_all, pthread_self() );

    CPU_ZERO(&cpu_set);               // clear the cpu set.
    CPU_SET(which_cpu, &cpu_set);     // set the cpu
    // CPU_CLR(which_cpu, &cpu_set);  // or clear
    // int pthread_setaffinity_np(pthread_t thread, size_t cpusetlen, cpu_set_t *cpuset);
    if (-1 == pthread_setaffinity_np(pthread_self(), sizeof(cpu_set), &cpu_set))
        printf( "!!! Error: bind current thread to specified CPU failed !!! ~ thread: %lu\n",
                pthread_self() );
    /* OR ************
     * unsigned long mask = 7; // processors 0, 1, and 2
     * unsigned int len = sizeof(mask);
     * if (pthread_setaffinity(0, len, &mask) < 0)  perror("xx");
     */


    for ( j = 0; j < 10; j++ ) {
        CPU_ZERO(&cpu_set); // clear cpu set

        // int pthread_getaffinity_np(pthread_t thread, size_t cpusetlen, const cpu_set_t *cpuset);
        if (-1 == pthread_getaffinity_np(pthread_self(), sizeof(cpu_set), &cpu_set))
            printf( "!!! Error: get current thread was bound which CPU failed !!! ~ thread: %lu\n",
                    pthread_self() );

        for ( i = 0; i < cpu_all; i++ )
            if (CPU_ISSET(i, &cpu_set)) // test if the process on this cpu
                printf( "Current thread is running at %d CPU ~ thread: %lu\n",
                        i, pthread_self() );
        usleep(10000);
    }
    return NULL;
}

int main(int argc, char* argv[])
{
    unsigned int which_cpu = 0;
    pthread_t thread_id;

    if (2 != argc) {
        printf( "Usage:\n$ ./runatcpu cpu_number\n" );
        return -1;
    }
    which_cpu = atoi( argv[1] );  // which one

    if ( 0 != pthread_create( &thread_id, NULL, get_cpu_affinity, &which_cpu)) {
        printf( "!!! Error: create thread failed !!!\n" );
        return -2;
    }

    pthread_join( thread_id, NULL );  // NULL: don't get return value

    return 0;
}


