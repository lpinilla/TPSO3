#ifndef _PROCESS_H
#define _PROCESS_H

#include <stdlib.h>
#include <stdint.h>
#include "./lib.h"

#define STACK_SIZE 4096

#define MAX_PROCESS_NAME 256
#define MAX_PROCESSES 256

typedef enum {P_READY, P_RUNNING, P_WAITING, P_TERMINATE} pstate_t;

typedef struct processADT * process_t;

void init_processes();
process_t create_process(uint64_t process_start, char * name, int priority);
void delete_process(process_t process);
void set_state(process_t process, pstate_t state);
void set_state_id(size_t pid, pstate_t state);
pstate_t get_state(process_t process);
void set_stack_pointer(process_t process, uint64_t stack_pointer);
void print_process(process_t process);
size_t get_pid(process_t process);
uint64_t get_stack_pointer(process_t process);
pstate_t get_state_id(size_t pid);
void set_foreground_process(size_t pid);
int is_current_process_foreground();
void set_current_process_terminate();
int get_priority(process_t process);

#endif