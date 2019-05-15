#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#define CHAR_HEIGHT 16
#define CHAR_WIDTH 8
#define VIDEO_START_ADDRESS 0xB8000

#define STD_IN 0
#define STD_OUT 1
#define STD_ERR 2

#define OUT_BG_COLOR 0x000000
#define OUT_FG_COLOR 0xFFFFFF
#define ERR_BG_COLOR 0xFF0000
#define ERR_FG_COLOR 0x000000

#include <stdint.h>

typedef struct __attribute__((packed)) {
  uint16_t attributes;
  uint8_t win_A,win_B;
  uint16_t granularity;
  uint16_t winsize;
  uint16_t segment_A, segment_B;
  uint32_t real_fct_ptr;
  uint16_t pitch; // bytes per scanline

  uint16_t x_res, y_res;
  uint8_t w_char, y_char, planes, bpp, banks;
  uint8_t memory_model, bank_size, image_pages;
  uint8_t reserved0;

  uint8_t red_mask, red_position;
  uint8_t green_mask, green_position;
  uint8_t blue_mask, blue_position;
  uint8_t rsv_mask, rsv_position;
  uint8_t directcolor_attributes;

  uint32_t physbase;  // your LFB (Linear Framebuffer) address ;)
  uint32_t reserved1;
  uint16_t reserved2;
} mode_info_block;

//dibujar
void draw_pixel(int x,int y, int r, int g, int b);
void shadow_pixel(int x,int y, int r, int g, int b);


//escribir
void draw_char_w_front_and_back_color(int x, int y, char c, int foreground_color, int background_color);
void draw_free_char(char c, int foreground_color, int background_color);
void draw_free_string(char * string, int foreground_color, int background_color);
void draw_color_char(char c, int foreground_color);
void draw_char(char c);
void draw_string(char * string);
void draw_n_chars(char * string, int size);
void erase_character(void);
int number_of_digits(int n);
void draw_number(int n);
void erase_character(void);
void draw_n_chars_color(char * s, int index, int foreground_color, int background_color);
void draw_err_number(int n);
void draw_err_string(char * string);

//aux
void init_graphics(void);
void clear_screen(void);
void new_line(void);
void move_everything_up(void);
int number_of_digits(int n);
void load_vga_info(void);
void swap_buffers(void);
int get_x_res(void);
int get_y_res(void);
void clear_shadow_buffer(void);
void reset_cursor(void);


#endif
