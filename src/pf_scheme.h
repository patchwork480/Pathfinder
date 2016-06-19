#pragma once


/**
 * COLORS
 */
#define PF_LIGHT	PBL_IF_COLOR_ELSE(GColorWhite, GColorWhite)
#define PF_MEDIUM  	PBL_IF_COLOR_ELSE(GColorBlue, GColorBlack)
#define PF_DARK    	PBL_IF_COLOR_ELSE(GColorBlack, GColorBlack)


typedef struct {
    GColor8 backgnd;
    GColor8 border;
    GColor8 foregnd;
} Scheme;


extern Scheme scheme;


extern void scheme_light_on_dark (Scheme* s);
extern void scheme_dark_on_light (Scheme* s);


/* EOF */
