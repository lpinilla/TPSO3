#ifndef _SYSCALL_H_
#define _SYSCALL_H_

#include <stdint.h>
#include "./call_int_80.h"
#include "./utilities.h"

typedef enum {P_READY, P_RUNNING, P_WAITING, P_TERMINATE} pstate_t;
typedef enum {BACKGROUND, FOREGROUND} pground_t;
typedef enum {PRIORITY_0=0, PRIORITY_1, PRIORITY_2} ppriority_t;
typedef enum {STDIN=0, STDOUT, STDERR, R_ONLY, W_ONLY} fd_t;

void sys_write(char * string, int size);
char sys_read(char * string, int size);
void sys_clear_console();
void sys_draw_pixel(int x, int y, int r, int g, int b);
void sys_shadow_pixel(int x, int y, int r, int g, int b);
void sys_swap_buffers(void);
void sys_clear_shadow_buffer();
void sys_color_write(char * string, int size, int foreground_color, int background_color);
void sys_reset_cursor(void);
void sys_beep(void);
void sys_sleep(int ticks);
void sys_new_line(void);
int sys_time(int selector);
void * sys_my_malloc(int size);
void sys_my_free(void* ptr);
void * sys_start_of_mem();
int sys_create_process(void * function, char * name, pground_t process_ground);
void sys_kill_process(int pid);
void sys_print_all_procceses();
pstate_t sys_get_process_state(int pid);
int sys_sem_open(char * name);
int sys_sem_close(int id);
int sys_sem_post(int id);
int sys_sem_wait(int id);
void sys_lock(void * lock);
void sys_unlock(void * lock);
void sys_set_foreground_process(int pid);
int sys_is_current_process_foreground();
void sys_print_mem_list();
void sys_ipc_read(int id, char * msg_ret);
void sys_ipc_write(char * msg, int id);
int sys_create_priority_process(void * function, char * name, pground_t process_ground, ppriority_t priority);
int sys_open_fd(char * path, fd_t type);
int sys_close_fd(int fd);
int sys_create_n_pipe(char * path);
int sys_delete_file(char * path);
void sys_read_fd(int fd, char * buff, int q);
void sys_write_fd(int fd, char * buff, int q);
int sys_create_args_process(void * function, char * name, pground_t process_ground, int argc, void ** argv);

#endif