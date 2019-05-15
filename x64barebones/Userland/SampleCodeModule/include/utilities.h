#ifndef _UTILITIES_H
#define _UTILITIES_H

#include <stdarg.h>
#include <stdio.h>
#include <syscall.h>
#include <string.h>
#include <stdint.h>

#define MAX_BUFFER 100
#define TRUE 1
#define FALSE 0


int scan_f(const char * format, ...);
int print_f(const char * format, ...);
void print_string(char * s);
void put_char(char c);
char get_char();
void clear_console(void);
int get_digits(int number);
int get_number(char * buffer, int * pointer, int * index);
void print_number(int number);
int is_space(unsigned char c);
int is_digit(unsigned char c);
int is_alpha(unsigned char c);
int is_symbol(unsigned char c);

uint64_t * shell();

#endif
