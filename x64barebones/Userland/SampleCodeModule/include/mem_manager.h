#ifndef _MEM_MANAGER_H
#define _MEM_MANAGER_H

#include <syscall.h>
#include <stdio.h>

//aloca un bloque de memoria size
void* my_malloc(int size);

//libera un bloque de memoria de un proceso
void my_free(void* ptr);

//devuelve un puntero al inicio de la memoria
void * start_of_memory();


#endif