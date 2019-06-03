//incluirlo manualmente para los tests
#include "./include/mem_manager.h"
static void * start_dir;
size_t * free_lists[N_OF_LISTS]; //hasta 20 listas
int data_in_list[N_OF_LISTS];
size_t max_partition_size, total_mem_size;
int n_of_lists;

void initialize_list(void * start_ptr, size_t total_size){
    start_dir = start_ptr;
    total_mem_size = total_size;
    memset(data_in_list, 0, N_OF_LISTS * sizeof(int));
    if(total_mem_size <= (2 *PAGE_SIZE) || !IS_POWER_OF_2(total_mem_size)){
        total_mem_size = fix_size(total_mem_size);
    }
    create_free_lists(start_ptr, total_mem_size);
}

void * memory_base(){
    return start_dir;
}

void * mem_alloc(size_t size){
    int index = 0;
    size_t aux = 0,free_space_offset = 0;
    if(size >= PAGE_SIZE){
        //arreglar el tamaño (+ 1 int) si es igual a una página o no es potencia de 2
        if(size == PAGE_SIZE || !IS_POWER_OF_2(size+sizeof(size_t))){
            aux = fix_size(size+sizeof(size_t));
        }
    }else{
        aux = PAGE_SIZE;
    }
    //buscar en la lista de ese tamaño si hay un espacio libre
    //buscar a qué lista le corresponde
    index = powers_in_between(aux, max_partition_size);
    free_space_offset = look_for_space_in_list(index);
    if(free_space_offset != -1){ //encontramos un hueco
        *((size_t *) ((char *) memory_base() + free_space_offset)) = aux;
        return (void *) ((char *) memory_base() + free_space_offset + sizeof(size_t));
    }//no encontramos hueco
    if(split_upper_level(aux<<1, 0) == -1) return NULL; //no hay memoria disponible
    //if(split_upper_level(aux<<1, 0) == -1) no_memory_error(); //no hay memoria disponible
    return mem_alloc(size); //se dividió, intentamos de nuevo el pedido
}

int split_upper_level(size_t desired, int levels){
    int index_in_list = powers_in_between(desired, max_partition_size);
    if(index_in_list == -1) return -1;
    int desired_val = look_for_space_in_list(index_in_list);
    if(desired_val == -1){
        if(desired == max_partition_size) return -1;
        return split_upper_level(desired<<1, levels+1);
    }
    //encontramos un espacio de memoria que podemos dividir
    data_in_list[index_in_list+1] += 2;
    free_lists[index_in_list+1][0] = desired_val;
    free_lists[index_in_list+1][1] = desired_val + (desired_val>>1);
    recursive_divide(index_in_list+1, levels);
    return 0;
}

//no se debe llamar con el último nivel
void recursive_divide(int index_in_list, int levels){
    if(levels == 0) return;
    int aux = free_lists[index_in_list][0];
    data_in_list[index_in_list]--;
    put_space_in_list(index_in_list+1,aux);
    put_space_in_list(index_in_list+1, aux + (PAGE_SIZE<<(n_of_lists-index_in_list-2)));
    free_lists[index_in_list][0] = 0;
    recursive_divide(index_in_list+1, levels-1);
}

size_t look_for_space_in_list(int index){
    size_t ret = 0;
    if(data_in_list[index] <= 0) return -1;
    for(int i = 0; i < (1<<index); i++){
        if(free_lists[index][i] != 0){
            ret = free_lists[index][i];
            free_lists[index][i] = 0;
            data_in_list[index]--;
            return ret;
        }
    }
    return -1;
}

size_t look_for_space_of_size(int index, size_t size){ //ver de mergear con la función de arriba
    size_t ret = 0;
    if(data_in_list[index] <= 0) return -1;
    for(int i = 0; i < (1<<index); i++){
        if(free_lists[index][i] == size){
            ret = free_lists[index][i];
            free_lists[index][i] = 0;
            data_in_list[index]--;
            return ret;
        }
    }
    return -1;
}


void free_mem(void * ptr){
    if(ptr == NULL) return;
    size_t block_size = *((size_t *) ptr - 1), buddy_offset = 0;
    size_t block_offset = ((char *)((size_t *) ptr - 1)) - (char *) memory_base();
    int list_index = powers_in_between(block_size, max_partition_size);
    if(block_size == max_partition_size){
        put_space_in_list(0,max_partition_size);
        return;
    }
    if(IS_POWER_OF_2(block_offset)){
        buddy_offset = block_offset + block_size; //buddy a la derecha
    }else{
        buddy_offset = block_offset - block_size; //buddy a la izquierda
    }
    //busco en list_index espacio de offset block_size + block_size/2
    if(look_for_space_of_size(list_index, buddy_offset) == -1){
        //no encontramos el buddy, introducimos este valor en la lista
        put_space_in_list(list_index, block_offset);
        return;
    }
    //encontramos al buddy, a unirlo y buscar la memoria más grande
    if(IS_POWER_OF_2(block_offset)){
        //agrandamos el tamaño y volvemos a buscar
        *((size_t *)ptr - 1) = block_size<<1; 
        free_mem(ptr);
    }else{
        //agrandamos el tamaño del de la izq y volvemos a buscar
        *((size_t *) (((char *)memory_base() + buddy_offset))) = block_size<<1;
        free_mem((void *) ((char *)memory_base() + buddy_offset + sizeof(size_t)));
    }
}

void put_space_in_list(int index, size_t size){
    data_in_list[index]++;
    for(int i = 0; i < (1<<index); i++){
        if(free_lists[index][i] == 0){
            free_lists[index][i] = size;
            return;
        }
    }
}

void print_list(){
    /*int aux = max_partition_size, index = 0;
    while(aux < PAGE_SIZE){
        //printf(freelist[i][o])
    }*/
}


void create_free_lists(void * mem, size_t total_size){
    int heap_size = 0;
    n_of_lists = powers_in_between(PAGE_SIZE, total_size);
    //"alocar" la memoria inicializada
    memset(free_lists, 0, N_OF_LISTS * sizeof(size_t));
    load_free_lists(mem, 0, n_of_lists);
    heap_size = pages_used_by_heap();
    if(heap_size == -1){
        heap_size = 0;
    }
    populate_free_list(PAGE_SIZE << (n_of_lists-1), 0, n_of_lists - heap_size);
    max_partition_size = *free_lists[0];
}

int pages_used_by_heap(){
    size_t size = ((1<<(n_of_lists+1)) - 1) * sizeof(size_t);
    fix_size(size);
    return powers_in_between(PAGE_SIZE,size);
}

int powers_in_between(size_t lower, size_t upper){
    if(upper < lower) return -1;
    if(lower == upper) return 0;
    return 1 + powers_in_between(lower << 1, upper);
}

void load_free_lists(void * mem, int index, int n_of_lists){
    if(!n_of_lists) return;
    free_lists[index] = (size_t *) mem + (1<<index) - 1;
    load_free_lists(mem, index+1, n_of_lists-1);
}

void populate_free_list(int initial_value, int index, int steps){
    if(!steps) return;
    *free_lists[index] = initial_value;
    data_in_list[index]++;
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

void no_memory_error(){
  /*clear_screen();
  draw_err_string("No memory available");*/
}