#ifndef _SCHEDULER_H
#define _SCHEDULER_H

#include "./process.h"

void init_scheduler();
void run_process(process_t process);
void kill_current_process();
uint64_t switch_process(uint64_t stack_pointer);
void print_current_processes();
process_t get_current_process();

#endif

