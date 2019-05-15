#include <mutex.h>

void lock_mutex(void * lock){
    _mutex_lock((uint64_t)lock);
}

void unlock_mutex(void * lock){
    _mutex_unlock((uint64_t)lock);
}