#include <pebble.h>
#include "pf_scheme.h"
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
int last_hour;
int last_min;
int last_sec;


void init_time () {
		last_hour = -1;
		last_min = -1;
		last_sec = -1;
}


void update_time (struct tm *tick_time, TimeUnits units_changed) {
		APP_LOG(APP_LOG_LEVEL_DEBUG, "update_battery");
		layer_mark_dirty(time_layer);
}



GPath *PF_TIME_BORDER = NULL;
const GPathInfo PF_TIME_BORDER_INFO = {
	.num_points = 23,
	.points = (GPoint []) {
			{4,0}, {139,0}, {140,1}, {141,2}, {142,3}, {142,23}, {143,24}, {142,25},
			{142,45}, {141,46}, {140,47}, {139,48}, {4,48}, {3,47}, {2,46}, {1,45},
			{1,25}, {0,24}, {1,23}, {1,3}, {2,2}, {3,1}, {4,0}
	} };


GPath *PF_TIME_DASH_1 = NULL;
GPath *PF_TIME_DASH_2 = NULL;
const GPathInfo PF_TIME_DASH_INFO = {
	.num_points = 7,
	.points = (GPoint []) {
			{3,9}, {6,9}, {7,10}, {6,11}, {3,11}, {2,10}, {3,9}
} };


GPoint PF_TIME_XY[PF_TIME_PLACES] = {
		{PF_TIME_DIGIT_1_X, PF_TIME_DIGIT_Y},
		{PF_TIME_DIGIT_2_X, PF_TIME_DIGIT_Y},
		{PF_TIME_DIGIT_3_X, PF_TIME_DIGIT_Y},
		{PF_TIME_DIGIT_4_X, PF_TIME_DIGIT_Y},
		{PF_TIME_DIGIT_5_X, PF_TIME_DIGIT_Y},
		{PF_TIME_DIGIT_6_X, PF_TIME_DIGIT_Y}
};


GPath *PF_TIME_SEGMENTS[PF_TIME_PLACES][PF_NUM_SEGMENTS] = {
		{NULL,NULL,NULL,NULL,NULL,NULL,NULL},
		{NULL,NULL,NULL,NULL,NULL,NULL,NULL},
		{NULL,NULL,NULL,NULL,NULL,NULL,NULL},
		{NULL,NULL,NULL,NULL,NULL,NULL,NULL},
		{NULL,NULL,NULL,NULL,NULL,NULL,NULL},
		{NULL,NULL,NULL,NULL,NULL,NULL,NULL}
};


const GPathInfo PF_TIME_SEGMENTS_INFO[PF_NUM_SEGMENTS] = {
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


void draw_time_glyph (GContext *ctx, bool segments[PF_NUM_SEGMENTS], int place) {
		for( int s = 0; s < PF_NUM_SEGMENTS; s++ ) {
				if(segments[s]) {
						if(PF_TIME_SEGMENTS[place][s]==NULL) {
								PF_TIME_SEGMENTS[place][s] = gpath_create(&PF_TIME_SEGMENTS_INFO[s]);
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
		GRect bounds = layer_get_bounds(layer);
		snprintf(message_buffer, sizeof(message_buffer), "draw_hour_min: %d,%d:%dx%d (%s)",
				bounds.origin.x, bounds.origin.y, bounds.size.w, bounds.size.h,
				layer_get_hidden(layer) ? "true" : "false");
		APP_LOG(APP_LOG_LEVEL_DEBUG, message_buffer);

		snprintf(message_buffer, sizeof(message_buffer), " - Drawing: ``%s''",
				time_buffer);
		APP_LOG(APP_LOG_LEVEL_DEBUG, message_buffer);

		// Draw BORDER
		if(PF_TIME_BORDER==NULL) {
				PF_TIME_BORDER = gpath_create(&PF_TIME_BORDER_INFO);
		}
		graphics_context_set_stroke_color(ctx, scheme.border);
		gpath_draw_outline(ctx, PF_TIME_BORDER);

		// Set COLORS
		graphics_context_set_stroke_color(ctx, scheme.foregnd);
		graphics_context_set_fill_color(ctx, scheme.foregnd);

		// Draw DASH #1
		if(PF_TIME_DASH_1==NULL) {
				PF_TIME_DASH_1 = gpath_create(&PF_TIME_DASH_INFO);
				gpath_move_to(PF_TIME_DASH_1, (GPoint){PF_TIME_DASH_1_X, PF_TIME_DIGIT_Y});
		}
		gpath_draw_filled(ctx, PF_TIME_DASH_1);
		gpath_draw_outline(ctx, PF_TIME_DASH_1);

		// Draw DASH #2
		if(PF_TIME_DASH_2==NULL) {
				PF_TIME_DASH_2 = gpath_create(&PF_TIME_DASH_INFO);
				gpath_move_to(PF_TIME_DASH_2, (GPoint){PF_TIME_DASH_2_X, PF_TIME_DIGIT_Y});
		}
		gpath_draw_filled(ctx, PF_TIME_DASH_2);
		gpath_draw_outline(ctx, PF_TIME_DASH_2);

		// Draw DIGITS
		draw_time_digit( ctx, time_buffer[0], true, 0 );
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
		if(PF_TIME_DASH_1 != NULL) {
				gpath_destroy(PF_TIME_DASH_1);
				PF_TIME_DASH_1 = NULL;
		}
		if(PF_TIME_DASH_2 != NULL) {
				gpath_destroy(PF_TIME_DASH_2);
				PF_TIME_DASH_2 = NULL;
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
