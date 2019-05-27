#ifndef _FILE_TABLE_H
#define _FILE_TABLE_H

#include <mem_manager.h>
#include <file_table.h>
#include <stdlib.h>

#define MAX_ENTRIES 256
#define MAX_PATH 30
#define INODE_BUFFER 4096

typedef enum {READ_ONLY, WRITE_ONLY} mode_t;
typedef enum {N_PIPE} file_t;

// inits the table with NULL
void init_table();
// create a "file" with type, if file already exist and is same time return the int, if is different type return -1, else return first empty inode
int create_file(char * path, file_t type);
// it creates a new file entry with path
int open_file(char * path);
// it recibes de position of file entry in array and delete it
int close(int pos);
#endif