#include <pebble.h>
#include "pf_scheme.h"
#include "pf_util.h"
#include "pf_date.h"


#define PF_DATE_PLACES		(6)

#define PF_DATE_DIGIT_Y		(3)
#define PF_DATE_DIGIT_1_X	(6)
#define PF_DATE_DIGIT_2_X	(PF_DATE_DIGIT_1_X + 13)
#define PF_DATE_DASH_1_X	(PF_DATE_DIGIT_2_X +  9)
#define PF_DATE_DIGIT_3_X	(PF_DATE_DIGIT_2_X + 17)
#define PF_DATE_DIGIT_4_X	(PF_DATE_DIGIT_3_X + 13)
#define PF_DATE_DASH_2_X	(PF_DATE_DIGIT_4_X +  9)
#define PF_DATE_DIGIT_5_X	(PF_DATE_DIGIT_4_X + 17)
#define PF_DATE_DIGIT_6_X	(PF_DATE_DIGIT_5_X + 13)


char date_buffer[9];
int16_t pf_year;
int8_t pf_mon;
int8_t pf_mday;


void init_date () {
		pf_year = -1;
		pf_mon = -1;
		pf_mday = -1;
}


GPath *PF_DATE_BORDER = NULL;
const GPathInfo PF_DATE_BORDER_INFO = {
	.num_points = 23,
	.points = (GPoint []) {
			{4,0}, {91,0}, {92,1}, {93,2}, {94,3}, {94,12}, {95,13}, {94,14}, {94,23}, {93,24}, {92,25}, {91,26},
			{4,26}, {3,25}, {2,24}, {1,23}, {1,14}, {0,13}, {1,12}, {1,3}, {2,2}, {3,1}, {4,0}
} };



GPath *PF_DATE_DASH_1 = NULL;
GPath *PF_DATE_DASH_2 = NULL;
const GPathInfo PF_DATE_DASH_INFO = {
	.num_points = 7,
	.points = (GPoint []) {
			{3,9}, {6,9}, {7,10}, {6,11}, {3,11}, {2,10}, {3,9}
} };


GPoint PF_DATE_XY[PF_DATE_PLACES] = {
		{PF_DATE_DIGIT_1_X, PF_DATE_DIGIT_Y},
		{PF_DATE_DIGIT_2_X, PF_DATE_DIGIT_Y},
		{PF_DATE_DIGIT_3_X, PF_DATE_DIGIT_Y},
		{PF_DATE_DIGIT_4_X, PF_DATE_DIGIT_Y},
		{PF_DATE_DIGIT_5_X, PF_DATE_DIGIT_Y},
		{PF_DATE_DIGIT_6_X, PF_DATE_DIGIT_Y}
};


GPath *PF_DATE_SEGMENTS[PF_DATE_PLACES][PF_NUM_SEGMENTS] = {
		{NULL,NULL,NULL,NULL,NULL,NULL,NULL},
		{NULL,NULL,NULL,NULL,NULL,NULL,NULL},
		{NULL,NULL,NULL,NULL,NULL,NULL,NULL},
		{NULL,NULL,NULL,NULL,NULL,NULL,NULL},
		{NULL,NULL,NULL,NULL,NULL,NULL,NULL},
		{NULL,NULL,NULL,NULL,NULL,NULL,NULL}
};


const GPathInfo PF_DATE_SEGMENTS_INFO[PF_NUM_SEGMENTS] = {
		{ .num_points = 7, .points = (GPoint []) {
				{3,0}, {7,0}, {8,1}, {7,2}, {3,2}, {2,1}, {3,0}
		} },
		{ .num_points = 7, .points = (GPoint []) {
				{9,2}, {10,3}, {10,8}, {9,9}, {8,8}, {8,3}, {9,2}
		} },
		{ .num_points = 7, .points = (GPoint []) {
				{9,18}, {10,17}, {10,12}, {9,11}, {8,12}, {8,17}, {9,18}
		} },
		{ .num_points = 7, .points = (GPoint []) {
				{3,20}, {7,20}, {8,19}, {7,18}, {3,18}, {2,19}, {3,20}
		} },
		{ .num_points = 7, .points = (GPoint []) {
				{1,18}, {0,17}, {0,12}, {1,11}, {2,12}, {2,17}, {1,18}
		} },
		{ .num_points = 7, .points = (GPoint []) {
				{1,2}, {0,3}, {0,8}, {1,9}, {2,8}, {2,3}, {1,2}
		} },
		{ .num_points = 7, .points = (GPoint []) {
				{3,9}, {7,9}, {8,10}, {7,11}, {3,11}, {2,10}, {3,9}
		} }
};


