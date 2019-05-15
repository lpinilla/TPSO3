#include "../Tasteful/testing_suite.h"
#include "../x64barebones/Kernel/include/mem_manager.h"
#include "../x64barebones/Kernel/include/lib.h"

void strlen_test1();
void strlen_test2();
void strlen_test3();
void strcmp_test1();
void strcmp_test2();
void strcmp_test3();
void strcmp_test4();
void strcmp_test5();


int main(void){
    create_suite("Testing Lib");
    //agregando los tests
    add_test(strlen_test1);
    add_test(strlen_test2);
    add_test(strlen_test3);
    add_test(strcmp_test1);
    add_test(strcmp_test2);
    add_test(strcmp_test3);
    add_test(strcmp_test4);
    add_test(strcmp_test5);
    //correr la suite
    run_suite();
    //liberar los espacios
    clear_suite();
}

void strlen_test1(){
    char * s = "hola";
    assert_true(str_len(s) == 5);
}

void strlen_test2(){
    char * s = "";
    assert_true(str_len(s) == 1);
}

void strlen_test3(){
    char * s = NULL;
    assert_true(str_len(s) == 0);
}

void strcmp_test1(){
    char * s = "hola", * s2 = "hola";
    assert_true(str_cmp(s,s2) == 0);
}

void strcmp_test2(){
    char * s = "hola", * s2 = "";
    assert_true(str_cmp(s,s2) != 0);
}

void strcmp_test3(){
    char * s = "hola", * s2 = NULL;
    assert_true(str_cmp(s,s2) != 0);
}

void strcmp_test4(){
    char * s = "hola", * s2 = "holas";
    assert_true(str_cmp(s,s2) != 0);
}

void strcmp_test5(){
    char * s = "hola", * s2 = "asdasd";
    assert_true(str_cmp(s,s2) != 0);
}