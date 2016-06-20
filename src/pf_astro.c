#include <pebble.h>
#include "pf_astro.h"
#include "pf_moon.h"


int gmt_juldate;
int gmt_year;
int gmt_mon;
int gmt_mday;
int gmt_hour;
int gmt_min;
int gmt_sec;


double hms_to_decimal (int hours, int minutes, int seconds) {
		double decimal =
				((double)hours)
				+ (((double)minutes) / MINS_PER_HOUR)
				+ (((double)seconds) / SECS_PER_HOUR);
		return (decimal / HOURS_PER_DAY);
}


int julian_date (int year, int month, int day) {
		int a, y, m;
		a = (14 - month) / 12;
		y = year + 4800 - a;
		m = month + (12 * a) - 3;
		/*int grg = day
				+ (((153 * m) + 2) / 5)
				+ (365 * y)
				+ (y / 4)
				- (y / 100)
				+ (y / 400)
				- 32045;*/
		int jul = day
				+ (((153 * m) + 2) / 5)
				+ (365 * y)
				+ (y / 4)
				- 32083;
		return jul;
}


int moon_phase (int julday) {
		return julday % PF_NUM_PHASES;
}


/* EOF */
