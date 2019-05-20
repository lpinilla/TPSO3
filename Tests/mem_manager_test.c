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
void recursive_divide_test();
void recursive_divide_test2();
void recursive_divide_test3();
void look_space_in_list_test();
void look_space_in_list_test2();
void look_space_in_list_test3();
void split_upper_level_test();
void split_upper_level_test2();
void init_list_test();
void init_list_test2();
void alloc_test();
void alloc_test2();
void alloc_test3();
void alloc_test4();
void alloc_test5();
void alloc_test6();
void alloc_first_byte_size_test();
void put_into_list_test();
void look_for_space_in_list_test();
void free_test();
void free_test2();

//helper functions
void print_mem();

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
    add_test(recursive_divide_test);
    add_test(recursive_divide_test2);
    add_test(recursive_divide_test3);
    add_test(look_space_in_list_test);
    add_test(look_space_in_list_test2);
    add_test(look_space_in_list_test3);
    add_test(split_upper_level_test);
    add_test(split_upper_level_test2);
    add_test(init_list_test);
    add_test(init_list_test2);
    add_test(alloc_test);
    add_test(alloc_test2);
    add_test(alloc_test3);
    add_test(alloc_test4);
    add_test(alloc_test5);
    add_test(alloc_test6);
    add_test(alloc_first_byte_size_test);
    add_test(put_into_list_test);
    add_test(look_for_space_in_list_test);
    add_test(free_test);
    add_test(free_test2);
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

void recursive_divide_test(){
    size_t total_size = (1<<15); //32KB
    void * mem = malloc(total_size);
    int ret = 0;
    initialize_list(mem, total_size);
    recursive_divide(1, 1);
    ret = look_for_space_of_size(2,8192) != -1;
    ret += look_for_space_of_size(2,8192 + 4096) != -1;
    free(mem);
    assert_true(ret == 2);
}

void recursive_divide_test2(){
    size_t total_size = (1<<15); //32KB
    void * mem = malloc(total_size);
    int ret = 0;
    initialize_list(mem, total_size);
    recursive_divide(0, 1);
    ret = free_lists[0][0] == 0;
    ret += look_for_space_of_size(1,16384) != -1;
    free(mem);
    assert_true(ret == 2);
}

void recursive_divide_test3(){
    size_t total_size = (1<<15); //32KB
    void * mem = malloc(total_size);
    int ret = 0;
    initialize_list(mem, total_size);
    recursive_divide(0, 2);    
    ret = free_lists[0][0] == 0;
    ret += free_lists[1][0] == 0;
    ret += look_for_space_of_size(1,16384) != -1;
    ret += look_for_space_of_size(2,8192) != -1;
    ret += look_for_space_of_size(2, 8192 + 4096) != -1;
    free(mem);
    assert_true(ret == 5);
}

void look_space_in_list_test(){
    size_t total_size = (1<<15); //32KB
    void * mem = malloc(total_size);
    int aux = 0;
    initialize_list(mem, total_size);
    aux = look_for_space_in_list(0);
    free(mem);
    assert_true(aux == 1<<14);
}

void look_space_in_list_test2(){
    size_t total_size = (1<<15); //32KB
    void * mem = malloc(total_size);
    int aux = 0;
    initialize_list(mem, total_size);
    look_for_space_in_list(0);
    aux = look_for_space_in_list(0);
    free(mem);
    assert_true(aux == -1);
}

void look_space_in_list_test3(){
    size_t total_size = (1<<15); //32KB
    void * mem = malloc(total_size);
    int aux = 0;
    initialize_list(mem, total_size);
    int index = powers_in_between(1<<13, max_partition_size);
    aux = look_for_space_in_list(index);
    free(mem);
    assert_true(aux == 1<<13);
}

void split_upper_level_test(){
    size_t total_size = (1<<15); //32KB
    void * mem = malloc(total_size);
    int ret = 0;
    initialize_list(mem, total_size);
    split_upper_level(1<<13,0);
    ret = free_lists[2][0] == 8192;
    ret += free_lists[2][1] == 8192 + 4096;
    free(mem);
    assert_true(ret == 2);
}

void split_upper_level_test2(){
    size_t total_size = (1<<15); //32KB
    void * mem = malloc(total_size);
    int ret = 0;
    initialize_list(mem, total_size);
    split_upper_level(1<<14,1);
    ret = free_lists[0][0] == 0;
    ret += free_lists[1][0] == 0;
    ret += look_for_space_of_size(1, 24576) != -1;
    ret += look_for_space_of_size(2, 16384) != -1;
    ret += look_for_space_of_size(2, 16384 + 4096) != -1;
    free(mem);
    assert_true(ret == 5);
}

void init_list_test(){
    size_t total_size = (1<<15); //32KB
    void * mem = malloc(total_size);
    int ret = 0;
    initialize_list(mem, total_size);
    ret = total_mem_size == total_size;
    ret += n_of_lists == 3;
    free(mem);
    assert_true(ret == 2);
}

void init_list_test2(){
    size_t total_size = ((1<<15)-1); //16KB (lo actualiza a 16)
    void * mem = malloc(total_size);
    int ret = 0;
    initialize_list(mem, total_size);
    ret = total_mem_size == (1<<15);
    ret += n_of_lists == 3;
    free(mem);
    assert_true(ret == 2);
}

