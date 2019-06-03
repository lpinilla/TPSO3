#include <n_pipes_test.h>

static void process_1();

void pipe_creation_test(){
    sys_create_n_pipe("/Hola");
    int fd = sys_open_fd("/Hola", W_ONLY);
    sys_create_process(process_1, "Proceso 1", BACKGROUND);
    sys_write_fd(fd, "Hola", 5);
    sys_close_fd(fd);
    //sys_delete_file("/Hola");
    return;
}

static void process_1(){
    char msg[5];
    int fd = sys_open_fd("/Hola", R_ONLY);
    sys_read_fd(fd, msg, 5);
    print_f("%s", msg);
    return;
}