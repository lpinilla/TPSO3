#include <file_table.h>

typedef struct file_entryADT * file_entry_t;

typedef struct inodeADT * inode_t;

static file_entry_t file_table[MAX_ENTRIES];
static inode_t inode_table[MAX_ENTRIES];

typedef struct inodeADT {
    int offset;
    void * entry;
    char * path[MAX_PATH];
    file_t type;
}inodeADT;

typedef struct file_entryADT {
    mode_t mode;
    inode_t file;
} file_entryADT;

void init_tables(){
    for(int i=0;i < MAX_ENTRIES; i++) {
        file_table[i]=NULL;
        inode_table[i]=NULL;
    }
}

int create_file(char * path, file_t type) {
    int first_empty=-1;
    for(int i=0; i<MAX_ENTRIES;i ++) {
        if(first_empty==-1 && inode_table[i]==NULL){
            first_empty=i;
        }
        if(str_cmp(path),inode_table[i]->path){
            if(inode_table[i]->type==type)
                return i;
            return -1;
        }
    }
    if(first_empty!= -1) {
        inode_t aux = mem_alloc(sizeof(inodeADT));
        aux->offset=0;
        aux->entry= mem_alloc(INODE_BUFFER);
        str_cpy(aux->path, path);
        aux->type=type;
    }
    return first_empty;
}

int open_file(char * path){
    for(int i=0; i<MAX_ENTRIES; i++){
        if(str_cmp(path, inode_table[i]->path));
    }
}
int close(int pos){
    file_table[pos]=NULL;
}
