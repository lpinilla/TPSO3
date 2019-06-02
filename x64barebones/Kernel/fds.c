#include <fds.h>

typedef struct fd_infoADT * fd_info_t;
typedef struct inodeADT * inode_t;


static inode_t file_table[MAX_ENTRIES];

typedef struct inodeADT {
    char * path[MAX_PATH];
    int offset;
    void * entry;
} inodeADT;

typedef struct fd_infoADT {
    inode_t file;
    fd_t type;
}fd_infoADT;

void init_tables(){
    for(int i=0;i < MAX_ENTRIES; i++) {
        file_table[i]=NULL;
    }
}

int create_file(char * path) {
    int first_empty=-1;
    for(int i=0; i<MAX_ENTRIES;i ++) {
        if(first_empty==-1 && file_table[i]==NULL){
            first_empty=i;
        }
        if(str_cmp(path),file_table[i]->path){
            return i;
        }
    }
    if(first_empty!= -1) {
        inode_t aux = mem_alloc(sizeof(inodeADT));
        aux->offset=0;
        aux->entry= mem_alloc(INODE_BUFFER);
        str_cpy(aux->path, path);
        file_table[first_empty] = aux;
    }
    return first_empty;
}

int delete_file(char * path) {
    for(int i=0; i<MAX_ENTRIES; i++) {
        if(str_cmp(path, file_table[i]->path)){
            free_mem(file_table[i]->entry);
            free_mem(file_table[i]);
            return 0;
        }
    }
    return 1;
}
