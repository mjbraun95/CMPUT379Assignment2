#include "buffer.h"
#include "global.h"
#include <time.h>

// Circular queue + time function for logfile

int pop() {
    int value = buffer[buffer_index];
    buffer[buffer_index] = 0;
    buffer_index = buffer_index + 1;
    if (buffer_length == buffer_index) {
        buffer_index = 0;
    }
    return value;
}

void push(int value) {
    buffer[buffer_tail] = value;
    buffer_tail = buffer_tail + 1;
    if (buffer_length == buffer_tail) {
        buffer_tail = 0;
    }
}

// Reference: https://cboard.cprogramming.com/c-programming/171428-measuring-time-function-execution-milliseconds-linux-environment.html
double get_current_time() {
    struct timespec ts1, ts2, ts3;
    ts1 = start; //start is global
    clock_gettime(CLOCK_REALTIME, &ts2);
    if (ts2.tv_nsec < ts1.tv_nsec) {
        ts2.tv_nsec += 1000000000;
        ts2.tv_sec--;
    }
    ts3.tv_nsec = ts2.tv_nsec-ts1.tv_nsec;
    ts3.tv_sec = ts2.tv_sec-ts1.tv_sec;
    double t = (double)ts3.tv_sec;
    double decimal = (double)ts3.tv_nsec;
    decimal = decimal/(1000000000);
    t = t+decimal;
    return t;
}