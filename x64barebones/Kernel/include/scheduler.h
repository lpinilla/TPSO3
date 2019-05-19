#ifndef _SCHEDULER_H
#define _SCHEDULER_H

#include <process.h>
#include <mem_manager.h>
#include <graphics.h>
#include <interrupts.h>
#include <queue.h>
#include <time.h>

#define HIGH 0
#define MEDIUM 1
#define LOW 2

#define PRIORITIES 3

#define FALSE 0
#define TRUE 1


void init_scheduler();
void run_process(process_t process);
uint64_t switch_process(uint64_t stack_pointer);
void print_current_processes();
process_t get_current_process();
int set_current_process_priority(int priority);

#endif

