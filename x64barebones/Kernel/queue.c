#include <queue.h>

typedef nodeADT * node_t;

typedef struct node{
    void * elem;
    node_t next;
} nodeADT;

typedef struct queue{
    size_t size;
    node_t head;
    node_t tail;
} queueADT;

queueADT * new_queue(){
    queueADT * new = mem_alloc(sizeof(queueADT));
    new->size=0;
    new->head=NULL;
    new->tail=NULL;
    return new;
}

queueADT * enqueue(queueADT * queue, void * elem){
    if(queue->head=NULL){
        queue->head=elem;
        queue->tail=elem;
    } else {
        nodeADT * aux = mem_alloc(sizeof(nodeADT));
        aux->elem=elem;
        aux->next=NULL;
        queue->tail->next=aux;
        queue->tail=aux;
    }
    queue->size=queue->size + 1;
    return queue;
}

void * peek(queueADT * queue){
    return queue->head;
}

void * dequeue(queueADT * queue){
    if(queue->head==NULL){
        return NULL;
    }
    nodeADT * aux_node = queue->head;
    void * aux_elem = aux_node->elem;
    queue->head=queue->head->next;
    free_mem(aux_node);
    queue->size = queue->size - 1;
    return aux_elem;
}

size_t get_queue_size(queueADT * queue){
    return queue->size;
}

void print_queue(queueADT * queue, void (*print_func)(void * elem)) {
    nodeADT * aux = queue->head;
    while(aux!=NULL) {
        print_func(aux->elem);
        aux=aux->next;
    }
    return;
}