#ifndef _FILE_TABLE_H
#define _FILE_TABLE_H

#include <mem_manager.h>
#include <stdlib.h>
#include <mutex.h>

#define MAX_ENTRIES 256
#define MAX_PATH 30
#define INODE_BUFFER 4096

typedef enum {N_PIPE} file_t;
typedef struct inodeADT * inode_t;

// inits the table with NULL
void init_table();
// create a "file" with path, if path already exist it doesnt create it
int create_file(char * path, file_t type);
// it deletes file with path "path"
int delete_file(char * path);
// wrapper for creating named pipe
int create_n_pipe(char * path);
#endif