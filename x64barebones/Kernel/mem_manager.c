//incluirlo manualmente para los tests
#include "./include/mem_manager.h"

#define PAGE_SIZE 0x1000000000000 //4KB


/*función que implementa first fit en la lista de alocación,
**si el espacio que encuentra es más grande que el pedido y hay espacio
**para crear un nuevo nodo, crea un nuevo nodo que apunta a la nueva zona
**de memoria liberada y lo agrega a la lista*/
static Node find_first_fit(Node curr, size_t size);

//función para liberar un nodo de la lista (de ser necesario, elimilandolo) 
static Node free_node(Node curr, void * mem_ptr);

static void print_r_list(Node curr);

static void * start_dir;
static Node root;
static size_t total_mem_size;

int * free_lists[20];

int powers_in_between(size_t total_size);
void load_free_lists(void * mem, int index, int n_of_lists);
void populate_free_list(size_t initial_value, int index, int steps);


static Node find_first_fit(Node curr, size_t size){
    if(curr == NULL || size == 0){
        return NULL;
    }
    if(curr->status == F && curr->size == size){
        curr->status = P;
        return curr;
    }
    if(curr->status == F && (curr->size > size)){
        curr->status = P;
        size_t dif = curr->size - size;
        //si el espacio que sobra es suficiente, aloca un nuevo nodo
        if(dif > sizeof(struct t_Node)){
            Node aux = (Node)((char *) curr->mem_ptr + size);

            aux->next = curr->next;
            aux->prev = curr;
            aux->mem_ptr = (void *) ((char *) curr->mem_ptr + size + sizeof(struct t_Node));
            aux->size = dif - sizeof(struct t_Node);
            aux->status = F;

            curr->size = size;
            curr->next = aux;        
        }
        return curr;
    }
    return find_first_fit(curr->next, size);
}

static Node free_node(Node curr, void * mem_ptr){
    if(curr == NULL || mem_ptr == NULL){
        return NULL; //tal vez separar caso de error
    }
    if(curr->mem_ptr == mem_ptr){ //encontramos el puntero a liberar
        //4 casos de liberación y merge, ver libro de Tanenbaum 4ta edición
        if((curr->prev == NULL || curr->prev->status == P) && (curr->next == NULL || curr->next->status == P)){
            //caso ambos ocupados
            curr->status = F;
            return curr;
        }else if((curr->prev != NULL && curr->prev->status != P) && (curr->next == NULL || curr->next->status == P)){
            //caso libre izq -> se agranda izq
            curr->prev->size += curr->size + sizeof(struct t_Node);
            if(curr->next != NULL) curr->next->prev = curr->prev;
            return curr->next;
        }else if((curr->prev == NULL || curr->prev->status == P)  && (curr->next != NULL && curr->next->status != P)){
            //caso libre der -> me agrando yo
            curr->status = F;
            curr->size += curr->next->size + sizeof(struct t_Node);
            if(curr->next->next != NULL) curr->next->next->prev = curr;
            curr->next = curr->next->next;            
            return curr;
        }else if((curr->prev != NULL && curr->prev->status != P)  && (curr->next != NULL && curr->next->status != P)){
            //caso libre de ambos lados -> se agranda la izq el tamaño mío más el de la derecha
            curr->prev->size += curr->size + curr->next->size + 2 * sizeof(struct t_Node);
            if(curr->next->next != NULL){
                curr->next->next->prev = curr->prev;
                return curr->next->next;
            }
            return NULL;
        }
    }
    curr->next = free_node(curr->next, mem_ptr);
    return curr;
}

/*
void initialize_list(void * start_ptr, size_t total_size){
    total_mem_size = total_size;
    root = start_dir = start_ptr;

    root->next = NULL;
    root->prev = NULL;
    root->mem_ptr =  (void *) ((char *)start_ptr + sizeof(struct t_Node));
    root->size = total_size - sizeof(struct t_Node);
    root->status = F;
}*/

void initialize_list(void * start_ptr, size_t total_size){
    total_mem_size = total_size;
    start_dir = start_ptr;
    //inicializar las listas iniciales
    //todo
}

void * return_memory_base(){
    return start_dir;
}

void * mem_alloc(size_t size){
    Node ret = find_first_fit(root, size);
    if(ret == NULL){
        return NULL;
    }
    return ret->mem_ptr;
}

void free_mem(void * ptr){
    root = free_node(root, ptr);
    if(root == NULL){
        //draw_string("Error al liberar memoria.\n");
    }
}

void print_list(){
    print_r_list(root);
}

static void print_r_list(Node curr){
    // if(curr == NULL){
    //     return;
    // }
    // draw_string("mem_ptr:");
    // draw_number((uint64_t)curr->mem_ptr);
    // draw_string(" status");
    // draw_number(curr->status);
    // draw_string(" size");
    // draw_number(curr->size);
    // draw_string("\n");
    // print_r_list(curr->next);
}


/*Esta función se encarga de crear e inicializar la estructura
**de listas que va a utilizar el mem_manager. Se asume que total_size
es potencia de 2.*/
void create_free_lists(void * mem, size_t total_size){
    int n_of_lists = powers_in_between(total_size);
    int lists_size = n_of_lists * sizeof(int); //es potencia de 2
    //"alocar" la memoria inicializada
    memset(free_lists, 0, 20 * sizeof(int));
    load_free_lists(mem, 0, n_of_lists);
    populate_free_list(PAGE_SIZE << n_of_lists, 0, n_of_lists - (lists_size / PAGE_SIZE));
}

/*función para calcular cuantas potencias de 2 hay entre
** el tamaño total y el tamaño de página (4KB)*/
int powers_in_between(size_t total_size){
    if(total_size == PAGE_SIZE) return 0;
    return 1 + powers_in_between(total_size >> 1);
}

void load_free_lists(void * mem, int index, int n_of_lists){
    if(!n_of_lists) return;
    free_lists[index] = (int *) mem;
    if(!index){
        load_free_lists( (void *) ((char *) mem + sizeof(void *)), index+1, n_of_lists-1);
        return;
    }
    load_free_lists( (void *) ((char *)mem + 2 * index * sizeof(void *)), index+1, n_of_lists-1);
}

void populate_free_list(size_t initial_value, int index, int steps){
    if(!index) return;
    *free_lists[index] = initial_value;
    populate_free_list(initial_value >> 1, index+1, steps-1);
}