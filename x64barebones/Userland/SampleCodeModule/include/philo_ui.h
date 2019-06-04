#ifndef _PHILO_UI_
#define _PHILO_UI_

#include <openlg.h>
#include <philosophers.h>

#define PHILO_SIZE 32
#define TABLE_HEIGHT 200
#define TABLE_WIDTH 250
#define SPACE_PHILO_TABLE 50
#define TABLE_X 250
#define TABLE_Y 300


typedef struct{
    char * name;
    int r,g,b;
}t_color;

void draw_table();
void draw_upper_side(int x, int y, int start_index);
void draw_lower_side(int x, int y, int start_index);
void draw_right_side(int x, int y, int start_index);

void print_ui();

#endif
