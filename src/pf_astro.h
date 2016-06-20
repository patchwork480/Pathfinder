#pragma once


#define PF_SECS_PER_MIN		(60.0)
#define PF_MINS_PER_HOUR	(60.0)
#define PF_HOURS_PER_DAY	(24.0)
#define PF_MINS_PER_DAY		(PF_MINS_PER_HOUR * PF_HOURS_PER_DAY)
#define PF_SECS_PER_HOUR	(PF_SECS_PER_MIN * PF_MINS_PER_HOUR)
#define PF_SECS_PER_DAY		(PF_SECS_PER_MIN * PF_MINS_PER_HOUR * PF_HOURS_PER_DAY)


extern int16_t gmt_year;
extern int8_t gmt_mon;
extern int8_t gmt_mday;
extern int8_t gmt_hour;
extern int8_t gmt_min;
extern int8_t gmt_sec;
extern double gmt_decitime;
extern uint32_t gmt_juldate;


extern double hms_to_decimal (int8_t hours, int8_t minutes, int8_t seconds);
extern uint32_t julian_date (int16_t year, int8_t month, int8_t day);
extern uint8_t moon_phase (uint32_t julday);


/* EOF */
