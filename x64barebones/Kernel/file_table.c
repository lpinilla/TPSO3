#include <file_table.h>
#include <mem_manager.h>

static file_entry_t[MAX_ENTRIES] file_table;

typedef struct file_entry {
    void * entry;
    int offset;
    mode_t mode;
} file_entryADT;

void init_table(){
    for(int i=0;i < MAX_ENTRIES; i++) {
        file_table[i]=NULL;
    }
}

int add_entry(void * entry, mode_t mode) {
    int found = -1;
    for(int i=0; i<MAX_ENTRIES && found!=-1; i++){
        if(file_table[i]==NULL){
            file_table[i] = mem_alloc(sizeof(file_entryADT));
            file_table[i]->offset=0;
            file_table[i]->mode=mode;
            found = i;
        }
    }
    return i;
}