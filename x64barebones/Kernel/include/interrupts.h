#ifndef INTERRUPS_H_
#define INTERRUPS_H_

#include <stdint.h>

void _irq00_handler(void);
void _irq01_handler(void);
/*void _irq02Handler(void);
void _irq03Handler(void);
void _irq04Handler(void);
void _irq05Handler(void);*/

void _exception0_handler(void);
void _exception6_handler(void);
void _exception13_handler(void);
void _syscall_handler(void);

void _cli(void);

void _sti(void);

void _hlt(void);

void pic_master_mask(uint8_t mask);

void pic_slave_mask(uint8_t mask);

//Termina la ejecución de la cpu.
void haltcpu(void);

void _change_process(uint64_t stack_pointer);
void _context_switch_process(void);
void _context_switch_interrupt(void);

#endif /* INTERRUPS_H_ */
