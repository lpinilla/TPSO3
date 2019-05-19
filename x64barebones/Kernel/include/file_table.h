#ifndef _FILE_TABLE_H
#define _FILE_TABLE_H

#define MAX_ENTRIES 256
#define PIPE_BUFFER 4096

typedef enum {READ_ONLY, WRITE_ONLY} mode_t;

typedef struct file_entry * file_entry_t;


// inits the table with NULL
void init_table();
// add an entry to the  and return the number of the entry
int add_entry(void * entry, mode_t mode);

#endif