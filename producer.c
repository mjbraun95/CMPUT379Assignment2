#include "getcurrenttime.h"
#include "globalvariables.h"
#include "myqueue.h"
#include "producer.h"
#include "tands.h"

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long unsigned int input_size = 10;

void log_work(int task) {
    double t = get_current_time();
    // Make sure log file doesn't get garbled
    pthread_mutex_lock(&logfile_mutex);

    fprintf(log_file, 
    "   %2.3f ID= %1d Q= %1d%8s    %4d\n", 
    t, 0, buffer_index, "Work", task);

    pthread_mutex_unlock(&logfile_mutex);
}

void log_sleep(int sleep) {
    double t = get_current_time();
    // Make sure log file doesn't get garbled
    pthread_mutex_lock(&logfile_mutex);
    
    fprintf(log_file, 
    "   %2.3f ID= %1d      %8s   %4d\n", 
    t, 0, "Sleep", sleep);

    pthread_mutex_unlock(&logfile_mutex);
}

void produce(int* total_sleeps, int* total_works) {
    int exit = 0;
    int num_sleeps = 0;
    int num_works = 0;
    while (1) {
        char input;
        input = getchar();
        printf("input: %c\n",input); //debug
        // Exit at end of input file
        if (input == EOF) {
            break;
        }
        else if(input == 'S') {
            char* number;
            getline(&number, &input_size, stdin);
            printf("S number: %s\n", number); //debug
            int num = atoi(number);
            log_sleep(num);
            Sleep(num);
            num_sleeps++;
        }
        else if(input =='T') {
            char* number;
            getline(&number, &input_size, stdin);
            printf("T number: %s\n", number); //debug
            int num = atoi(number);
            
            sem_wait(&empty);
            pthread_mutex_lock(&buffer_mutex);
            push(num);
            pthread_mutex_unlock(&buffer_mutex);

            sem_post(&full);
            log_work(num);
            num_works++;
        }
        // Exit at invalid input
        else {
            printf("Invalid input!\n");
            break;
        }
    }
    (*total_sleeps) = num_sleeps;
    (*total_works) = num_works;
    // printf("total_sleeps updated to %i\n", total_sleeps);
    // printf("total_works updated to %i\n", total_works);
}