#ifndef DINING_PHILOSOPHERS
#define DINING_PHILOSOPHERS


#define MAXPHILO 20
#define THINKING 2 
#define HUNGRY 1 
#define EATING 0

#include <stdint.h>
#include "./syscall.h"
#include "./utilities.h"

typedef struct arguments{
	int ph_id;
}arguments;

typedef struct arguments* argumentsPointer;


void create_philosopher();
void delete_philosopher();
void test(int ph_id);
void take_fork(int ph_id);
void put_fork(int ph_id);
void philosopher(int argc,argumentsPointer arg);
void print_ph_state();
void philosophers();
int left();
int right();

#endif