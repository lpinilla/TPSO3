#include <philo_ui.h>

t_color colors[5] = {{.name = "brown", .r = 0x87, .g = 0X87, .b = 0x0},
                     {.name = "green", .r =0x95, .g = 0xFF, .b = 0x175},    //thiking
                     {.name = "blue", .r = 0x95, .g = 0x175, .b = 0xFF},    //eating
                     {.name = "red", .r = 0x175, .g = 0x0, .b = 0x0}};      //hungry



void print_ui(){
    print_f("Press 'c' to create a new philosopher.                                                     pensando\n");
    print_f("Press 'd' to delete one philosopher.                                                       comiendo\n");
    print_f("Press 'q' to quit dining philosophers                                                      hambriento\n");    
    draw_fill_square(820, 15, colors[1].r, colors[1].g, colors[1].b, 15);
    draw_fill_square(820, 32, colors[2].r, colors[2].g, colors[2].b, 15);
    draw_fill_square(820, 49, colors[3].r, colors[3].g, colors[3].b, 15);
    while(1){
        
        sys_reset_x_cursor();
        print_f("Number of philosophers: %d",ph_count);
        
        //print_ph_state();
        //la mesa
        draw_table();

        //borde superior
        draw_upper_side(TABLE_X, TABLE_Y - SPACE_PHILO_TABLE, 0);

        //borde derecho
        draw_right_side(TABLE_X+ TABLE_WIDTH * 1.7f+PHILO_SIZE,TABLE_Y ,(MAXPHILO/4));

        //borde inferior
        draw_lower_side(TABLE_X + TABLE_WIDTH * 1.7f ,TABLE_Y + TABLE_HEIGHT + SPACE_PHILO_TABLE / 2, (2 * (MAXPHILO / 4)));
        sys_sleep(1);
    }
    //borde izquierdo
}

void draw_table(){
    draw_fill_rect(TABLE_X,TABLE_Y, colors[0].r, colors[0].g, colors[0].b, TABLE_WIDTH,TABLE_HEIGHT);
    draw_fill_rect(TABLE_Y + TABLE_Y / 2,TABLE_Y, colors[0].r, colors[0].g, colors[0].b, TABLE_WIDTH,TABLE_HEIGHT);
}

void draw_upper_side(int x, int y, int start_index){
    t_color aux;
    for(int i = 0; i < MAXPHILO / 4; i++){
    if( (i + start_index) >= ph_count) break;
        switch(state[i]){
            case THINKING:
                aux = colors[1];
                break;
            case EATING:
                aux = colors[2];
                break;
            case HUNGRY:
                aux = colors[3];
        }
        draw_fill_square(x + i * 3.3f * PHILO_SIZE, y, aux.r, aux.g, aux.b, PHILO_SIZE);
    }
}

void draw_lower_side(int x, int y, int start_index){
    t_color aux;
    for(int i = 0; i < MAXPHILO / 4; i++){
    if( (i + start_index) >= ph_count) break;
        switch(state[i]){
            case THINKING:
                aux = colors[1];
                break;
            case EATING:
                aux = colors[2];
                break;
            case HUNGRY:
                aux = colors[3];
        }
        draw_fill_square(x - i * 3.3f * PHILO_SIZE, y, aux.r, aux.g, aux.b, PHILO_SIZE);
    }
}

void draw_right_side(int x, int y, int start_index){
    t_color aux;
    for(int i = 0; i < MAXPHILO / 4; i++){
    if( (i + start_index) >= ph_count) break;
    
        switch(state[i]){
            case THINKING:
                aux = colors[1];
                break;
            case EATING:
                aux = colors[2];
                break;
            case HUNGRY:
                aux = colors[3];
        }
    draw_fill_square(x+SPACE_PHILO_TABLE , y+ i * 1.3f * PHILO_SIZE, aux.r, aux.g, aux.b, PHILO_SIZE);
    }
}