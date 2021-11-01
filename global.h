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
extern sem_t empty; // # of empty spaces in buffer
extern sem_t full; // # of occupied spaces in buffer
extern pthread_mutex_t buffer_mutex;

// Log file
extern FILE* log_file;
extern pthread_mutex_t logfile_mutex;

extern struct timespec start; // Starting time of program

struct thread_info {    
    pthread_t thread_id;        
    int thread_num;       
    int num_asks;
    int num_receives;      
    int num_completes;   
};

#endif