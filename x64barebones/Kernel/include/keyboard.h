#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#include <stdint.h>

#define BUFFER_SIZE 80

char read_keyboard();
void erase_buffer();
void read_from_buffer(char * placeholder, int count);
char get_char();

#define KEYBOARD_STATUS_PORT    0x64
#define KEYBOARD_DATA_PORT      0x60


#define BREAK_CODE_DIF          128

#define LEFT_SHIFT              130
#define RIGHT_SHIFT             131
#define CAPS_LOCK               132
#define UP_ARROW                133
#define DOWN_ARROW              134
#define LEFT_ARROW              135
#define RIGHT_ARROW             136
#define TRUE                    1
#define FALSE                   0
#define MAX_BUFF_SIZE           512
#define EOF -1

#endif
