#include <n_pipes_test.h>

static void process_1();
static void process_2();

void pipe_creation_test(){
    print_f("Creando named pipe en el path /Test \n");
    sys_create_n_pipe("/Test");
    print_f("Abriendo el fd del proceso main en modo write para el named pipe \n");
    int fd = sys_open_fd("/Test", W_ONLY);
    print_f("Escribiendo Hola en el pipe mediante el fd creado \n ");
    sys_write_fd(fd, "Hola", 4);
    print_f("Creando procesos 1 y 2 \n");
    sys_create_process(process_1, "Proceso 1", BACKGROUND);
    sys_create_process(process_2, "Proceso 2", BACKGROUND);
    sys_close_fd(fd);
    print_f("Proceso principal espera 100 ticks y borra el pipe \n");
    sys_sleep(100);
    sys_delete_file("/Hola");
    return;
}

static void process_1(){
    char msg[9];
    msg[8] = 0;
    print_f("Abriendo el fd en el proceso 1 en modo read para el named pipe \n");
    int fd = sys_open_fd("/Test", R_ONLY);
    print_f("Leyendo 8 caracteres, esperamos el Hola y el Chau \n");
    sys_read_fd(fd, msg, 8);
    sys_close_fd(fd);
    print_f("Imprimiendo el string leido del pipe: ");
    print_f("%s \n", msg);
    return;
}

static void process_2(){
    print_f("Abriendo el fd en el proceso 2 en modo write para el named pipe \n");
    int fd = sys_open_fd("/Test", W_ONLY);
    print_f("Durmiendo el proceso 2 durante 20 ticks asi el proceso 1 lee y cuando no tiene mas caracteres espera a que el proceso 2 escriba \n");
    sys_sleep(20);
    print_f("Escribiendo Chau en el pipe mediante el fd creado \n");
    sys_write_fd(fd, "Chau", 4);
    sys_close_fd(fd);
}