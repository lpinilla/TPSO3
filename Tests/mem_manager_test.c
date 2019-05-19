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
void list_initial_populate_test2();
void list_initial_populate_test3();
void fix_size_test();
void fix_size_test2();
void fix_size_test3();
void fix_size_test4();
void power_of_2_check_test();
void power_of_2_check_test2();
void power_of_2_check_test3();
void alloc_free_list_available_test();

//helper functions
void print_mem(size_t total_size);

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
    add_test(list_initial_populate_test2);
    add_test(list_initial_populate_test3);
    add_test(fix_size_test);
    add_test(fix_size_test2);
    add_test(fix_size_test3);
    add_test(fix_size_test4);
    add_test(power_of_2_check_test);
    add_test(power_of_2_check_test2);
    add_test(power_of_2_check_test3);
    add_test(alloc_free_list_available_test);
    //correr la suite
    run_suite();
    //liberar los espacios
    clear_suite();
}

void powers_in_between_test(){
    assert_true(powers_in_between(PAGE_SIZE, 1<<12) == 0);
}

void powers_in_between_test2(){
    assert_true(powers_in_between(PAGE_SIZE, 1<<13) == 1);
}

void powers_in_between_test3(){
    assert_true(powers_in_between(PAGE_SIZE, 1<<16) == 4);
}

void powers_in_between_test4(){
    assert_true(powers_in_between(PAGE_SIZE, 1<<11) == -1);
}

void free_lists_creation_test(){
    size_t total_size = (1<<15); //32KB
    int n_of_lists = powers_in_between(PAGE_SIZE, total_size);
    int n_of_elems = 1<<n_of_lists;
    int mem[n_of_elems], asst = 0;
    for(int i = 0; i < n_of_elems; i++) mem[i] = i+1;
    load_free_lists(mem, 0, n_of_lists);
    asst = *free_lists[0] == mem[0];
    asst += *free_lists[1] == mem[1];
    asst += *free_lists[2] == mem[3];
    assert_true(asst == 3);
}

void free_lists_creation_test2(){
    size_t total_size = (1<<16); //64KB
    int n_of_lists = powers_in_between(PAGE_SIZE, total_size);
    int n_of_elems = 1<<n_of_lists;
    int mem[n_of_elems], asst = 0;
    for(int i = 0; i < n_of_elems; i++) mem[i] = i+1;
    load_free_lists(mem, 0, n_of_lists);
    asst = *free_lists[0] == mem[0];
    asst += *free_lists[1] == mem[1];
    asst += *free_lists[2] == mem[3];
    asst += *free_lists[3] == mem[7];
    assert_true(asst == 4);
}

void list_initial_populate_test(){
    size_t total_size = (1<<15); //32KB
    int n_of_lists = powers_in_between(PAGE_SIZE, total_size);
    int n_of_elems = 1<<n_of_lists;
    int mem[n_of_elems], asst = 0, aux = 0;
    memset(mem, 0, n_of_elems * sizeof(int));
    load_free_lists(mem, 0, n_of_lists);
    aux = PAGE_SIZE << n_of_lists;
    populate_free_list(aux, 0, n_of_lists);    
    for(int i = 0; !asst && i < n_of_lists; i++, aux >>=1){
        if(*free_lists[i] != aux) asst = 1;
    }
    assert_true(!asst);
}

void list_initial_populate_test2(){
    size_t total_size = (1<<16); //64KB
    int n_of_lists = powers_in_between(PAGE_SIZE, total_size);
    int n_of_elems = 1<<n_of_lists;
    int mem[n_of_elems], asst = 0, aux = 0;
    memset(mem, 0, n_of_elems * sizeof(int));
    load_free_lists(mem, 0, n_of_lists);
    aux = PAGE_SIZE << n_of_lists;
    populate_free_list(aux, 0, n_of_lists);    
    for(int i = 0; !asst && i < n_of_lists; i++, aux >>=1){
        if(*free_lists[i] != aux) asst = 1;
    }
    assert_true(!asst);
}

void list_initial_populate_test3(){
    size_t total_size = (1<<20); //1MB
    int n_of_lists = powers_in_between(PAGE_SIZE, total_size);
    int n_of_elems = 1<<n_of_lists;
    int mem[n_of_elems], asst = 0, aux = 0;
    memset(mem, 0, n_of_elems * sizeof(int));
    load_free_lists(mem, 0, n_of_lists);
    aux = PAGE_SIZE << n_of_lists;
    populate_free_list(aux, 0, n_of_lists);    
    for(int i = 0; !asst && i < n_of_lists; i++, aux >>=1){
        if(*free_lists[i] != aux) asst = 1;
    }
    assert_true(!asst);
}

void fix_size_test(){
    assert_true(fix_size(7) == 8);
}

void fix_size_test2(){
    assert_true(fix_size(0) == 1);
}

void fix_size_test3(){
    assert_true(fix_size(16) == 32);
}

void fix_size_test4(){
    assert_true(fix_size(PAGE_SIZE) == PAGE_SIZE<<1);
}

void power_of_2_check_test(){
    assert_true(IS_POWER_OF_2(2));
}

void power_of_2_check_test2(){
    assert_false(IS_POWER_OF_2(3));
}

void power_of_2_check_test3(){
    assert_false(IS_POWER_OF_2(15));
}

void alloc_free_list_available_test(){
    size_t total_size = (1<<15); //32KB
    void * mem = malloc(total_size), * requested = NULL;
    int ret = 0;
    initialize_list(mem, total_size);
    requested = mem_alloc(PAGE_SIZE<<1);
    if(requested == NULL){
        exit(EXIT_FAILURE);
    }
    *((int *) requested) = 30;
    /*printf("base        %p \n", memory_base());
    printf("returned    %p \n", requested);
    printf("calculated  %p \n", (int *) memory_base() + (PAGE_SIZE+1) * sizeof(char));
    printf("%d \n", *((int *) mem + (PAGE_SIZE+1) * sizeof(char)));*/
    ret =  *((int *) mem + (PAGE_SIZE+1) * sizeof(char)) == 30;
    free(mem);
    assert_true(ret);
}

//helper function

void print_mem(size_t total_size){
    for(int i = 0; i < powers_in_between(PAGE_SIZE, total_size); i++){
        for(int j = 0; j < (1<<i);j++){
            printf("%d ", free_lists[i][j]);
        }
        printf("\n");
    }
}