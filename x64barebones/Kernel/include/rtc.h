#ifndef _RTC_H
#define _RTC_H

#include <stdint.h>
#include <interrupts.h>

#define RTC_REGISTER_SELECTOR 0x70
#define RTC_DATA 0x71

#define SECONDS_REGISTER 0x00
#define MINUTES_REGISTER 0x02
#define HOUR_REGISTER 0x04
#define WEEKDAY_REGISTER 0x06
#define DAY_OF_MONTH_REGISTER 0x07
#define MONTH_REGISTER 0x08
#define YEAR_REGISTER 0x09
#define CENTURY_REGISTER 0x32
#define STATUS_A_REGISTER 0x0A
#define STATUS_B_REGISTER 0x0B

void set_binary_time();
int get_time(int selector);

#endif
