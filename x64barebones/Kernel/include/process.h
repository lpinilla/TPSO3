#ifndef _PROCESS_H
#define _PROCESS_H

#include <stdlib.h>
#include <stdint.h>
#include "./lib.h"

#define STACK_SIZE 4096

#define MAX_PROCESS_NAME 256
#define MAX_PROCESSES 256
#define MAX_FD 50

typedef enum {P_READY, P_RUNNING, P_WAITING, P_TERMINATE} pstate_t;
typedef enum {STDIN=0, STDOUT, STDERR, R_ONLY, W_ONLY} fd_t;

typedef struct fd_infoADT * fd_info_t;
typedef struct processADT * process_t;

void init_processes();
process_t create_process(uint64_t process_start, char * name, int priority);
process_t create_process_args(uint64_t process_start, char * process_name, int argc, void ** argv, int priority);
void delete_process(process_t process);
void set_state(process_t process, pstate_t state);
void set_state_id(size_t pid, pstate_t state);
pstate_t get_state(process_t process);
void set_stack_pointer(process_t process, uint64_t stack_pointer);
void print_process(void * p);
size_t get_pid(process_t process);
uint64_t get_stack_pointer(process_t process);
pstate_t get_state_id(size_t pid);
void set_foreground_process(size_t pid);
int is_current_process_foreground();
void set_current_process_terminate();
int get_priority(process_t process);
int set_priority(int pdi, int priority);
// search for path and create fd with type, if file doesnt exist return -1
int open_fd(char * path, fd_t type);
// close the fd, if exist return 0, if error return 1
int close_fd(int fd_pos);
// writes in the fd of current process
void write_fd(int fd, const char * buff, int q);
// writes q chars in buff from the fd
void read_fd(int fd, char * buff, int q);
#endif