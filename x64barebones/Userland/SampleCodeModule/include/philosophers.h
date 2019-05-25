#ifndef DINING_PHILOSOPHERS
#define DINING_PHILOSOPHERS


#define MAXPHILO 20
#define THINKING 2 
#define HUNGRY 1 
#define EATING 0

#include <stdint.h>
#include "./syscall.h"
#include "./utilities.h"

void createPhilosopher();
void deletePhilosopher();
void test(int ph_id);
void take_fork(int ph_id);
void put_fork(int ph_id);
void philosopher(void* id);
void print_ph_state();


#endif