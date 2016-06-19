#include <pebble.h>
#include "pf_util.h"


char *strupr (char *str) {
		char *s;
		for(s = str; *s; s++) {
				if(('a' <= *s) && (*s <= 'z')) {
						*s = 'A' + (*s - 'a');
				}
		}
		return str;
}


bool DIGIT_SEGS[PF_NUM_DIGITS][PF_NUM_SEGMENTS] = {
		{  true,  true,  true,  true,  true,  true, false },
		{ false,  true,  true, false, false, false, false },
		{  true,  true, false,  true,  true, false,  true },
		{  true,  true,  true,  true, false, false,  true },
		{ false,  true,  true, false, false,  true,  true },
		{  true, false,  true,  true, false,  true,  true },
		{  true, false,  true,  true,  true,  true,  true },
		{  true,  true,  true, false, false, false, false },
		{  true,  true,  true,  true,  true,  true,  true },
		{  true,  true,  true,  true, false,  true,  true }
};


/* EOF */
