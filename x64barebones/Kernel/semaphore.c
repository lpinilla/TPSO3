#include "include/semaphore.h"
#include <graphics.h>
#include <queue.h>

typedef struct nodeADT *node_t;


typedef struct nodeADT{
    process_t element;
    node_t next;
}nodeADT;

typedef struct semaphoreADT{
    char * name[MAX_SEMAPHORE_NAME];
    int sid;
    int value;
    int lock;
    node_t first_waiting_process;
    node_t last_waiting_process;
} semaphoreADT;


// typedef struct semaphoreADT {
//     char * name[MAX_SEMAPHORE_NAME];
//     int sid;
//     int value;
//     queue_t waiting_processes;
// } semaphoreADT;

typedef struct semaphoreADT * semaphore_t;

static semaphore_t all_semaphores[MAX_SEMAPHORES];
static int global_sid;

void init_semaphores(){
    for(int i = 0; i< MAX_SEMAPHORES; i++){
        all_semaphores[i] = NULL;
    }
    global_sid = 0;
}

int my_sem_open(char * name){

    for(int i = 0; i < global_sid; i++){
        if(all_semaphores[i] != NULL && str_cmp((char*)all_semaphores[i]->name, name) == 0){
            return i;
        }
    }

    semaphore_t new_semaphore = mem_alloc(sizeof(semaphoreADT));

    str_cpy(name, (char *)new_semaphore->name);
    new_semaphore->sid = global_sid;
    new_semaphore->value = 0;
    new_semaphore->lock = 0;
    
    new_semaphore->first_waiting_process = NULL;
    new_semaphore->last_waiting_process = NULL;
    
    //new_semaphore->waiting_processes=new_queue();

    all_semaphores[global_sid++] = new_semaphore;

    return new_semaphore->sid;
}

int my_sem_close(int sid){
    semaphore_t semaphore = all_semaphores[sid];
    all_semaphores[sid] = NULL;
    
    if(semaphore->first_waiting_process != NULL){

        node_t aux2, aux = semaphore->first_waiting_process;
        while(aux != semaphore->last_waiting_process){
            aux2 = aux;
            aux = aux->next;
            free_mem(aux2);
        }
        free_mem(aux);

        free_mem(semaphore);
        return 1;
    }
    else{
        free_mem(semaphore);
        return 0;
    }
    
    // if(get_queue_size(semaphore->waiting_processes)>0){
    //     do{
    //         dequeue(semaphore->waiting_processes);
    //     }while(get_queue_size(semaphore->waiting_processes)>0);
    // }
    // free_queue(semaphore->waiting_processes);
    // free_mem(semaphore);
    //return 1;
}

int my_sem_post(int sid){
    semaphore_t semaphore = all_semaphores[sid];
    
    
    if(semaphore->value <= 0){
        node_t aux = semaphore->first_waiting_process;
        if(aux != NULL){
            process_t p = aux->element;
            if(aux->next != NULL){
                semaphore->first_waiting_process = aux->next;
            }
            else{
                semaphore->first_waiting_process = NULL;
                semaphore->last_waiting_process = NULL;
            }
            free_mem(aux);
            set_state(p, P_READY);
        }
    }
    semaphore->value++;
    return semaphore->value;
    
    // if(semaphore->value <= 0){
    //     if(get_queue_size(semaphore->waiting_processes)>0){
    //         process_t aux = dequeue(semaphore->waiting_processes);
    //         set_state(aux, P_READY);
    //     }
    // }
    // semaphore->value++;
    // return semaphore->value;
}

int my_sem_wait(int sid){
    semaphore_t semaphore = all_semaphores[sid];
    
    if(semaphore->value <= 0){
        semaphore->value = 0;

        node_t aux = mem_alloc(sizeof(nodeADT));
        aux->element = get_current_process();
        aux->next = NULL;
        if(semaphore->first_waiting_process == NULL){
            semaphore->first_waiting_process = aux;
        }
        else{
            semaphore->last_waiting_process->next = aux;
        }
        semaphore->last_waiting_process = aux;
        set_state(semaphore->last_waiting_process->element, P_WAITING);
        _context_switch_process();
    }
    semaphore->value--;
    return semaphore->value;
    
    // if(semaphore->value <= 0) {
    //     semaphore->value = 0;
    //     process_t aux = get_current_process();
    //     set_state(aux, P_WAITING);
    //     enqueue(semaphore->waiting_processes, aux);
    //     _context_switch_process();
    // }
    // semaphore->value--;
    // return semaphore->value;
}

int my_sem_get_value(int sid){
    return all_semaphores[sid]->value;
}

void my_sem_print(int sid){
    semaphore_t m = all_semaphores[sid];
	draw_string("SID: ");
	draw_number(m->sid);
	draw_string(" SEMAPHORE NAME: ");
	draw_string((char *)m->name);
	draw_string(" VALUE: ");
	draw_number(all_semaphores[sid]->value);
	new_line();
}