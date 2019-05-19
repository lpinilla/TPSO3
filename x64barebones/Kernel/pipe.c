#include <pipe.h>

typedef enum {READ, WRITE} pipe_mode;

typedef struct pipeADT * pipe_t;

typedef struct pipeADT {
    char * name[MAX_PIPE_NAME];
    char * data[PIPE_DATA_SIZE];
    int * offset;
    pipe_mode mode;
} pipeADT;

static pipe_t[MAX_PIPES] global_pipes;

void init_pipes() {
    for(int i=0; i<MAX_PIPES; i++) {
        global_pipes[i]=NULL;
    }
}

static int find_id(char * pipe_name){
    int first_null=-1;
    int i;
    for(i=0; i<MAX_PIPES; i++){
        if(global_pipes[i]==NULL && first_null==-1){
            first_null=i;
        }
        if(global_pipes[i]!=NULL && strcmp(pipe_name, global_pipes[i]->name){
            return i;
        }
    }
    return first_null;
    
}

int get_pipe(char * pipe_name, int fd[2]){
    int id = find_id(pipe_name);
    if(id==-1)
        return -1;
    if(global_pipes[id]==NULL){

    }
}