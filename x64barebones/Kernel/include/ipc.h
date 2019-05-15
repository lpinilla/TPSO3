#ifndef _IPC_H_
#define _IPC_H_

#include <stdint.h>
#include "./mem_manager.h"
#include "./lib.h"
#include "./mutex.h"
#include "./semaphore.h"

#define MAX_MESSAGES 256
#define MAX_MESSAGE_SIZE 256

typedef struct{
    int id;
    char msg[MAX_MESSAGE_SIZE];
}t_Message;

typedef t_Message * Message;

void init_mailbox();
void * get_mailbox_address();
void my_write(char * msg, int id);
void my_read(int id, char * ret);

#endif