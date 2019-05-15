#ifndef _SHELL_H_
#define _SHELL_H_

/*
PARA AGREGAR UN COMANDO HAY QUE AGREGARLO EN EL DEFINE EN ORDEN, DESPUES EN EL VECTOR DE FUNCIONES EN EL MISMO NUMERO DEL
DEFINE Y DESPUES EN EL VECTOR DE STRINGS ENE EL NUMERO DEL DEFINE -1 (podriamos cambiar esto para que sea mas consistente)
*/
#include <utilities.h>
#include <string.h>
#include <syscall.h>
#include <time.h>
#include <syscall.h>
#include <pong.h>
#include <openlg.h>
#include <time.h>
#include <mem_manager.h>
#include <processes_test.h>
#include <mutex_test.h>
#include <semaphore_test.h>
#include <mem_manager_test.h>
#include <ipc_test.h>
#include <prodcons.h>

#define RETURN_ADRESS 0xDEADC0DE

#define INVALID_COMMAND 0
#define PONG_COMMAND 1
#define TIME_COMMAND 2
#define SHUTDOWN_COMMAND 3
#define BEEP_COMMAND 4
#define MAKE_DIV 5
#define AYUDA 6
#define SCAN_F 7
#define PRINT_F 8
#define INVALID 9

#define COMMANDS 16

#define MAX_LENGTH 20

typedef void (*func)();

void try_scan_f();
void invalid_command();
void play_pong();
void show_time();
void shutdown();
void print_user();
void make_beep();
void make_div();
void make_div_process();
void ayuda();
void try_invalid_function();
void try_invalid_function_process();
void try_print_f();
void try_processes();
void try_mutex();
void try_semaphore();
void try_alloc();
void try_ipc();
void run_prodcons();
void ps();
uint64_t * shell();


#endif
