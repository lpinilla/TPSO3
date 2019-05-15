#include "include/processes_test.h"

void child1_process();
void child2_process();

void child1_process(){
    while(1){

    }
}

void child2_process(){
    while(1){

    }
}

void process_test(){

	int child1 = sys_create_process(child1_process, "First Child Process", BACKGROUND);
	int child2 = sys_create_process(child2_process, "Second Child Process", BACKGROUND);

	print_f("Current Processes: \n");
    sys_print_all_procceses();

    print_f("Killing process number: %d\n", child1);
    sys_kill_process(child1);

    print_f("Killing process number: %d\n", child2);
    sys_kill_process(child2);

    print_f("Current Processes: \n");
    sys_print_all_procceses();
}
