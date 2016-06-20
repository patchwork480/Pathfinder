#include <pebble.h>
#include "pf_astro.h"
#include "pf_moon.h"

int pf_juldate;


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
