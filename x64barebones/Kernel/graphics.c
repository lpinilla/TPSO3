#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "./include/graphics.h"
#include "./include/bitmap.h"
#include "./include/glyphs.h"
#include "./include/scheduler.h"
#include "./include/process.h"

//resolucion 1024*768

//-----------------Variables locales
unsigned char * screen; //se usa para no estar creandolo todo el tiempo
static char shadow_buffer[64] = {'0'}; //64k = 320 * 200
int x_cursor, y_cursor;
mode_info_block* info_block;


void reset_cursor(){
  clear_screen();
  new_line();
  new_line();
  x_cursor = 0;
  y_cursor = CHAR_HEIGHT;
}


//-----------------------------------------------------------------ESCRITURA

//se puede especificar color de frente y de fondo
void draw_char_w_front_and_back_color(int x, int y, char c, int foreground_color, int background_color){
  if(!is_current_process_foreground()){
    return;
  }
  if(c=='\n')
    return new_line();
  if(c=='\b')
    return erase_character();
  if(x_cursor >= get_x_res()){
    x_cursor = 0;
    if(y_cursor >= get_y_res() - CHAR_HEIGHT){
      move_everything_up();
    }else{
      y_cursor += CHAR_HEIGHT;
    }
  }
  for(int i = 0; i < CHAR_HEIGHT; i++){
    for(int j = 0; j < CHAR_WIDTH; j++){
      if(*(&glyphs[(c-31) * CHAR_HEIGHT] + i * sizeof(uint8_t)) & 1<<j){
        draw_pixel(CHAR_WIDTH -1 -j + x_cursor, i + y_cursor,
                  (foreground_color >> 16) & 255, (foreground_color >> 8) & 255, foreground_color & 255);
      }else{
        draw_pixel(CHAR_WIDTH -1 -j + x_cursor, i + y_cursor,
                  (background_color >> 16) & 255, (background_color >> 8) & 255, background_color & 255); //necesito esto para poder borrar
      }
    }
  }
  x_cursor += CHAR_WIDTH;
}

//vos le especificas color de frente y de fondo
void draw_free_char(char c, int foreground_color, int background_color){
  draw_char_w_front_and_back_color(x_cursor, y_cursor, c, foreground_color, background_color);
}

//vos le especificas los colores de frente y de fondo
void draw_free_string(char * string, int foreground_color, int background_color){
  int i = 0;
  while(*(string + i)){
    draw_free_char(string[i++], foreground_color, background_color);
  }
}

//vos solo elegis color de frente (fondo negro)
void draw_color_char(char c, int foreground_color){
  draw_char_w_front_and_back_color(x_cursor, y_cursor, c, foreground_color, 0x0);
}

//clasico, fondo negro letras blancas
void draw_char(char c){
  draw_free_char(c, 0xFFFFFF, 0x0);
}

void draw_string(char * string){
  draw_free_string(string, 0xFFFFFF, 0x0);
}
void draw_n_chars(char * s, int index){
  for(int i = 0 ; i< index; i++){
    draw_char(s[i]);
  }
}
void draw_n_chars_color(char * s , int index, int foreground_color, int background_color){
  for(int i=0; i<index; i++){
    draw_free_char(s[i], foreground_color, background_color);
  }
}

//testeable
int number_of_digits(int n){
  if(n == 0)  return 0;
  return 1 + number_of_digits(n/10);
}

//verificar los límites
void erase_character(){
  if(x_cursor == 0){
    if(y_cursor == 0){
      draw_color_char(' ', 0xFFFFFF);
    }else{
      y_cursor -= CHAR_HEIGHT;
      x_cursor = get_x_res() - CHAR_WIDTH;
      draw_color_char(' ', 0xFFFFFF);
    }
  }else{
    x_cursor -= CHAR_WIDTH;
    draw_color_char(' ', 0xFFFFFF);
  }
  x_cursor -= CHAR_WIDTH;
}

//testeable
void draw_number(int n){
  if (n == 0){
   draw_char('0');
   return;
  }
  int count = number_of_digits(n);
  int array[count];
  for(int i = 0; i < count; i++){
    array[count-1-i] = n % 10;
    n /= 10;
  }
  for(int i = 0; i < count; i++){
    draw_char(array[i] + '0');
  }
}
void draw_err_number(int n){
  if (n == 0){
   draw_free_char('0',ERR_FG_COLOR,ERR_BG_COLOR);
   return;
  }
  int count = number_of_digits(n);
  int array[count];
  for(int i = 0; i < count; i++){
    array[count-1-i] = n % 10;
    n /= 10;
  }
  for(int i = 0; i < count; i++){
    draw_free_char(array[i] + '0',ERR_FG_COLOR,ERR_BG_COLOR);
  }
}
void draw_err_string(char * string){
  draw_free_string(string,ERR_FG_COLOR, ERR_BG_COLOR);
}

void new_line(){
  if(!is_current_process_foreground()){
    return;
  }
  if(y_cursor != (get_y_res()-CHAR_HEIGHT)){ //tal vez esto es lo que escribe abajo de la pantalla
    y_cursor += CHAR_HEIGHT;
  }else{
    move_everything_up();
  }
  x_cursor = 0;
}

//-------------------------------------HARDWARE PURAS

void init_graphics(){
  info_block = (mode_info_block*)0x0000000000005C00;
}

void draw_pixel(int x, int y, int r, int g, int b) {
	screen = (unsigned char *) ((uint64_t) info_block->physbase + x*info_block->bpp / 8 + (int) y*info_block->pitch);
  screen[0] = b;              // BLUE
  screen[1] = g;              // GREEN
  screen[2] = r;              // RED
}

void shadow_pixel(int x, int y, int r, int g, int b) {
  screen = (unsigned char *) ((uint64_t) shadow_buffer + x*info_block->bpp / 8 + (int) y*info_block->pitch);
  screen[0] = b;              // BLUE
  screen[1] = g;              // GREEN
  screen[2] = r;              // RED
}


//limpiar la pantalla principal
void clear_screen(){
  memset((char *) ((uint64_t) info_block->physbase), 0, info_block->y_res * info_block->x_res * info_block->bpp/8);
  x_cursor = 0;
  y_cursor = CHAR_HEIGHT;
  //memset(shadow_buffer, 0x0, sizeof(shadow_buffer));
  //swap_buffers();
}

//limpiar todo el buffer auxiliar
void clear_shadow_buffer(){
  memset(shadow_buffer, 0x0, sizeof(shadow_buffer));
}


void move_everything_up(){
  memcpy((char *) ((uint64_t) info_block->physbase), (char *) ((uint64_t) info_block->physbase + info_block->pitch * CHAR_HEIGHT),
           (info_block->x_res * info_block->bpp / 8 * CHAR_WIDTH * 2) * info_block->y_res / CHAR_HEIGHT);
}

//si no anda bien, copiar la cantidad de bytes del move_everything_up
void swap_buffers(){
  memcpy((char *) ((uint64_t) info_block->physbase - info_block->pitch * CHAR_HEIGHT), (char *) shadow_buffer,
         (uint64_t) info_block->x_res * info_block->y_res * info_block->bpp/8);
}


int get_x_res(){
  return info_block->x_res;
}

int get_y_res(){
  return info_block->y_res;
}
