#include "include/shell.h"

static func execute_command[]={invalid_command,play_pong,show_time,shutdown,make_beep,make_div,ayuda,try_scan_f,try_print_f,try_invalid_function,
try_processes, ps, try_mutex, try_semaphore, try_alloc, try_ipc, run_prodcons, try_pipe, try_process_args, run_philo};

const char * commands[] = {"pong", "time","shutdown","beep","div","help","scan","print","invalid", "processes_test", "ps",
"mutex_test", "semaphore_test", "alloc_test", "ipc_test", "prodcons", "pipe", "process_args_test","philo"};

static int command_handler(char * command);

uint64_t * shell(void){
	draw_welcome_screen();

	int command_id=INVALID_COMMAND;
	print_user();
	int i=0;
	char command[MAX_LENGTH];
	char c;
	while(command_id!=SHUTDOWN_COMMAND){
		c=get_char();
		if(c=='\b' && i!=0){  // si es un backspace y no estamos al principio de linea, volvemos el indice hacia atras
			put_char(c);
			i--;
		}
		else if(c=='\n'){ // si es una new line entramos
			put_char(c); // imprimimos la new line
			if(i<MAX_LENGTH){  // si nuestro indice es menor al de comando maximo significa que puede ser un comando valido
				command[i]=0;  // le ponemos al final un 0 para saber donde termina
				command_id=command_handler(command); // lo mandamos al handler para que se encargue de decirnos que comando es
				execute_command[command_id](); // ejecutamos el comando
			}
			else // este es el caso que entramos a una new line y el comando es mas largo que MAX LENGHT
				invalid_command();  // mandamos un mensaje de comando invalido
			i=0; // reseteamos el contador a 0 ya que empezamos una nueva linea
			if(command_id!=SHUTDOWN_COMMAND)
					print_user();
		}
		else if (c!='\b' && (is_alpha(c) || is_digit(c) || is_symbol(c) || is_space(c))){ // este caso es el generico, sacamos el caso si es un backspace porque no hacemos nada
			put_char(c);
			if(i<MAX_LENGTH) // si el indice todavia es menor que el maximo seguimos poniendolo en el comando
				command[i]=c;
			i++; //subimos el indice OJO QUE ES POSIBLE QUE HAYA OVERFLOW SI EL INDICE ES MUY GRANDE(SE ESCRIBE UN COMANDO ENORME MAS GRANDE QUE INT)
		}
	}
	return (uint64_t *) RETURN_ADRESS;
}
static int command_handler(char * command){
	for(int i=0; i<COMMANDS; i++){
		if(str_cmp(command, commands[i])==0){
			return i+1;
		}
	}
	return INVALID_COMMAND;

}

void invalid_command(){
	print_f("Invalid command \n");
}

void shutdown(){
	print_f("Thank you, powering off \n");
	sys_sleep(10);
	sys_clear_console();
}
void play_pong(){
	print_f("Aca jugamos al pong \n");
	init_game();
}
void show_time(){
	print_time();
}
void print_user(){
	while(!sys_is_current_process_foreground()){ }
	print_f("SO@ITBA:");
}

void make_beep(){
	sys_beep();
}
void try_print_f(){
	char s[100];
	scan_f("%s",s);
	print_f("%s \n", s);
}

void try_processes(){
	process_test();
}

void try_mutex(){
	mutex_test();
}

void try_semaphore(){
	semaphore_test();
}

void try_alloc(){
	mem_manager_test();
}

void try_ipc(){
	ipc_test();
}

void run_prodcons(){
	prodcons();
}

void run_philo(){
	philosophers();
}

void try_process_args(){
	process_args_test();
}

void ps(){
	sys_create_process(sys_print_all_procceses, "ps", FOREGROUND);
}

void make_div(){
	sys_create_process(make_div_process, "Div Exception", FOREGROUND);
}

void make_div_process(){
	int n = 1;
	int b = 0;
	int c = n/b;
	c--;
}

void try_scan_f(){
	char * aux[20];
	int a;
	scan_f("Hola %d %s", &a,aux);
	print_f("%d %s \n",a,aux);
}

void try_invalid_function(){
	sys_create_process(try_invalid_function_process, "Invalid Code Exception", FOREGROUND);
}

void try_invalid_function_process(){
	uint64_t asd= 0xFFFFFFFFFFFF; //claramente una instruccion no valida
	uint64_t * aux = &asd;
	((func)aux)();
}

void try_pipe(){
	pipe_creation_test();
}

void ayuda(){
	print_f("\nBienvenido a nuestra shell \n");
	print_f("\nLos comandos disponibles son los siguientes \n \n \n");
	print_f("beep - Usa el pcspeaker para hacer sonido \n");
	print_f("pong - Ejecuta el juego pong \n");
	print_f("div - Levanta una excepcion de division por 0 \n");
	print_f("invalid - Levanta una excepcion de codigo invalido \n");
	print_f("time - Devuelve la hora en formato GMT \n");
	print_f("shutdown - Apaga el SO \n");
	print_f("scan - prueba el comando de scan_f con el formato \"Hola %%d %%s\" e imprime el resultado  \n");
	print_f("processes_test - prueba la creacion, borrado y listado de procesos \n");
	print_f("mutex_test - prueba la funcion mutex \n");
	print_f("semaphore_test - prueba los semáforos \n");
	print_f("alloc_test - prueba el memory manager \n");
	print_f("process_args_test - prueba la creacion de un proceso con argumentos \n");
	print_f("ipc_test - prueba los ipc \n");
	print_f("prodcons - ejecuta el proceso prodcons \n");
	print_f("philo - ejecuta el proceso dining philosophers\n");
	print_f("print - prueba el comando de print_f con el formato \"%%s \\n \" \n\n\n");

	return;
}
