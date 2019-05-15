#include "../Tasteful/testing_suite.h"
#include "../x64barebones/Kernel/include/mem_manager.h"
#include "../x64barebones/Kernel/include/ipc.h"

void write_test();
void writer_reader_test();
void reader_writer_test();

int main(void){
    create_suite("Testing the IPC");
    //agregando los tests
    add_test(write_test);
    add_test(writer_reader_test);
    //correr la suite
    run_suite();
    //liberar los espacios
    clear_suite();
}

void write_test(){
    void * mailbox = malloc(1024*1024 *100);
    initialize_list(mailbox, 1024*1024 *100); //creo que le puse 100mb de memoria
    init_mailbox();
    Message message = NULL, written = NULL;
    message = malloc(sizeof(t_Message));
    if(message == NULL){
        perror("Malloc Error");
        exit(EXIT_FAILURE);
    }
    void * start_of_mailbox = get_mailbox_address();
    int ret = 0;
    message->rpid = 1;
    message->spid = getpid();
    message->mid = 0;
    message->msg = malloc(strlen("Hola mundo!") * sizeof(char));
    strcpy(message->msg, "Hola mundo!");
    message->seen = 0;
    my_write("Hola mundo!", 1, getpid());
    written = (Message) start_of_mailbox;
    ret += message->rpid - written->rpid;
    ret += message->spid - written->spid;
    ret += message->mid - written->mid;
    ret += message->seen - written->seen;
    ret += strncmp(message->msg, written->msg, strlen(message->msg));
    free(message->msg);
    free(message);
    free(mailbox);
    assert_true(!ret);
}

void writer_reader_test(){
    void * mailbox = malloc(1024*1024 *100);
    initialize_list(mailbox, 1024*1024 *100); //creo que le puse 100mb de memoria
    init_mailbox();
    char * msg = "hola mundo!";
    int pid = fork(), ret = 0;
    if(pid < 0){
        perror("Fork Error");
        exit(EXIT_FAILURE);
    }else if(pid == 0){
        sleep(5); //para que el padre escriba primero
        char * read_msg = malloc(13 * sizeof(char));
        my_read(getpid(), read_msg);
        ret = strcmp(msg, read_msg);
        exit(EXIT_SUCCESS);
    }
    my_write(msg, pid, getpid());
    free(mailbox);
    assert_true(!ret);
}

/*void reader_write_test(){
    char * msg = "hola mundo!";
    int pid = fork(), ret = 0;
    if(pid < 1){
        perror("Fork Error");
        exit(EXIT_FAILURE);
    }else if(pid == 0){
        char * read_msg = my_read(getpid());
        ret = strcmp(msg, read_msg);
        exit(EXIT_SUCCESS);
    }
    my_write(msg, pid, getpid());
    assert_true(!ret);
}*/