void alloc_test(){
    size_t total_size = (1<<15); //32KB
    void * mem = malloc(total_size), * requested = NULL;
    int ret = 0;
    initialize_list(mem, total_size);
    requested = mem_alloc(PAGE_SIZE);
    ret = requested != NULL;
    free(mem);
    assert_true(ret);
}

void alloc_test2(){
    size_t total_size = ((1<<15)); //32KB
    void * mem = malloc(total_size), * requested = NULL;
    int ret = 0;
    initialize_list(mem, total_size);
    requested = mem_alloc(8);
    ret = requested != NULL;
    free(mem);
    assert_true(ret);
}

void alloc_test3(){
    size_t total_size = ((1<<15)); //32KB
    void * mem = malloc(total_size), * r1 = NULL, *r2 = NULL;
    int ret = 0;
    initialize_list(mem, total_size);
    r1 = mem_alloc(8);
    ret = r1 != NULL;
    r2 = mem_alloc(8);
    ret += r2 != NULL;
    free(mem);
    assert_true(ret == 2);
}

void alloc_test4(){
    size_t total_size = ((1<<15)); //32KB
    void * mem = malloc(total_size), * r1 = NULL, *r2 = NULL, *r3 = NULL;
    int ret = 0;
    initialize_list(mem, total_size);
    r1 = mem_alloc((1<<13)-1024);
    ret = r1 != NULL;
    r2 = mem_alloc(8);
    ret += r2 != NULL;
    r3 = mem_alloc(8);
    ret += r3 != NULL;
    free(mem);
    assert_true(ret == 3);
}

void alloc_test5(){
    size_t total_size = ((1<<15)); //32KB
    void * mem = malloc(total_size), * r1 = NULL, *r2 = NULL;
    int ret = 0;
    initialize_list(mem, total_size);
    r1 = mem_alloc(1<<13);
    ret = r1 != NULL;
    r2 = mem_alloc(1<<13);
    ret += r2 == NULL;
    free(mem);
    assert_true(ret == 2);
}

void alloc_test6(){
    size_t total_size = ((1<<15)); //32KB
    void * mem = malloc(total_size), * r1 = NULL, *r2 = NULL, * r3 = NULL;
    int ret = 0;
    initialize_list(mem, total_size);
    r1 = mem_alloc(1<<13);
    ret = r1 != NULL;
    r2 = mem_alloc(1<<12);
    ret += r2 != NULL;
    r3 = mem_alloc(1<<12);
    ret += r3 == NULL;
    free(mem);
    assert_true(ret == 3);
}

void alloc_first_byte_size_test(){
    size_t total_size = ((1<<15)); //32KB
    void * mem = malloc(total_size), * r1 = NULL;
    int ret = 0;
    initialize_list(mem, total_size);
    r1 = mem_alloc(1<<11);
    if(r1 == NULL) exit(EXIT_FAILURE);
    ret = *((int *)r1 - 1) == PAGE_SIZE;
    free(mem);
    assert_true(ret);
}

void put_into_list_test(){
    size_t total_size = ((1<<15)); //32KB
    void * mem = malloc(total_size), * r1 = NULL;
    int ret = 0;
    initialize_list(mem, total_size);
    r1 = mem_alloc(1<<11);
    if(r1 == NULL) exit(EXIT_FAILURE);
    put_space_in_list(2, PAGE_SIZE);
    ret = free_lists[2][0] = PAGE_SIZE;
    free(mem);
    assert_true(ret);
}

void look_for_space_in_list_test(){
    size_t total_size = ((1<<15)); //32KB
    void * mem = malloc(total_size);
    int ret = 0;
    initialize_list(mem, total_size);
    ret =  look_for_space_of_size(2,PAGE_SIZE) == PAGE_SIZE;
    free(mem);
    assert_true(ret);
}

void free_test(){
    size_t total_size = ((1<<15)); //32KB
    void * mem = malloc(total_size), * r1 = NULL;
    int ret = 0;
    initialize_list(mem, total_size);
    r1 = mem_alloc(1<<11);
    if(r1 == NULL) exit(EXIT_FAILURE);
    free_mem(r1);
    ret = look_for_space_of_size(2, PAGE_SIZE) != -1;
    free(mem);
    assert_true(ret);
}

void free_test2(){
    size_t total_size = ((1<<15)); //32KB
    void * mem = malloc(total_size), * r1 = NULL, * r2 = NULL, * r3 = NULL;
    int ret = 0;
    initialize_list(mem, total_size);
    r1 = mem_alloc(1<<11);
    if(r1 == NULL) exit(EXIT_FAILURE);
    r2 = mem_alloc(1<<11);
    if(r2 == NULL) exit(EXIT_FAILURE);
    r3 = mem_alloc(1<<11);
    if(r3 == NULL) exit(EXIT_FAILURE);
    free_mem(r3);
    ret = look_for_space_of_size(2, 12288) != -1;
    free(mem);
    assert_true(ret);
}

//helper function
void print_mem(){
    for(int i = 0; i < powers_in_between(PAGE_SIZE, total_mem_size); i++){
        for(int j = 0; j < (1<<i);j++){
            printf("%d ", free_lists[i][j]);
        }
        printf("\n");
    }
}