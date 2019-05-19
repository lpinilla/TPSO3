#include <pipe.h>

typedef struct pipeADT * pipe_t;

typedef struct pipeADT {
    char * name[MAX_PIPE_NAME];
    int pipeid;
    char * data[PIPE_DATA_SIZE];
} pipeADT;

static pipe_t[MAX_PIPES] global_pipes;

void init_pipes() {
    for(int i=0; i<MAX_PIPES; i++) {
        global_pipes[i]=NULL;
    }
}