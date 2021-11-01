#include "consumer.h"
#include "global.h"
#include "buffer.h"
#include "tands.h"

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>
#include <time.h>

void log_ask(int threadnum) {
    double t = get_current_time();
    // Make sure log file doesn't get garbled
    pthread_mutex_lock(&logfile_mutex);

    fprintf(log_file, 
    "   %2.3f ID= %1d    %8s\n", 
    t, threadnum, "Ask");

    pthread_mutex_unlock(&logfile_mutex);
}

void log_receive(int threadnum, int task) {
    double t = get_current_time();
    // Make sure log file doesn't get garbled
    pthread_mutex_lock(&logfile_mutex);

    fprintf(log_file, 
    "   %2.3f ID= %1d Q= %1d   %8s %4d\n", 
    t, threadnum, buffer_index, "Receive", task);

    pthread_mutex_unlock(&logfile_mutex);
}

void log_complete(int threadnum, int task) {
    double t = get_current_time();
    // Make sure log file doesn't get garbled
    pthread_mutex_lock(&logfile_mutex);

    fprintf(log_file, 
    "   %2.3f ID= %1d         %8s %3d\n", 
    t, threadnum, "Complete", task);

    pthread_mutex_unlock(&logfile_mutex);
}

// Void pointer to use in pthread_create() function
void* consume(void* argsp) {
    struct thread_info *tinfo = argsp;
    int task;

    while(1) {     
        (tinfo->num_asks)++;
        log_ask(tinfo->thread_num);
        sem_wait(&full);
        pthread_mutex_lock(&buffer_mutex);
        task = pop();
        pthread_mutex_unlock(&buffer_mutex);
        sem_post(&empty);
        if(task == -1) {
            break;
        }
        // Thread takes task
        tinfo->num_receives++;
        log_receive(tinfo->thread_num,task);
        Trans(task);
        log_complete(tinfo->thread_num,task);
        tinfo->num_completes++;
    }
    return (void *) 0;
}