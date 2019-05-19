#include <queue.h>

typedef struct nodeADT * node_t;

typedef struct nodeADT{
    void * elem;
    node_t next;
} nodeADT;

typedef struct queueADT{
    size_t size;
    node_t head;
    node_t tail;
} queueADT;

queue_t new_queue(){
    queue_t new = mem_alloc(sizeof(queueADT));
    new->size=0;
    new->head=NULL;
    new->tail=NULL;
    return new;
}

queue_t enqueue(queue_t queue, void * elem){
    if(queue->head=NULL){
        queue->head=elem;
        queue->tail=elem;
    } else {
        node_t aux = mem_alloc(sizeof(nodeADT));
        aux->elem=elem;
        aux->next=NULL;
        queue->tail->next=aux;
        queue->tail=aux;
    }
    queue->size=queue->size + 1;
    return queue;
}

void * peek(queue_t queue){
    return queue->head;
}

void * dequeue(queue_t queue){
    if(queue->head==NULL){
        return NULL;
    }
    node_t aux_node = queue->head;
    void * aux_elem = aux_node->elem;
    queue->head=queue->head->next;
    free_mem(aux_node);
    queue->size = queue->size - 1;
    return aux_elem;
}

size_t get_queue_size(queue_t queue){
    return queue->size;
}

void print_queue(queue_t queue, void (*print_func)(void * elem)) {
    node_t aux = queue->head;
    while(aux!=NULL) {
        print_func(aux->elem);
        aux=aux->next;
    }
    return;
}