#include "include/time.h"

tm get_time(){
  tm time;
  time.seconds=sys_time(SECONDS_SELECTOR);
  time.minutes=sys_time(MINUTES_SELECTOR);
  time.hours=sys_time(HOURS_SELECTOR);
  time.day=sys_time(DAY_SELECTOR);
  time.month=sys_time(MONTH_SELECTOR);
  time.year=sys_time(YEAR_SELECTOR);
  print_time(time);
  return time;
}
void print_time(){
  print_f("La hora es: %d:%d:%d del %d/%d/%d del horario GMT \n",
    (sys_time(HOURS_SELECTOR) + 21) % 24, sys_time(MINUTES_SELECTOR), sys_time(SECONDS_SELECTOR),
    sys_time(DAY_SELECTOR),sys_time(MONTH_SELECTOR),sys_time(YEAR_SELECTOR));
}
