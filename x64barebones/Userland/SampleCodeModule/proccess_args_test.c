#include "include/processes_test.h"

static int p;

void process(int argc, void ** argv);

void process(int argc, void ** argv){
    int **myargs = (int **)argv;
    print_f("Cantidad de argumentos = %d\n", argc);
    for(int i=0; i < argc; i++){
        print_f("Argumento numbero %d is = %d\n", i + 1, **(myargs + i*sizeof(int *)) );
    }
    print_f("\n");
    sys_kill_process(p);
}

void process_args_test(){

    int argc = 2;
    void ** argv = sys_my_malloc(argc * sizeof(void *));
    void *number1 = sys_my_malloc(sizeof(int));
    void *number2 = sys_my_malloc(sizeof(int));

    *(int *)number1 = 12345;
    *(int *)number2 = 67890;

    *argv = number1;
    *(argv + sizeof(void *)) = number2;

	p = sys_create_args_process(process, "First Child Process", FOREGROUND, argc, argv);

}
