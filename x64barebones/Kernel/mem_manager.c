//incluirlo manualmente para los tests
#include "./include/mem_manager.h"


static void * start_dir;


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
    size_t aux = 0;
    if(size >= PAGE_SIZE){
        //arreglar el tamaño (+ 1 int) si es igual a una página o no es potencia de 2
        if(size == PAGE_SIZE || !IS_POWER_OF_2(size+sizeof(int))){
            aux = fix_size(size+sizeof(int));
        }
    }else{
        aux = PAGE_SIZE;
    }
    //buscar en la lista de ese tamaño si hay un espacio libre
    //buscar a qué lista le corresponde
    index = powers_in_between(aux, max_partition_size);
    free_space_offset = look_for_space_in_list(index);
    if(free_space_offset != -1){ //encontramos un hueco
        *((char *) memory_base() + free_space_offset) = aux;
        return (void *) ((char *) memory_base() + free_space_offset + sizeof(int));
    }//no encontramos hueco
    if(split_upper_level(aux<<1, 0) == -1) return NULL; //no hay memoria disponible
    return mem_alloc(size); //se dividió, intentamos de nuevo el pedido
}

int split_upper_level(size_t desired, int levels){
    int index_in_list = powers_in_between(desired, max_partition_size);
    int desired_val = look_for_space_in_list(index_in_list);
    if(desired_val == -1){
        if(desired == max_partition_size) return -1;
        return split_upper_level(desired<<1, levels+1);
    }
    //encontramos un espacio de memoria que podemos dividir
    free_lists[index_in_list+1][0] = desired_val;
    free_lists[index_in_list+1][1] = desired_val + (desired_val>>1);
    recursive_divide(index_in_list+1, levels);
    return 0;
}

//no se debe llamar con el último nivel
void recursive_divide(int index_in_list, int levels){
    if(levels == 0) return;
    int aux = free_lists[index_in_list][0];
    free_lists[index_in_list+1][0] = aux;
    free_lists[index_in_list+1][1] = aux + (PAGE_SIZE<<(n_of_lists-index_in_list-2));
    free_lists[index_in_list][0] = 0;
    recursive_divide(index_in_list+1, levels-1);
}

int look_for_space_in_list(int index){
    int ret = 0;
    for(int i = 0; i < (1<<index); i++){
        if(free_lists[index][i] != 0){
            ret = free_lists[index][i];
            free_lists[index][i] = 0;
            return ret;
        }
    }
    return -1;
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
    n_of_lists = powers_in_between(PAGE_SIZE, total_size);
    //"alocar" la memoria inicializada
    memset(free_lists, 0, 20 * sizeof(int));
    load_free_lists(mem, 0, n_of_lists);
    populate_free_list(PAGE_SIZE << (n_of_lists-1), 0, n_of_lists);
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