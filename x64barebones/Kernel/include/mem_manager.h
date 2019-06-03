#ifndef _MEM_MANAGER_H_
#define _MEM_MANAGER_H_

#include <stddef.h>
#include "../include/lib.h"
#include "graphics.h"

//#define PAGE_SIZE 4096 //4KB
#define PAGE_SIZE 1024
#define IS_POWER_OF_2(x) (!((x)&((x)-1)))
#define N_OF_LISTS 20 //20 listas alcanzaría como para 1Gb (creo)

//sistema basado en: https://silcnitc.github.io/run_data_structures/heap.html#nav-buddy-allocation

/*función para inicializar la memoria dado un puntero inicial y el tamaño
**total de la memoria*/
void initialize_list(void * start_ptr, size_t total_size);

/*función que llama a find_first_fit con el nodo raíz y 
**retorna el puntero del nodo adecuado*/
void * mem_alloc(size_t size);

//función que llama a liberar el nodo que tenga el puntero apuntando a ptr
void free_mem(void * ptr);

//devuelve un puntero al inicio de la memoria
void * memory_base();

void print_list();

//------------------------------------------------------------------------------------buddy system

/*Esta función se encarga de crear e inicializar la estructura
**de listas que va a utilizar el mem_manager. Se asume que total_size
es potencia de 2.*/
void create_free_lists(void * mem, size_t total_size);

/*función para calcular cuantas potencias de 2 hay entre
** el tamaño total y el tamaño de página (4KB)*/
int powers_in_between(size_t lower, size_t upper);

/*función que se encarga de asignar al array  de int * qué lugar
**de la memoria les corresponde*/
void load_free_lists(void * mem, int index, int n_of_lists);


/*Función que se encarga de iniciar la memoria con los valores correspondientes
**que sería, crear las divisiones que hicieron que podamos alocar a las listas
**en la memoria*/
void populate_free_list(int initial_value, int index, int steps);

/*función para retornar la próxima potencia de 2 que contiene a size*/
size_t fix_size(size_t size);

/*Función que busca en la lista de ídice i un espacio libre*/
size_t look_for_space_in_list(int index);

//Función para dividir un espacio de memoria en 2
int split_upper_level(size_t desired,int levels);

//Función que se encarga dividir recursivamente la memoria "para abajo"
void recursive_divide(int index_in_list, int levels);

void put_space_in_list(int index, size_t size);

size_t look_for_space_of_size(int index, size_t size);

int pages_used_by_heap();

void no_memory_error();



#endif
