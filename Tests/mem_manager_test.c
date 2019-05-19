#include "../Tasteful/testing_suite.h"
#include "../x64barebones/Kernel/include/mem_manager.h"
#include "../x64barebones/Kernel/include/graphics.h"


void powers_in_between_test();
void powers_in_between_test2();
void powers_in_between_test3();
void powers_in_between_test4();
void free_lists_creation_test();
void free_lists_creation_test2();
void list_initial_populate_test();

int main(void){
    create_suite("Testing the Memory Manager");
    //agregando los tests
    add_test(powers_in_between_test);
    add_test(powers_in_between_test2);
    add_test(powers_in_between_test3);
    add_test(powers_in_between_test4);
    add_test(free_lists_creation_test);
    add_test(free_lists_creation_test2);
    add_test(list_initial_populate_test);
    //correr la suite
    run_suite();
    //liberar los espacios
    clear_suite();
}

void powers_in_between_test(){
    assert_true(powers_in_between(1<<12) == 0);
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

void free_lists_creation_test(){
    size_t total_size = (1<<15); //32KB
    int n_of_lists = powers_in_between(total_size);
    int n_of_elems = 1<<n_of_lists;
    int mem[n_of_elems], asst = 0;
    for(int i = 0; i < n_of_elems; i++) mem[i] = i+1;
    load_free_lists(mem, 0, n_of_lists);
    asst = *free_lists[0] == mem[0];
    asst = *free_lists[1] == mem[1];
    asst = *free_lists[2] == mem[3];
    assert_true(asst);
}

void free_lists_creation_test2(){
    size_t total_size = (1<<16); //64KB
    int n_of_lists = powers_in_between(total_size);
    int n_of_elems = 1<<n_of_lists;
    int mem[n_of_elems], asst = 0;
    for(int i = 0; i < n_of_elems; i++) mem[i] = i+1;
    load_free_lists(mem, 0, n_of_lists);
    asst = *free_lists[0] == mem[0];
    asst = *free_lists[1] == mem[1];
    asst = *free_lists[2] == mem[3];
    asst = *free_lists[3] == mem[7];
    assert_true(asst);
}

void list_initial_populate_test(){
    size_t total_size = (1<<15); //32KB
    int n_of_lists = powers_in_between(total_size);
    int n_of_elems = 1<<n_of_lists;
    int mem[n_of_elems], asst = 0, aux = 0;
    memset(mem, 0, n_of_elems * sizeof(int));
    load_free_lists(mem, 0, n_of_lists);
    aux = PAGE_SIZE << n_of_lists;
    populate_free_list(aux, 0, n_of_lists - (n_of_lists / PAGE_SIZE));    
    for(int i = 0; i < n_of_lists; i++, aux >>=1){
        if(*free_lists[i] != aux){
            asst = 1;
            break;
        }
    }
    assert_true(!asst);
}