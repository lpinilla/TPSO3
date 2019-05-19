#include <file_table.h>

typedef enum mode_t {READ_ONLY, WRITE_ONLY} mode_t;

typedef struct file_entry {
    void * entry;
    int offset;
    mode_t mode;
} file_entry;