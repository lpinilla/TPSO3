#include <file_table.h>
/*
typedef struct file_entryADT * file_entry_t;

static file_entry_t file_table[MAX_ENTRIES];

typedef struct file_entryADT {
    char * path[MAX_PATH];
    void * entry;
    int offset;
    mode_t mode;
} file_entryADT;

void init_table(){
    for(int i=0;i < MAX_ENTRIES; i++) {
        file_table[i]=NULL;
    }
}

int add_entry(char * path, void * entry, mode_t mode) {
    int found = -1;
    for(int i=0; i<MAX_ENTRIES && found!=-1; i++){
        if(file_table[i]==NULL){
            file_table[i] = mem_alloc(sizeof(file_entryADT));
            file_table[i]->offset=0;
            file_table[i]->mode=mode;
            str_cpy(file_table[i]->path, path);
            found = i;
        }
    }
    return found;
}
*/