#include "./include/ipc.h"
#include "./include/semaphore.h"

static Message mailbox[MAX_MESSAGES];
static int sem;
static int read_lock;
static int write_lock;

void init_mailbox(){
    memset(mailbox, 0, MAX_MESSAGES * sizeof(Message));
    sem = my_sem_open("ipc");
    read_lock = 0;
    write_lock = 0;
}

void my_write(char * msg, int id){
    int i, found = 0;
    //vemos si podemos escribir
    while(my_sem_get_value(sem) > MAX_MESSAGES);
    lock_mutex(&write_lock);   //ganar el recurso
    //encontrar el 1er espacio libre
    for(i = 0; i < MAX_MESSAGES && !found; i++){
        if( mailbox[i] == NULL ) found = 1;
    }
    Message aux = mem_alloc(sizeof(t_Message));
    aux->id = id;
    str_cpy(msg, aux->msg);
    mailbox[i] = aux;
    my_sem_post(sem); //sumarle al semáforo para indicar que hay un mensaje disponible
    unlock_mutex(&write_lock);    //liberar el recurso
}

void my_read(int id, char * ret){
    int found = 0;
    my_sem_wait(sem);    //esperar al semáforo a qué haya algo para leer
    lock_mutex(&read_lock);   //ganar el recurso
    for(int i = 0; i < MAX_MESSAGES && !found; i++){
        //ver si el mensaje es para un pid que esta vivo
        if(mailbox[i]->id == id){
            str_cpy(mailbox[i]->msg, ret);
            free_mem(mailbox[i]);
            found = 1;
            mailbox[i] = NULL;
        }
    }
    if(!found){
        my_sem_post(sem); //decrementar el semáforo número si se leyó
        unlock_mutex(&read_lock);
        _context_switch_process();
        my_read(id, ret);
        return;
    }
    unlock_mutex(&read_lock);    //liberar el recurso
}

void * get_mailbox_address(){
    return mailbox;
}