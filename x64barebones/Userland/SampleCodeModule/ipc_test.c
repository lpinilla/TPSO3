#include "include/ipc_test.h"

#define MAX_MSG_SIZE 256

void ipc_child1_process();
void ipc_child2_process();
void ipc_child3_process();

static int child1;
static int child2;
static int child3;
static char msg[MAX_MSG_SIZE];

void ipc_child1_process(){
    sys_sleep(5);
    print_f("Current Processes: \n");
    sys_print_all_procceses();
    print_f("\n");

    char * msg1 = "First Message";
    print_f("Message write from First Child Process to Second Child Process : %s.\n", msg1);
    sys_set_foreground_process(child2);
    sys_ipc_write(msg1, child2);

    while(!sys_is_current_process_foreground()){}
    char * msg2 = "Second Message";
    print_f("Message write from First Child Process to Third Child Process : %s.\n", msg2);
    sys_set_foreground_process(child3);
    sys_ipc_write(msg2, child3);
    sys_sleep(5);

}

void ipc_child2_process(){
    sys_ipc_read(child2, msg);
    sys_set_foreground_process(child2);
    print_f("Message read from Second Child Process : %s.\n", msg);
    sys_set_foreground_process(child1);
}

void ipc_child3_process(){
    sys_ipc_read(child3, msg);
    sys_set_foreground_process(child3);
    print_f("Message read from Third Child Process : %s.\n", msg);
    sys_set_foreground_process(child1);
}

void ipc_test(){

	child1 = sys_create_process(ipc_child1_process, "First Child Process", FOREGROUND);
	child2 = sys_create_process(ipc_child2_process, "Second Child Process", BACKGROUND);
    child3 = sys_create_process(ipc_child3_process, "Third Child Process", BACKGROUND);

    while(!sys_is_current_process_foreground()){}
	print_f("\nCurrent Processes: \n");
    sys_print_all_procceses();
}