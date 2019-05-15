#ifndef LIB_H
#define LIB_H

#include <stdint.h>
#include <stddef.h>

void * memset(void * destination, int32_t character, uint64_t length);
void * memcpy(void * destination, const void * source, uint64_t length);
int str_cpy(const char* from, char* destination);
int str_len(char * msg);
int str_cmp(char * s1, char * s2);


char *cpuVendor(char *result);


#endif