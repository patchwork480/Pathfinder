#include <pebble.h>
#include "pf_astro.h"
#include "pf_moon.h"


int16_t gmt_year;
int8_t gmt_mon;
int8_t gmt_mday;
int8_t gmt_hour;
int8_t gmt_min;
int8_t gmt_sec;
double gmt_decitime;
int gmt_juldate;


double hms_to_decimal (int hours, int minutes, int seconds) {
		double decimal =
				((double)hours)
				+ (((double)minutes) / PF_MINS_PER_HOUR)
				+ (((double)seconds) / PF_SECS_PER_HOUR);
		return (decimal / PF_HOURS_PER_DAY);
}


/**
 * SOURCE: https://en.wikipedia.org/wiki/Julian_day#Converting_Julian_or_Gregorian_calendar_date_to_Julian_day_number
 */
int julian_date (int year, int month, int day) {
		int a, y, m;
		a = (int)((14 - month) / 12);
		y = year + 4800 - a;
		m = month + (12 * a) - 3;
		int jul = day
				+ (int)(((153 * m) + 2) / 5)
				+ (365 * y)
				+ (int)(y / 4)
				- 32083;
		// Result is off by 14 (or 13) days
		return jul - 14; // FUDGE
}


int8_t moon_phase (int julday) {
		double decimal = (double)julday + 2.5;
		decimal = (decimal / PF_DAYS_PER_LUNAR_ORBIT);
		decimal = decimal - ((int)decimal);
		return (int8_t)(decimal * (double)PF_NUM_PHASES);
}


/* EOF */
