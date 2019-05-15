#include <syscall_dispacher.h>

// usamos la convencion de linux y c para los parametros de las syscalls
uint64_t syscall_dispacher(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9) {
  switch(rdi){
      case READ:
        read(rsi,(char *)rdx,rcx);
        break;
      case WRITE:
        write(rsi,(char *) rdx, rcx);
        break;
      case DRAW_PIXEL:
        draw_pixel(rsi,rdx,rcx,r8,r9);
        break;
      case X_RES:
        return get_x_res();
      case Y_RES:
        return get_y_res();
      case CLEAR_SCREEN:
        clear_screen();
        break;
      case TIME:
        return get_time(rsi);
      case SHADOW_PIXEL:
        shadow_pixel(rsi, rdx, rcx, r8, r9);
        break;
      case MOVE_EVERYTHING_UP:
        move_everything_up();
        break;
      case SWAP_BUFFERS:
        swap_buffers();
        break;
      case CLEAR_SHADOW_BUFFER:
        clear_shadow_buffer();
        break;
      case INIT_GRAPHICS:
        init_graphics();
        break;
      case COLOR_WRITE:
        color_write((char *)rsi, rdx, rcx,r8);
        break;
      case RESET_CURSOR:
        reset_cursor();
        break;
      case BEEP:
        beep();
        break;
      case SLEEP:
        time_wait(rsi);
        break;
      case NEW_LINE:
        new_line();
        break;
      case MY_MALLOC:
        return (uint64_t) mem_alloc(rsi); //VERRR!!
      case MY_FREE:
        free_mem((void*) rsi);
        break;
      case MEM_BASE:
        return (uint64_t) return_memory_base();
      case NEW_PROCESS:
        return new_process(rsi, (char *)rdx, (int)rcx, 1);
      case KILL_PROCESS:
        set_state_id((size_t)rsi, P_TERMINATE);
        break;
      case LIST_PROCESSES:
        print_current_processes();
        break;
      case GET_STATE_PROCESS:
        return (uint64_t)get_state_id((size_t)rsi);
      case SEM_OPEN:
        return (uint64_t)my_sem_open((char *)rsi);
      case SEM_CLOSE:
        return (uint64_t)my_sem_close((int)rsi);
      case SEM_POST:
        return (uint64_t)my_sem_post((int)rsi);
      case SEM_WAIT:
        return (uint64_t)my_sem_wait((int)rsi);
      case MUTEX_LOCK:
        lock_mutex((void *)rsi);
        break;
      case MUTEX_UNLOCK:
        unlock_mutex((void *)rsi);
        break;
      case SET_FOREGROUND_PROCESS:
        set_foreground_process((size_t)rsi);
        break;
      case IS_CURRENT_PROCESS_FOREGROUND:
        return (uint64_t)is_current_process_foreground();
      case PRINT_MEM_LIST:
        print_list();  
        break;
      case IPC_READ:
        my_read((int)rsi, (char *)rdx);
        break;
      case IPC_WRITE:
        my_write((char *)rsi, (int)rdx);
        break;
      case NEW_PROCESS_PRIORITY:
        return (uint64_t)new_process(rsi, (char *)rdx, (int)rcx, (int)r8);
  }
	return 0;
}

void color_write(char * pointer, int size, int foreground_color, int background_color){
  draw_n_chars_color(pointer,size,foreground_color,background_color);
}

int read(int fd, char * pointer, int size) {
  char c;
  for(int i=0; i<size; i++){
    c=get_char();
    if(c==EOF){
      pointer[i]=c;
      return i;
    }
    pointer[i]=c;
  }
  return size;
}

void write(int fd, char * pointer, int size) {
  // por ahora solo implementamos por salida estandar (en nuestro caso pantalla), y el numero de salida estandar es 1
	if(fd==STD_OUT)
    draw_n_chars_color(pointer,size, OUT_FG_COLOR, OUT_BG_COLOR);
  if(fd==STD_ERR)
    draw_n_chars_color(pointer,size,ERR_FG_COLOR, OUT_BG_COLOR);
  else
    return;
}

size_t new_process(uint64_t process_start, char * process_name, int foreground, int priority){
  process_t new_process = create_process(process_start, process_name, priority);
  if(foreground == 1){
    set_foreground_process(get_pid(new_process));
  }
  run_process(new_process);
  return get_pid(new_process);
}