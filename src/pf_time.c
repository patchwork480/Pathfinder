#include <pebble.h>
#include "pf_scheme.h"
#include "pf_util.h"
#include "pf_time.h"


#define PF_TIME_PLACES		(6)

#define PF_TIME_SM_W		(12)
#define PF_TIME_SM_H		(23)
#define PF_TIME_LG_W		(21)
#define PF_TIME_LG_H		(41)
#define PF_TIME_DIGIT_Y		(4)
#define PF_TIME_SMALL_Y		(16)
#define PF_TIME_DIGIT_1_X	(6)
#define PF_TIME_DIGIT_2_X	(PF_TIME_DIGIT_1_X + 25)
#define PF_TIME_COLON_X		(PF_TIME_DIGIT_2_X + 23)
#define PF_TIME_DIGIT_3_X	(PF_TIME_DIGIT_2_X + 30)
#define PF_TIME_DIGIT_4_X	(PF_TIME_DIGIT_3_X + 25)
#define PF_TIME_DIGIT_5_X	(PF_TIME_DIGIT_4_X + 26)
#define PF_TIME_DIGIT_6_X	(PF_TIME_DIGIT_5_X + 14)


char time_buffer[9];
int pf_hour;
int pf_min;
int pf_sec;


void init_time () {
		pf_hour = -1;
		pf_min = -1;
		pf_sec = -1;
}


GPath *PF_TIME_BORDER = NULL;
const GPathInfo PF_TIME_BORDER_INFO = {
	.num_points = 23,
	.points = (GPoint []) {
			{4,0}, {139,0}, {140,1}, {141,2}, {142,3}, {142,23}, {143,24}, {142,25},
			{142,45}, {141,46}, {140,47}, {139,48}, {4,48}, {3,47}, {2,46}, {1,45},
			{1,25}, {0,24}, {1,23}, {1,3}, {2,2}, {3,1}, {4,0}
	} };


GPath *PF_TIME_COLON_1 = NULL;
const GPathInfo PF_TIME_COLON_1_INFO = {
	.num_points = 5, .points = (GPoint []) { {2,10}, {4,12}, {2,14}, {0,12}, {2,10}
} };
GPath *PF_TIME_COLON_2 = NULL;
const GPathInfo PF_TIME_COLON_2_INFO = {
	.num_points = 5, .points = (GPoint []) { {2,25}, {4,27}, {2,29}, {0,27}, {2,25}
} };


GPoint PF_TIME_XY[PF_TIME_PLACES] = {
		{PF_TIME_DIGIT_1_X, PF_TIME_DIGIT_Y},
		{PF_TIME_DIGIT_2_X, PF_TIME_DIGIT_Y},
		{PF_TIME_DIGIT_3_X, PF_TIME_DIGIT_Y},
		{PF_TIME_DIGIT_4_X, PF_TIME_DIGIT_Y},
		{PF_TIME_DIGIT_5_X, PF_TIME_SMALL_Y},
		{PF_TIME_DIGIT_6_X, PF_TIME_SMALL_Y}
};


GPath *PF_TIME_SEGMENTS[PF_TIME_PLACES][PF_NUM_SEGMENTS] = {
		{NULL,NULL,NULL,NULL,NULL,NULL,NULL},
		{NULL,NULL,NULL,NULL,NULL,NULL,NULL},
		{NULL,NULL,NULL,NULL,NULL,NULL,NULL},
		{NULL,NULL,NULL,NULL,NULL,NULL,NULL},
		{NULL,NULL,NULL,NULL,NULL,NULL,NULL},
		{NULL,NULL,NULL,NULL,NULL,NULL,NULL}
};


const GPathInfo PF_TIME_SEGMENTS_LG_INFO[PF_NUM_SEGMENTS] = {
		{ .num_points = 7, .points = (GPoint []) {
				{5,0}, {15,0}, {17,2}, {15,4}, {5,4}, {3,2}, {5,0}
		} },
		{ .num_points = 7, .points = (GPoint []) {
				{18,3}, {20,5}, {20,17}, {18,19}, {16,17}, {16,5}, {18,3}
		} },
		{ .num_points = 7, .points = (GPoint []) {
				{18,37}, {20,35}, {20,23}, {18,21}, {16,23}, {16,35}, {18,37}
		} },
		{ .num_points = 7, .points = (GPoint []) {
				{5,40}, {15,40}, {17,38}, {15,36}, {5,36}, {3,38}, {5,40}
		} },
		{ .num_points = 7, .points = (GPoint []) {
				{2,37}, {0,35}, {0,23}, {2,21}, {4,23}, {4,35}, {2,37}
		} },
		{ .num_points = 7, .points = (GPoint []) {
				{2,3}, {0,5}, {0,17}, {2,19}, {4,17}, {4,5}, {2,3}
		} },
		{ .num_points = 7, .points = (GPoint []) {
				{5,18}, {15,18}, {17,20}, {15,22}, {5,22}, {3,20}, {5,18}
		} }
};


