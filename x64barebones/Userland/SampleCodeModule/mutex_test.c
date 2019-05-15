#include "include/mutex_test.h"

#define COUNT_TO 1000000

static int x;
static int lock;

void variable_lock_test(){
    while(1){
        sys_lock(&lock);
        if(x >= COUNT_TO){
            sys_unlock(&lock);
            return;
        }
        ++x;
        sys_unlock(&lock);
    }
}

void mutex_test(){
    x = 0;
    lock = 0;
    sys_create_process(variable_lock_test, "M_TEST1", BACKGROUND);
    sys_create_process(variable_lock_test, "M_TEST2", BACKGROUND);
    sys_create_process(variable_lock_test, "M_TEST3", BACKGROUND);
    sys_create_process(variable_lock_test, "M_TEST4", BACKGROUND);
    sys_create_process(variable_lock_test, "M_TEST5", BACKGROUND);
    sys_create_process(variable_lock_test, "M_TEST6", BACKGROUND);
    sys_create_process(variable_lock_test, "M_TEST7", BACKGROUND);
    sys_create_process(variable_lock_test, "M_TEST8", BACKGROUND);
    sys_create_process(variable_lock_test, "M_TEST9", BACKGROUND);

    sys_print_all_procceses();
    while(x < COUNT_TO);
    print_f("Should be %d : %d \n", COUNT_TO, x);
}
