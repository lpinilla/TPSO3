//inicio .h
#include <time.h>
#include <stdint.h>
#include <graphics.h>
#include <lib.h>

#include <naiveConsole.h> //testing purposes

static void int_20();
static void int_21();
void keyboard_handler();

typedef void (*func)();
func f_pointers[] = {int_20, int_21};

//fin.h

void irq_dispatcher(uint64_t irq) {
	f_pointers[irq]();
	return;
}

void int_20() {
	timer_handler();
}

void int_21() {
	keyboard_handler();
}