#include "include/syscall.h"

#define READ 3
#define WRITE 4
#define DRAW_PIXEL 5
#define X_RES 6
#define Y_RES 7
#define CLEAR_SCREEN 8
#define SHADOW_PIXEL 9
#define MOVE_EVERYTHING_UP 10
#define SWAP_BUFFERS 11
#define CLEAR_SHADOW_BUFFER 12
#define TIME 13
#define INIT_GRAPHICS 14
#define COLOR_WRITE 15
#define RESET_CURSOR 16
#define BEEP 17
#define SLEEP 18
#define NEW_LINE 19
#define MY_MALLOC 20
#define MY_FREE 21
#define MEM_BASE 22
#define NEW_PROCESS 23
#define KILL_PROCESS 24
#define LIST_PROCESSES 25
#define GET_STATE_PROCESS 26
#define SEM_OPEN 27
#define SEM_CLOSE 28
#define SEM_POST 29
#define SEM_WAIT 30
#define MUTEX_LOCK 31
#define MUTEX_UNLOCK 32
#define SET_FOREGROUND_PROCESS 33
#define IS_CURRENT_PROCESS_FOREGROUND 34
#define PRINT_MEM_LIST 35
#define IPC_READ 36
#define IPC_WRITE 37
#define NEW_PROCESS_PRIORITY 38

void sys_write(char * string, int size){
  _call_int_80( (uint64_t) WRITE, 1, (uint64_t) string, (uint64_t)size, 0, 0);
}

char sys_read(char * string, int size){
	char ret = (char) _call_int_80(READ, 1, (uint64_t) string, size, 0, 0);
  return ret;
}

void sys_clear_console(){
	_call_int_80(CLEAR_SCREEN, 0,0,0,0,0);
}

void sys_draw_pixel(int x, int y, int r, int g, int b){
	_call_int_80((uint64_t)DRAW_PIXEL, (uint64_t)x,(uint64_t) y,(uint64_t) r,(uint64_t) g,(uint64_t) b);
}

void sys_shadow_pixel(int x, int y, int r, int g, int b){
	_call_int_80((uint64_t) SHADOW_PIXEL, (uint64_t)x,(uint64_t) y,(uint64_t) r,(uint64_t) g,(uint64_t) b);
}
int sys_time(int selector){
	int ret = _call_int_80((uint64_t) TIME,(uint64_t) selector, 0,0,0,0);
  return ret;
}

void sys_swap_buffers(){
	_call_int_80((uint64_t) SWAP_BUFFERS, 0, 0, 0, 0, 0);
}

void sys_clear_shadow_buffer(){
	_call_int_80((uint64_t) CLEAR_SHADOW_BUFFER, 0, 0, 0, 0, 0);
}

void sys_color_write(char * string, int size, int foreground_color, int background_color){
	_call_int_80((uint64_t) COLOR_WRITE,(uint64_t) string,(uint64_t) size,(uint64_t) foreground_color,(uint64_t) background_color, 0);
}

void sys_reset_cursor(){
	_call_int_80((uint64_t) RESET_CURSOR, 0, 0, 0, 0, 0);
}


void sys_new_line(){
	_call_int_80((uint64_t) NEW_LINE, 0, 0, 0, 0, 0);
}

void sys_sleep(int ticks){
  _call_int_80((uint64_t) SLEEP,(uint64_t) ticks,0,0,0,0);
}

void sys_beep(){
  _call_int_80(BEEP,0,0,0,0,0);
}

void* sys_my_malloc(int size){
	void * ret = (void*) _call_int_80(MY_MALLOC,(uint64_t) size,0,0,0,0);
	return ret;
}

void sys_my_free(void* ptr){	
	_call_int_80(MY_FREE,(uint64_t) ptr,0,0,0,0);
}

void * sys_start_of_mem(){
	return (void *) _call_int_80(MEM_BASE, 0, 0,0,0,0);
}

int sys_create_process(void * function, char * name, pground_t process_ground){
	return (int)_call_int_80(NEW_PROCESS, (uint64_t)function, (uint64_t) name, (uint64_t)process_ground, 0, 0);
}

void sys_kill_process(int pid){
	_call_int_80(KILL_PROCESS, (uint64_t)pid, 0, 0, 0, 0);
}

void sys_print_all_procceses(){
	_call_int_80(LIST_PROCESSES, 0, 0, 0, 0, 0);
}

pstate_t sys_get_process_state(int pid){
	return (pstate_t)_call_int_80(GET_STATE_PROCESS, (uint64_t)pid, 0, 0, 0, 0);
}

int sys_sem_open(char * name){
	return (int)_call_int_80(SEM_OPEN, (uint64_t)name, 0, 0, 0, 0);
}

int sys_sem_close(int id){
	return (int)_call_int_80(SEM_CLOSE, (uint64_t)id, 0, 0, 0, 0);
}

int sys_sem_post(int id){
	return (int)_call_int_80(SEM_POST, (uint64_t)id, 0, 0, 0, 0);
}

int sys_sem_wait(int id){
	return (int)_call_int_80(SEM_WAIT, (uint64_t)id, 0, 0, 0, 0);
}

void sys_lock(void * lock){
	_call_int_80(MUTEX_LOCK, (uint64_t)lock, 0, 0, 0, 0);
}

void sys_unlock(void * lock){
	_call_int_80(MUTEX_UNLOCK, (uint64_t)lock, 0, 0, 0, 0);
}

void sys_set_foreground_process(int pid){
	_call_int_80(SET_FOREGROUND_PROCESS, (uint64_t)pid, 0, 0, 0, 0);
}

int sys_is_current_process_foreground(){
	return (int)_call_int_80(IS_CURRENT_PROCESS_FOREGROUND, 0, 0, 0, 0, 0);
}

void sys_print_mem_list(){
	_call_int_80(PRINT_MEM_LIST, 0, 0, 0, 0, 0);
}

void sys_ipc_read(int id, char * msg_ret){
	_call_int_80(IPC_READ, (uint64_t)id, (uint64_t)msg_ret, 0, 0, 0);
}

void sys_ipc_write(char * msg, int id){
	_call_int_80(IPC_WRITE, (uint64_t)msg, (uint64_t)id, 0, 0, 0);
}

int sys_create_priority_process(void * function, char * name, pground_t process_ground, ppriority_t priority){
	return (int)_call_int_80(NEW_PROCESS, (uint64_t)function, (uint64_t) name, (uint64_t)process_ground, (uint64_t)priority, 0);
}