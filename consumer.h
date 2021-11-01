#ifndef __INCLUDE_CONSUMER_H__
#define __INCLUDE_CONSUMER_H__

void log_ask(int threadnum);
void log_receive(int threadnum, int task);
void log_complete(int threadnum, int task);
void* consume(void* argsp);

#endif