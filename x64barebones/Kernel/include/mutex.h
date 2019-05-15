#ifndef _MUTEX_H_
#define _MUTEX_H_

#include "./process.h"
#include "./scheduler.h"

void lock_mutex(void * lock);
void unlock_mutex(void * lock);

extern void _mutex_lock(uint64_t lock);
extern void _mutex_unlock(uint64_t lock);

#endif