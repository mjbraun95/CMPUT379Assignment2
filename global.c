#include "global.h"

int *buffer;
int buffer_index;
int buffer_tail;
int buffer_length;
sem_t empty;
sem_t full;
pthread_mutex_t buffer_mutex = PTHREAD_MUTEX_INITIALIZER;

pthread_mutex_t logfile_mutex = PTHREAD_MUTEX_INITIALIZER;
FILE* log_file;