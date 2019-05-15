
#include <rtc.h>

extern uint8_t io_read(uint16_t port);
extern void io_write(uint16_t port, uint8_t data);

#define SECONDS 0
#define MINUTES 1
#define HOUR 2
#define DAY_OF_MONTH 3
#define MONTH 4
#define YEAR 5

static int time_selector[] = {SECONDS_REGISTER,MINUTES_REGISTER,HOUR_REGISTER,DAY_OF_MONTH_REGISTER,MONTH_REGISTER,YEAR_REGISTER};

void set_binary_time(){
  io_write(RTC_REGISTER_SELECTOR, STATUS_B_REGISTER);
  uint8_t aux = io_read(RTC_DATA);
  aux = aux | 0x04 ; 
  io_write(RTC_DATA, aux);
}

int get_time(int selector){
  _cli();
  set_binary_time();
  io_write(RTC_REGISTER_SELECTOR, time_selector[selector]);
  int aux = io_read(RTC_DATA);
  _sti();
  return aux;
}
