#ifndef __INCLUDE__PRODUCER_H__
#define __INCLUDE_PRODUCER_H__

void log_work(int task);
void log_sleep(int task);
void produce(int* total_sleeps, int* total_works);

#endif