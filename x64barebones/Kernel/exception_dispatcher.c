#include <graphics.h>

extern void print_all_registers();

void _cli();
void _sti();

typedef void (*func)();

static void dummy_func();
static void exception0();
static void exception6();
static void exception13();

func exception_functions[] = {exception0, dummy_func, dummy_func, dummy_func, dummy_func, dummy_func, exception6
,dummy_func,dummy_func,dummy_func,dummy_func,dummy_func,dummy_func,exception13};

void exception_dispatcher(int idx){
	//_cli();
	exception_functions[idx]();
	//_sti();
}

void dummy_func(){ // funcion dummy que no hace nada, se deja asi hasta que se implementen las proximas excepciones
	return;
}

void exception0(){
	draw_err_string("Excepcion 0: Division por cero detectada, registros: \n");
	print_all_registers();
}

void exception6(){
	draw_err_string("Excepcion 6: Codigo invalido, registros: \n");
	print_all_registers();
}

void exception13(){
	print_all_registers();
}
