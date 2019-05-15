#ifndef _TIME_H
#define _TIME_H

#include <syscall.h>
#include <utilities.h>

#define SECONDS_SELECTOR 0
#define MINUTES_SELECTOR 1
#define HOURS_SELECTOR 2
#define DAY_SELECTOR 3
#define MONTH_SELECTOR 4
#define YEAR_SELECTOR 5


typedef struct{
  int seconds;
  int minutes;
  int hours;
  int day;
  int month;
  int year;
}tm;

void print_time();
tm get_time();

#endif
