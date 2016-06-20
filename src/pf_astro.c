#include <pebble.h>
#include "pf_astro.h"
#include "pf_moon.h"


int8_t gmt_year;
int8_t gmt_mon;
int8_t gmt_mday;
int16_t gmt_hour;
int8_t gmt_min;
int8_t gmt_sec;
double gmt_decitime;
uint32_t gmt_juldate;


double hms_to_decimal (int8_t hours, int8_t minutes, int8_t seconds) {
		double decimal =
				((double)hours)
				+ (((double)minutes) / PF_MINS_PER_HOUR)
				+ (((double)seconds) / PF_SECS_PER_HOUR);
		return (decimal / PF_HOURS_PER_DAY);
}


uint32_t julian_date (int16_t year, int8_t month, int8_t day) {
		int8_t a, y, m;
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
		uint32_t jul = day
				+ (uint32_t)(((153 * m) + 2) / 5)
				+ (365 * y)
				+ (uint32_t)(y / 4)
				- 32083;
		return jul;
}


int8_t moon_phase (uint32_t julday) {
		return (int8_t)(julday % PF_NUM_PHASES);
}


/* EOF */
