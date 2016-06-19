#include <pebble.h>
#include "pf_scheme.h"


Scheme scheme;


void scheme_light_on_dark (Scheme* s) {
		s->backgnd = GColorBlack;
		s->border = GColorWhite;
		s->foregnd = GColorWhite;
}


void scheme_dark_on_light (Scheme* s) {
		s->backgnd = GColorWhite;
		s->border = GColorBlack;
		s->foregnd = GColorBlack;
}


/* EOF */