const GPathInfo PF_TIME_SEGMENTS_SM_INFO[PF_NUM_SEGMENTS] = {
		{ .num_points = 7, .points = (GPoint []) {
				{3,0}, {8,0}, {9,1}, {8,2}, {3,2}, {2,1}, {3,0}
		} },
		{ .num_points = 7, .points = (GPoint []) {
				{10,2}, {11,3}, {11,9}, {10,10}, {9,9}, {9,3}, {10,2}
		} },
		{ .num_points = 7, .points = (GPoint []) {
				{10,20}, {11,19}, {11,13}, {10,12}, {9,13}, {9,19}, {10,20}
		} },
		{ .num_points = 7, .points = (GPoint []) {
				{3,22}, {8,22}, {9,21}, {8,20}, {3,20}, {2,21}, {3,22}
		} },
		{ .num_points = 7, .points = (GPoint []) {
				{1,20}, {0,19}, {0,13}, {1,12}, {2,13}, {2,19}, {1,20}
		} },
		{ .num_points = 7, .points = (GPoint []) {
				{1,2}, {0,3}, {0,9}, {1,10}, {2,9}, {2,3}, {1,2}
		} },
		{ .num_points = 7, .points = (GPoint []) {
				{3,10}, {8,10}, {9,11}, {8,12}, {3,12}, {2,11}, {3,10}
		} }
};


void draw_time_glyph (GContext *ctx, bool segments[PF_NUM_SEGMENTS], int place) {
		for( int s = 0; s < PF_NUM_SEGMENTS; s++ ) {
				if(segments[s]) {
						if(PF_TIME_SEGMENTS[place][s] == NULL) {
								if( (place==4) || (place==5) ) {
										PF_TIME_SEGMENTS[place][s] = gpath_create(&PF_TIME_SEGMENTS_SM_INFO[s]);
								} else {
										PF_TIME_SEGMENTS[place][s] = gpath_create(&PF_TIME_SEGMENTS_LG_INFO[s]);
								}
								gpath_move_to(PF_TIME_SEGMENTS[place][s], PF_TIME_XY[place]);
						}
						gpath_draw_filled(ctx, PF_TIME_SEGMENTS[place][s]);
						gpath_draw_outline(ctx, PF_TIME_SEGMENTS[place][s]);
				}
		}
}


void draw_time_digit (GContext *ctx, char digit, bool zero, int place) {
		if( (digit == '0') && zero ){
				return;
		}
		int index = ((int)digit) - ((int)'0');
		if( (index < 0) || (index >= PF_NUM_DIGITS) ){
				return;
		}
		draw_time_glyph(ctx, DIGIT_SEGS[index], place);
}


void draw_time (Layer *layer, GContext *ctx) {

		// Draw BORDER
		if(PF_TIME_BORDER == NULL) {
				PF_TIME_BORDER = gpath_create(&PF_TIME_BORDER_INFO);
		}
		graphics_context_set_stroke_color(ctx, scheme.border);
		gpath_draw_outline(ctx, PF_TIME_BORDER);

		// Set COLORS
		graphics_context_set_stroke_color(ctx, scheme.foregnd);
		graphics_context_set_fill_color(ctx, scheme.foregnd);

		// Draw COLON #1
		if(PF_TIME_COLON_1 == NULL) {
				PF_TIME_COLON_1 = gpath_create(&PF_TIME_COLON_1_INFO);
				gpath_move_to(PF_TIME_COLON_1, (GPoint){PF_TIME_COLON_X, PF_TIME_DIGIT_Y});
		}
		gpath_draw_filled(ctx, PF_TIME_COLON_1);
		gpath_draw_outline(ctx, PF_TIME_COLON_1);

		// Draw COLON #2
		if(PF_TIME_COLON_2 == NULL) {
				PF_TIME_COLON_2 = gpath_create(&PF_TIME_COLON_2_INFO);
				gpath_move_to(PF_TIME_COLON_2, (GPoint){PF_TIME_COLON_X, PF_TIME_DIGIT_Y});
		}
		gpath_draw_filled(ctx, PF_TIME_COLON_2);
		gpath_draw_outline(ctx, PF_TIME_COLON_2);

		// Draw DIGITS
		draw_time_digit( ctx, time_buffer[0],  true, 0 );
		draw_time_digit( ctx, time_buffer[1], false, 1 );
		//
		draw_time_digit( ctx, time_buffer[3], false, 2 );
		draw_time_digit( ctx, time_buffer[4], false, 3 );
		//
		draw_time_digit( ctx, time_buffer[6], false, 4 );
		draw_time_digit( ctx, time_buffer[7], false, 5 );
}


void deinit_time () {
		if(PF_TIME_BORDER != NULL) {
				gpath_destroy(PF_TIME_BORDER);
				PF_TIME_BORDER = NULL;
		}
		if(PF_TIME_COLON_1 != NULL) {
				gpath_destroy(PF_TIME_COLON_1);
				PF_TIME_COLON_1 = NULL;
		}
		if(PF_TIME_COLON_2 != NULL) {
				gpath_destroy(PF_TIME_COLON_2);
				PF_TIME_COLON_2 = NULL;
		}
		for( int p = 0; p < PF_TIME_PLACES; p++ ) {
				for( int s = 0; s < PF_NUM_SEGMENTS; s++ ) {
						if(PF_TIME_SEGMENTS[p][s] != NULL) {
								gpath_destroy(PF_TIME_SEGMENTS[p][s]);
								PF_TIME_SEGMENTS[p][s] = NULL;
						}
				}
		}
}


/* EOF */
