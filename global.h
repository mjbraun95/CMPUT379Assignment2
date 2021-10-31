#ifndef __INCLUDE_GLOBAL_H__
#define __INCLUDE_GLOBAL_H__

#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <time.h>

// Circular queue
extern int *buffer;
extern int buffer_index;
extern int buffer_tail;
extern int buffer_length;
extern sem_t empty; // counts how many empty spaces in buffer
extern sem_t full; // counts filled spaces in buffer
extern pthread_mutex_t buffer_mutex;

// extern int total_sleeps;
// extern int total_works;

// Log file
extern FILE* log_file;
extern pthread_mutex_t logfile_mutex;

extern struct timespec start; // when program starts in ns since epoch

struct thread_info {    /* Used as argument to thread_start() */
    pthread_t thread_id;        /* ID returned by pthread_create() */
    int thread_num;       /* Application-defined thread # */
    int num_asks;
    int num_receives;      // assigned tasks
    int num_completes;   // completed tasks
};

#endif //__INCLUDE_GLOBALVARIABLES_H__