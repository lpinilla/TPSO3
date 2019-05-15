#include "include/semaphore_test.h"

static int sem;

void sem_child1_process();
void sem_child2_process();
void sem_child3_process();

static int child1;
static int child2;
static int child3;

void sem_child1_process(){
    sys_sleep(5);
    print_f("Current Processes: \n");
    sys_print_all_procceses();
    sys_new_line();
    print_f("Sem Post from First Child\n");
    sys_set_foreground_process(child2);
    sys_sleep(10);

    sys_sem_post(sem);

    sys_sleep(10);
    print_f("Sem Post from First Child\n");
    sys_set_foreground_process(child3);
    sys_sleep(10);

    sys_sem_post(sem);
}

void sem_child2_process(){
    sys_sleep(10);
    sys_sem_wait(sem);
    print_f("Sem Consumed from Second Child\n");
    sys_set_foreground_process(child1);
}

void sem_child3_process(){
    sys_sleep(10);
    sys_sem_wait(sem);
    print_f("Sem Consumed from Third Child\n");
    sys_new_line();
    sys_set_foreground_process(child1);
}

void semaphore_test(){

    sem = sys_sem_open("Sem Test");
	child1 = sys_create_process(sem_child1_process, "First Child Process", FOREGROUND);
	child2 = sys_create_process(sem_child2_process, "Second Child Process", BACKGROUND);
    child3 = sys_create_process(sem_child3_process, "Third Child Process", BACKGROUND);

    while(!sys_is_current_process_foreground()){}
	print_f("Current Processes: \n");
    sys_print_all_procceses();
    sys_sem_close(sem);
}