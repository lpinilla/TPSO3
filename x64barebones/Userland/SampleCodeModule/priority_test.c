#include "include/priority_test.h"

static int child1_number;
static int child2_number;


void child1();
void child2();

void child1(){
    while(1){
        child1_number++;
        print_f("Process 1\n");
    }
}

void child2(){
    for(int i = 0; i<10; i++){
        child2_number++;
        print_f("Process 2\n");
    }
    sys_nice(PRIORITY_2);
    print_f("\n Priority of process 2 changed with nice\n\n");
    while(1){
        child2_number++;
        print_f("Process 2\n");
    }
}

void priority_test(){

    child1_number = 0;
    child2_number = 0;

	int child1_pid = sys_create_priority_process(child1, "First Child Process", BACKGROUND, PRIORITY_3);
	int child2_pid = sys_create_priority_process(child2, "Second Child Process", BACKGROUND, PRIORITY_1);

	print_f("Current Processes: \n\n");
    sys_print_all_procceses();

    sys_sleep(50);

    print_f("Killing process number: %d\n", child1_pid);
    sys_kill_process(child1_pid);

    print_f("Killing process number: %d\n", child2_pid);
    sys_kill_process(child2_pid);

    
    print_f("Total cycles process 1 with priority 3: %d\n", child1_number);
    print_f("Total cycles process 2 with priority 1(first 10 cycles) and priority 2(last cycles): %d\n", child2_number);

}
