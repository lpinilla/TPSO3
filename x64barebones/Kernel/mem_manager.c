//incluirlo manualmente para los tests
#include "./include/mem_manager.h"


static void * start_dir;
static size_t total_mem_size;

void initialize_list(void * start_ptr, size_t total_size){
    start_dir = start_ptr;
    total_mem_size = total_size;
    if(total_mem_size <= (2 *PAGE_SIZE) || !IS_POWER_OF_2(total_mem_size)){
        total_mem_size = fix_size(total_mem_size);
    }
    create_free_lists(start_ptr, total_mem_size);
}

void * memory_base(){
    return start_dir;
}

void * mem_alloc(size_t size){
    int index = 0, free_space_offset = 0;
    if(size >= PAGE_SIZE){
        //arreglar el tamaño (+ 1 int) si es igual a una página o no es potencia de 2
        if(size == PAGE_SIZE || !IS_POWER_OF_2(size+sizeof(int))){
            size = fix_size(size+sizeof(int));
        }
    }else{
        size = PAGE_SIZE;
    }
    //buscar en la lista de ese tamaño si hay un espacio libre
    //buscar a qué lista le corresponde
    index = powers_in_between(size, max_partition_size);
    free_space_offset = look_for_space_in_list(index);
    if(free_space_offset){ //encontramos un hueco
        *((char *) memory_base() + free_space_offset) = size;
        return (void *) ((char *) memory_base() + free_space_offset + sizeof(int));
    }else{ //no encontramos, tenemos que partir un bloque más grande
        
    }
    return start_dir; //para que compile
}

int look_for_space_in_list(int index){
    int ret = 0;
    for(int i = 0; i < (1<<index); i++){
        if(free_lists[index][i] != 0){
            ret = free_lists[index][i];
            free_lists[index][i] = 0;
            break;
        }
    }
    return ret;
}


void free_mem(void * ptr){
   
}

void print_list(){
    /*int aux = max_partition_size, index = 0;
    while(aux < PAGE_SIZE){
        //printf(freelist[i][o])
    }*/
}


void create_free_lists(void * mem, size_t total_size){
    int n_of_lists = powers_in_between(PAGE_SIZE, total_size);
    //int lists_size = n_of_lists * sizeof(int); //es potencia de 2
    //"alocar" la memoria inicializada
    memset(free_lists, 0, 20 * sizeof(int));
    load_free_lists(mem, 0, n_of_lists);
    populate_free_list(PAGE_SIZE << n_of_lists, 0, n_of_lists);
    max_partition_size = *free_lists[0];
}

int powers_in_between(size_t lower, size_t upper){
    if(upper < lower) return -1;
    if(lower == upper) return 0;
    return 1 + powers_in_between(lower << 1, upper);
}

void load_free_lists(void * mem, int index, int n_of_lists){
    if(!n_of_lists) return;
    free_lists[index] = (int *) mem + (1<<index) - 1;
    load_free_lists(mem, index+1, n_of_lists-1);
}

void populate_free_list(int initial_value, int index, int steps){
    if(!steps) return;
    *free_lists[index] = initial_value;
    for(int i = 1; i < (1<<index); i++){
        free_lists[index][i] = 0;
    }
    populate_free_list(initial_value >> 1, index+1, steps-1);
}

size_t fix_size(size_t size){
    size |= size >> 1;
    size |= size >> 2;
    size |= size >> 4;
    size |= size >> 8;
    size |= size >> 16;
    return size+1;
}