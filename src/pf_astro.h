#pragma once


#define PF_SECS_PER_MIN		(60.0)
#define PF_MINS_PER_HOUR	(60.0)
#define PF_HOURS_PER_DAY	(24.0)
#define PF_MINS_PER_DAY		(PF_MINS_PER_HOUR * PF_HOURS_PER_DAY)
#define PF_SECS_PER_HOUR	(PF_SECS_PER_MIN * PF_MINS_PER_HOUR)
#define PF_SECS_PER_DAY		(PF_SECS_PER_MIN * PF_MINS_PER_HOUR * PF_HOURS_PER_DAY)

#define PF_DAYS_PER_LUNAR_ORBIT	(29.53)


extern int16_t gmt_year;
extern int8_t gmt_mon;
extern int8_t gmt_mday;
extern int8_t gmt_hour;
extern int8_t gmt_min;
extern int8_t gmt_sec;
extern double gmt_decitime;
extern int gmt_juldate;


extern double hms_to_decimal (int hours, int minutes, int seconds);
extern int julian_date (int year, int month, int day);
extern int8_t moon_phase (int julday, double decitime);


/* EOF */
