#ifndef _TIME_H_
#define _TIME_H_

void timer_handler();
int ticks_elapsed();
int seconds_elapsed();
void time_wait(int n_ticks);
void _hlt();

#endif