void draw_date_glyph (GContext *ctx, bool segments[PF_NUM_SEGMENTS], int place) {
		for( uint8_t s = 0; s < PF_NUM_SEGMENTS; s++ ) {
				if(segments[s]) {
						if(PF_DATE_SEGMENTS[place][s] == NULL) {
								PF_DATE_SEGMENTS[place][s] = gpath_create(&PF_DATE_SEGMENTS_INFO[s]);
								gpath_move_to(PF_DATE_SEGMENTS[place][s], PF_DATE_XY[place]);
						}
						gpath_draw_filled(ctx, PF_DATE_SEGMENTS[place][s]);
						gpath_draw_outline(ctx, PF_DATE_SEGMENTS[place][s]);
				}
		}
}


void draw_date_digit (GContext *ctx, char digit, bool zero, int place) {
		if( (digit == '0') && zero ){
				return;
		}
		int index = ((int)digit) - ((int)'0');
		if( (index < 0) || (index >= PF_NUM_DIGITS) ){
				return;
		}
		draw_date_glyph(ctx, DIGIT_SEGS[index], place);
}


void draw_date (Layer *layer, GContext *ctx) {

		// Draw BORDER
		if(PF_DATE_BORDER == NULL) {
				PF_DATE_BORDER = gpath_create(&PF_DATE_BORDER_INFO);
		}
		graphics_context_set_stroke_color(ctx, scheme.border);
		gpath_draw_outline(ctx, PF_DATE_BORDER);

		// Set COLORS
		graphics_context_set_stroke_color(ctx, scheme.foregnd);
		graphics_context_set_fill_color(ctx, scheme.foregnd);

		// Draw DASH #1
		if(PF_DATE_DASH_1 == NULL) {
				PF_DATE_DASH_1 = gpath_create(&PF_DATE_DASH_INFO);
				gpath_move_to(PF_DATE_DASH_1, (GPoint){PF_DATE_DASH_1_X, PF_DATE_DIGIT_Y});
		}
		gpath_draw_filled(ctx, PF_DATE_DASH_1);
		gpath_draw_outline(ctx, PF_DATE_DASH_1);

		// Draw DASH #2
		if(PF_DATE_DASH_2 == NULL) {
				PF_DATE_DASH_2 = gpath_create(&PF_DATE_DASH_INFO);
				gpath_move_to(PF_DATE_DASH_2, (GPoint){PF_DATE_DASH_2_X, PF_DATE_DIGIT_Y});
		}
		gpath_draw_filled(ctx, PF_DATE_DASH_2);
		gpath_draw_outline(ctx, PF_DATE_DASH_2);

		// Draw DIGITS
		draw_date_digit( ctx, date_buffer[0], false, 0 );
		draw_date_digit( ctx, date_buffer[1], false, 1 );
		//
		draw_date_digit( ctx, date_buffer[3], true, 2 );
		draw_date_digit( ctx, date_buffer[4], false, 3 );
		//
		draw_date_digit( ctx, date_buffer[6], true, 4 );
		draw_date_digit( ctx, date_buffer[7], false, 5 );
}


void deinit_date () {
		if(PF_DATE_BORDER != NULL) {
				gpath_destroy(PF_DATE_BORDER);
				PF_DATE_BORDER = NULL;
		}
		if(PF_DATE_DASH_1 != NULL) {
				gpath_destroy(PF_DATE_DASH_1);
				PF_DATE_DASH_1 = NULL;
		}
		if(PF_DATE_DASH_2 != NULL) {
				gpath_destroy(PF_DATE_DASH_2);
				PF_DATE_DASH_2 = NULL;
		}
		for( uint8_t p = 0; p < PF_DATE_PLACES; p++ ) {
				for( uint8_t s = 0; s < PF_NUM_SEGMENTS; s++ ) {
						if(PF_DATE_SEGMENTS[p][s] != NULL) {
								gpath_destroy(PF_DATE_SEGMENTS[p][s]);
								PF_DATE_SEGMENTS[p][s] = NULL;
						}
				}
		}
}


/* EOF */
