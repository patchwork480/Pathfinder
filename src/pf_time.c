#include <pebble.h>
#include "pf_scheme.h"
#include "pf_time.h"


char time_buffer[12];
int last_hour;
int last_min;
int last_sec;


void init_time () {
		last_hour = -1;
		last_min = -1;
		last_sec = -1;
}


void deinit_time () {
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



void draw_time (Layer *layer, GContext *ctx) {
		GRect bounds = layer_get_bounds(layer);
		snprintf(message_buffer, sizeof(message_buffer), "draw_hour_min: %d,%d:%dx%d (%s)",
				bounds.origin.x, bounds.origin.y, bounds.size.w, bounds.size.h,
				layer_get_hidden(layer) ? "true" : "false");
		APP_LOG(APP_LOG_LEVEL_DEBUG, message_buffer);

		snprintf(message_buffer, sizeof(message_buffer), " - Drawing: ``%s''",
				time_buffer);
		APP_LOG(APP_LOG_LEVEL_DEBUG, message_buffer);

		// graphics_context_set_fill_color(ctx, PF_BACKGND);
		// graphics_fill_rect(ctx, bounds, 0, GCornerNone);

		if(PF_TIME_BORDER==NULL) {
				PF_TIME_BORDER = gpath_create(&PF_TIME_BORDER_INFO);
		}
		graphics_context_set_stroke_color(ctx, scheme.border);
		gpath_draw_outline(ctx, PF_TIME_BORDER);

		graphics_context_set_text_color(ctx, scheme.foregnd);
		graphics_draw_text(ctx, time_buffer,
						fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD),
						bounds,
						GTextOverflowModeWordWrap,
						GTextAlignmentCenter,
						NULL);
}


