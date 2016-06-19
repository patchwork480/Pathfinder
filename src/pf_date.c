#include <pebble.h>
#include "pf_scheme.h"
#include "pf_date.h"


#define PF_NUM_DIGITS		(10)
#define PF_NUM_SEGMENTS		(7)

#define PF_DATE_DIGIT_Y		(3)
#define PF_DATE_DIGIT_1_X	(6)
#define PF_DATE_DIGIT_2_X	(PF_DATE_DIGIT_1_X + 13)
#define PF_DATE_DASH_1_X	(PF_DATE_DIGIT_2_X +  9)
#define PF_DATE_DIGIT_3_X	(PF_DATE_DIGIT_2_X + 17)
#define PF_DATE_DIGIT_4_X	(PF_DATE_DIGIT_3_X + 13)
#define PF_DATE_DASH_2_X	(PF_DATE_DIGIT_4_X +  9)
#define PF_DATE_DIGIT_5_X	(PF_DATE_DIGIT_4_X + 17)
#define PF_DATE_DIGIT_6_X	(PF_DATE_DIGIT_5_X + 13)


char date_buffer[12];
int last_year;
int last_mon;
int last_mday;


void init_date () {
		last_year = -1;
		last_mon = -1;
		last_mday = -1;
}


void update_date (struct tm *tick_date, TimeUnits units_changed) {
		APP_LOG(APP_LOG_LEVEL_DEBUG, "update_date");
		layer_mark_dirty(date_layer);
}


bool DIGIT_SEGS[PF_NUM_DIGITS][PF_NUM_SEGMENTS] = {
		{  true,  true,  true,  true,  true,  true, false },
		{ false,  true,  true, false, false, false, false },
		{  true,  true, false,  true,  true, false,  true },
		{  true,  true,  true,  true, false, false, false },
		{ false,  true,  true, false, false,  true,  true },
		{  true, false,  true,  true, false, false,  true },
		{  true, false,  true,  true,  true,  true,  true },
		{  true,  true,  true, false, false, false, false },
		{  true,  true,  true,  true,  true,  true,  true },
		{  true,  true,  true,  true, false,  true,  true }
};


GPath *PF_DATE_BORDER = NULL;
const GPathInfo PF_DATE_BORDER_INFO = {
	.num_points = 23,
	.points = (GPoint []) {
			{4,0}, {91,0}, {92,1}, {93,2}, {94,3}, {94,12}, {95,13}, {94,14}, {94,23}, {93,24}, {92,25}, {91,26},
			{4,26}, {3,25}, {2,24}, {1,23}, {1,14}, {0,13}, {1,12}, {1,3}, {2,2}, {3,1}, {4,0}
} };



void draw_date_glyph (GContext *ctx, bool segments[PF_NUM_SEGMENTS], int place, int x, int y) {
		for( int k =0; k < PF_NUM_SEGMENTS; k++ ) {
				if(segments[k]) {
				}
		}
}


void draw_date_digit (GContext *ctx, char digit, bool zero, int place, int x, int y) {
		if( (digit == '0') && zero ){
				return;
		}
		int index = ((int)digit) - ((int)'0');
		if( (index < 0) || (index >= PF_NUM_DIGITS) ){
				return;
		}
		bool segments[PF_NUM_SEGMENTS];
		(*segments) = DIGIT_SEGS[index];
		draw_date_glyph(*ctx, segments, place, x, y);
}


void draw_date (Layer *layer, GContext *ctx) {
		GRect bounds = layer_get_bounds(layer);
		snprintf(message_buffer, sizeof(message_buffer), "draw_date: %d,%d:%dx%d (%s)",
				bounds.origin.x, bounds.origin.y, bounds.size.w, bounds.size.h,
				layer_get_hidden(layer) ? "true" : "false");
		APP_LOG(APP_LOG_LEVEL_DEBUG, message_buffer);

		snprintf(message_buffer, sizeof(message_buffer), " - Drawing: ``%s''",
				date_buffer);
		APP_LOG(APP_LOG_LEVEL_DEBUG, message_buffer);

		if(PF_DATE_BORDER==NULL) {
				PF_DATE_BORDER = gpath_create(&PF_DATE_BORDER_INFO);
		}
		graphics_context_set_stroke_color(ctx, scheme.border);
		gpath_draw_outline(ctx, PF_DATE_BORDER);

		graphics_context_set_stroke_color(ctx, scheme.foregnd);
		graphics_context_set_fill_color(ctx, scheme.foregnd);

		draw_date_digit( ctx, date_buffer[0],	false,	0, PF_DATE_DIGIT_1_X, PF_DATE_DIGIT_Y );
		draw_date_digit( ctx, date_buffer[1],	false,	1, PF_DATE_DIGIT_2_X, PF_DATE_DIGIT_Y );
		draw_date_glyph( ctx, PF_DATE_DASH,	PF_DATE_DASH_1_X, PF_DATE_DIGIT_Y );
		draw_date_digit( ctx, date_buffer[3],	 true,	2, PF_DATE_DIGIT_3_X, PF_DATE_DIGIT_Y );
		draw_date_digit( ctx, date_buffer[4],	false,	3, PF_DATE_DIGIT_4_X, PF_DATE_DIGIT_Y );
		draw_date_glyph( ctx, PF_DATE_DASH,	PF_DATE_DASH_2_X, PF_DATE_DIGIT_Y );
		draw_date_digit( ctx, date_buffer[6],	 true,	4, PF_DATE_DIGIT_5_X, PF_DATE_DIGIT_Y );
		draw_date_digit( ctx, date_buffer[7],	false,	5, PF_DATE_DIGIT_6_X, PF_DATE_DIGIT_Y );
}


void deinit_date () {
		if(PF_DATE_BORDER != NULL) {
				gpath_destroy(PF_DATE_BORDER);
				PF_DATE_BORDER = NULL;
		}
}


/* EOF */
