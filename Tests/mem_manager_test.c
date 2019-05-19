#include "../Tasteful/testing_suite.h"
#include "../x64barebones/Kernel/include/mem_manager.h"
#include "../x64barebones/Kernel/include/graphics.h"


void powers_in_between_test();
void powers_in_between_test2();
void powers_in_between_test3();
void powers_in_between_test4();

int main(void){
    create_suite("Testing the Memory Manager");
    //agregando los tests
    add_test(powers_in_between_test);
    add_test(powers_in_between_test2);
    add_test(powers_in_between_test3);
    add_test(powers_in_between_test4);
    //correr la suite
    run_suite();
    //liberar los espacios
    clear_suite();
}

void powers_in_between_test(){
    assert_true(!powers_in_between(1<<12));
}

void powers_in_between_test2(){
    assert_true(powers_in_between(1<<13) == 1);
}

void powers_in_between_test3(){
    assert_true(powers_in_between(1<<16) == 4);
}

void powers_in_between_test4(){
    assert_true(powers_in_between(1<<11) == -1);
}