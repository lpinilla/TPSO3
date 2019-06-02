#include <n_pipes_test.h>

void pipe_creation_test(){
    sys_create_n_pipe("/Hola");
    int fd = sys_open_fd("/Hola", R_ONLY);
    sys_close_fd(fd);
    sys_delete_file("/Hola");
}