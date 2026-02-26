#ifndef TIME_H
#define TIME_H

typedef struct {
uint8_t second;
uint8_t minute;
uint8_t hour;
uint8_t date_of_the_month;
uint8_t month;
uint8_t year;
} t_rtc_time;
	
	
errno_t fw_get_time(struct t_rtc_time *t);


#endif
