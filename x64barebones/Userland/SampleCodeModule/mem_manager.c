#include "./include/mem_manager.h"
#include "./include/syscall.h"


void * my_malloc(int size){
    if(size<0){
        return NULL;
    }
    return (void *) sys_my_malloc(size);
}

void my_free(void* ptr){
    sys_my_free(ptr);
}

void * start_of_memory(){
   return  sys_start_of_mem();
}