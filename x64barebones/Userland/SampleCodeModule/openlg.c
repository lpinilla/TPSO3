#include <openlg.h>

char * title[9] = {"       ##      ##                           ",
                   "       ##      ##                   TP DE SO",
                   "     ##############                         ",
                   "   ####  ######  ####                       ",
                   " ######################                     ",
                   " ##  ##############  ##                     ",
                   " ##  ##          ##  ##                     ",
                   "       ####  ####                           "};


void draw_welcome_screen(){
  sys_reset_cursor();
  //mensaje de bienvenida
  for(int i = 0; i < 9; i++){
    print_f(title[i]);
    sys_new_line();
  }
  print_f("Escriba 'help' para ver los comandos disponibles \n");
    for(int i = 0; i < 36; i++){
        sys_new_line();
    }
}


void shadow_fill_square(int x, int y, unsigned char r, unsigned char g, unsigned   char b, unsigned char size) {
    for (int i = y; i < size + y; i++) {
        for (int j = x; j < size + x; j++) {
            sys_shadow_pixel(j,i, r,g,b);
        }
    }
}

void draw_fill_square(int x, int y, unsigned char r, unsigned char g, unsigned   char b, unsigned char size) {
    for (int i = y; i < size + y; i++) {
        for (int j = x; j < size + x; j++) {
            sys_draw_pixel(j,i, r,g,b);
        }
    }
}

void draw_fill_rect_triangle(int x, int y, unsigned char r, unsigned char g, unsigned char b, unsigned char height){
    for(int i = y, t = 0; i < (height + y); i++, t++){
        for(int j = x; j < (x+t); j++){
            sys_draw_pixel(j,i,r,g,b);
        }
    }
}

void draw_fill_rect_triangle_rot_90(int x, int y, unsigned char r, unsigned char g, unsigned char b, unsigned char height){
    for (int i = y, t = height; i < height + y; i++, t--) {
        for (int j = x; j < (x + t); j++) {
            sys_draw_pixel(j,i, r,g,b);
        }
    }
}

void draw_fill_rect_triangle_rot_180(int x, int y, unsigned char r, unsigned char g, unsigned char b, unsigned char height){
    for (int i = y, t = 0; i < height + y; i++, t++) {
        for (int j = x; j < (x + height -t); j++) {
            sys_draw_pixel(j,i, r,g,b);
        }
        x++;
    }
}

void draw_fill_rect_triangle_rot_270(int x, int y, unsigned char r, unsigned char g, unsigned char b, unsigned char height){
    for (int i = y, t = 0; i < height + y; i++, t++) {
        for (int j = x + height - t; j < (x + height); j++) {
            sys_draw_pixel(j,i, r,g,b);
        }
    }
}

void draw_fill_iso_triangle_rot_180(int x, int y, unsigned char r, unsigned char g, unsigned char b, unsigned char height){
    for (int i = y, t = height; i < height + y; i++, t--) {
        for (int j = (x+ height - t); j < (x + t); j++) {
            sys_draw_pixel(j,i, r,g,b);
        }
    }
}

void draw_fill_rect(int x, int y, unsigned char r, unsigned char g, unsigned   char b,
                     unsigned char base, unsigned char height) {
    for (int i = y; i < height + y; i++) {
        for (int j = x; j < base + x; j++) {
            sys_draw_pixel(j,i, r,g,b);
        }
    }
}

void shadow_fill_rect(int x, int y, unsigned char r, unsigned char g, unsigned   char b,
                     unsigned char base, unsigned char height) {
    for (int i = y; i < height + y; i++) {
        for (int j = x; j < base + x; j++) {
            sys_shadow_pixel(j,i, r,g,b);
        }
    }
}

void swap_buffers(){
	sys_swap_buffers();
}

char get_key(){
    char c;
    sys_read(&c, 1);
    return c;
}
