#ifndef _IRQ_DISPATCHER_H_
#define _IRQ_DISPATCHER_H_

#include <keyboard.h>
#include <stdint.h>
#include <graphics.h>
#include <rtc.h>
#include <sound.h>
#include <time.h>
#include <stddef.h>
#include <scheduler.h>
#include <process.h>
#include <mutex.h>
#include <semaphore.h>
#include <ipc.h>

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

//si pongo #include <mem_manager.h> se rompe
void * mem_alloc(size_t size);
void free_mem(void * ptr);
void * return_memory_base();

int read(int param1, char * param2, int param3);
void write(int param1, char * param2, int param3);
void color_write(char * pointer, int size, int foreground_color, int background_color);
size_t new_process(uint64_t process_start, char * process_name, int foreground, int priority);

#endif
