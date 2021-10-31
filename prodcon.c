#include "consumer.h"
#include "global.h"
#include "buffer.h"
#include "producer.h"
#include "tands.h"

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


// Buffer variables
int *buffer;
int buffer_index, buffer_tail = 0;
int buffer_length;
pthread_mutex_t buffer_mutex = PTHREAD_MUTEX_INITIALIZER;
sem_t empty, full;

// Logfile variables
pthread_mutex_t logfile_mutex = PTHREAD_MUTEX_INITIALIZER;
FILE* log_file;

struct timespec start;

int total_sleeps, total_works, total_asks, total_receives, total_completes = 0;


int main(int argc, char** argv[]) {
    clock_gettime(CLOCK_REALTIME, &start);
    printf("argc: %i\n", argc); //debug

    // Read args to get logfile name + number of threads
    char log_file_name[15] = "prodcon.";
    if(argc = 2) {
        strcat(log_file_name, argv[2]);
    }
    else {
        strcat(log_file_name, "0");
    }
    strcat(log_file_name, ".log");
    int num_threads = atoi(argv[1]);

    // Open logfile to write
    log_file = fopen(log_file_name, "w");

    // Allocate memory for circular queue of size 2*(# of consumers)
    buffer_length = num_threads*2;
    // Create buffer
    buffer = malloc(buffer_length*sizeof(*buffer));
    sem_init(&full, 0, 0);
    sem_init(&empty, 0, buffer_length);

    // Allocate memory for thread pool
    struct thread_info *tinfo;
    tinfo = calloc(num_threads, sizeof(struct thread_info));
    // Create thread pool, run consumers
    int pthread;
    int i;
    for (i=0; i<num_threads; i++) {
        tinfo[i].thread_num = i + 1;
        tinfo[i].num_asks = 0;
        tinfo[i].num_receives = 0;
        tinfo[i].num_completes = 0;
        pthread = pthread_create(&tinfo[i].thread_id, NULL, consume, &tinfo[i]);
        if (pthread != 0) {
            perror("Error creating thread pool");
        }
    }

    // Run producer
    produce(&total_sleeps, &total_works);
    for (i=0; i<(num_threads*2); i++) {
        sem_wait(&empty);
        pthread_mutex_lock(&buffer_mutex);
        //EDIT
        // Kill thread
        push(-1);
        pthread_mutex_unlock(&buffer_mutex);
        sem_post(&full);
    }

    //EDIT
    int join;
    for (i=0; i<num_threads; i++) {
        //printf("joining thread %d\n",tinfo[i].thread_num);
        join = pthread_join(tinfo[i].thread_id ,NULL);
        if (join != 0) {
            perror("Error");
        }
    }

    // Sum the thread pool data
    for (i=0; i<num_threads; i++) {
        total_asks += tinfo[i].num_asks;
        total_receives += tinfo[i].num_receives;
        total_completes += tinfo[i].num_completes;  
    }
    //Log summary data
    fprintf(log_file,"Summary:\n");
    fprintf(log_file,"    Work           %d\n",total_works);
    fprintf(log_file,"    Ask            %d\n",total_asks);
    fprintf(log_file,"    Receive        %d\n",total_receives);
    fprintf(log_file,"    Complete       %d\n",total_completes);
    fprintf(log_file,"    Sleep          %d\n",total_sleeps);
    for (i=0; i<num_threads; i++) {
        fprintf(log_file,
        "    Thread  %d      %d\n",
        tinfo[i].thread_num, tinfo[i].num_completes);
    }
    fclose(log_file);
    return 0;
}