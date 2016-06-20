#pragma once


#define SECS_PER_MIN	(60.0)
#define MINS_PER_HOUR	(60.0)
#define HOURS_PER_DAY	(24.0)
#define MINS_PER_DAY	(MINS_PER_HOUR * HOURS_PER_DAY)
#define SECS_PER_HOUR	(SECS_PER_MIN * MINS_PER_HOUR)
#define SECS_PER_DAY	(SECS_PER_MIN * MINS_PER_HOUR * HOURS_PER_DAY)


extern int gmt_year;
extern int gmt_mon;
extern int gmt_mday;
extern int gmt_hour;
extern int gmt_min;
extern int gmt_sec;
extern int gmt_juldate;


extern double hms_to_decimal (int hours, int minutes, int seconds);
extern int julian_date (int year, int month, int day);
extern int moon_phase (int julday);


/* EOF */
