#ifndef _OPENLG_H_
#define _OPENLG_H_

#include <syscall.h>
#include <utilities.h>

void draw_welcome_screen(void);
void draw_fill_square(int x, int y, unsigned char r, unsigned char g, unsigned   char b, unsigned char size);
void shadow_fill_square(int x, int y, unsigned char r, unsigned char g, unsigned   char b, unsigned char size);
void shadow_fill_rect(int x, int y, unsigned char r, unsigned char g, unsigned   char b,
                     unsigned char base, unsigned char height);
void draw_fill_rect(int x, int y, unsigned char r, unsigned char g, unsigned   char b,
                     unsigned char base, unsigned char height);
char get_key(void);


#endif
