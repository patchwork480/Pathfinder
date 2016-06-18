#pragma once

#include <pebble.h>


/**
 * COLORS
 */
#define PF_BACKGND		PBL_IF_COLOR_ELSE(GColorWhite, GColorWhite)
#define PF_BORDER  		PBL_IF_COLOR_ELSE(GColorBlue, GColorBlack)
#define PF_FOREGND		PBL_IF_COLOR_ELSE(GColorBlack, GColorBlack)


/* EOF */
