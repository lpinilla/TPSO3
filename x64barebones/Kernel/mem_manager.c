//incluirlo manualmente para los tests
#include "./include/mem_manager.h"

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

void initialize_list(void * start_ptr, size_t total_size){
    total_mem_size = total_size;
    root = start_dir = start_ptr;

    root->next = NULL;
    root->prev = NULL;
    root->mem_ptr =  (void *) ((char *)start_ptr + sizeof(struct t_Node));
    root->size = total_size - sizeof(struct t_Node);
    root->status = F;
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