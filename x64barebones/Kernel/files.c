#include <files.h>

static int working_file=0;

static inode_t file_table[MAX_ENTRIES];

typedef struct inodeADT {
    char path[MAX_PATH];
    int offset;
    void * entry;
    file_t type;
} inodeADT;

void init_tables(){
    for(int i=0;i < MAX_ENTRIES; i++) {
        file_table[i]=NULL;
    }
}

int create_file(char * path, file_t type) {
    int first_empty=-1;
    draw_number(1);
    lock_mutex(&working_file);
    draw_number(2);
    for(int i=0; i<MAX_ENTRIES;i ++) {
        if(first_empty==-1 && file_table[i]==NULL){
            first_empty=i;
        }
        if(str_cmp(path,file_table[i]->path) ){
            unlock_mutex(&working_file);
            return i;
        }
    }
    if(first_empty!= -1) {
        inode_t aux = mem_alloc(sizeof(inodeADT));
        aux->offset=0;
        aux->entry= mem_alloc(INODE_BUFFER);
        str_cpy(aux->path, path);
        aux->type=type;
        file_table[first_empty] = aux;
    }
    unlock_mutex(&working_file);
    return first_empty;
}

int delete_file(char * path) {
    lock_mutex(&working_file);
    for(int i=0; i<MAX_ENTRIES; i++) {
        if(str_cmp(path, file_table[i]->path)){
            free_mem(file_table[i]->entry);
            free_mem(file_table[i]);
            unlock_mutex(&working_file);
            return 0;
        }
    }
    unlock_mutex(&working_file);
    return 1;
}

inode_t get_file(char * path){
    for(int i=0; i<MAX_ENTRIES; i++){
        if(str_cmp(path, file_table[i]->path))
            return file_table[i];
    }
    return NULL;
}

int create_n_pipe(char * path){
    return create_file(path, N_PIPE);
}
