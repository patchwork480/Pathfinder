#include <pebble.h>
#include "all.h"
#include "pf_date.h"


char date_buffer[12];
int last_year;
int last_mon;
int last_mday;


void update_date (struct tm *tick_date, TimeUnits units_changed) {
		APP_LOG(APP_LOG_LEVEL_DEBUG, "update_date");
		layer_mark_dirty(date_layer);
}



GPath *PF_DATE_BORDER = NULL;
const GPathInfo PF_DATE_BORDER_INFO = {
	.num_points = 23,
	.points = (GPoint []) {
			{4,0}, {91,0}, {92,1}, {93,2}, {94,3}, {94,12}, {95,13}, {94,14}, {94,23}, {93,24}, {92,25}, {91,26},
			{4,26}, {3,25}, {2,24}, {1,23}, {1,14}, {0,13}, {1,12}, {1,3}, {2,2}, {3,1}, {4,0}
} };



void draw_date (Layer *layer, GContext *ctx) {
		GRect bounds = layer_get_bounds(layer);
		snprintf(message_buffer, sizeof(message_buffer), "draw_date: %d,%d:%dx%d (%s)",
				bounds.origin.x, bounds.origin.y, bounds.size.w, bounds.size.h,
				layer_get_hidden(layer) ? "true" : "false");
		APP_LOG(APP_LOG_LEVEL_DEBUG, message_buffer);

		snprintf(message_buffer, sizeof(message_buffer), " - Drawing: ``%s''",
				date_buffer);
		APP_LOG(APP_LOG_LEVEL_DEBUG, message_buffer);

		// graphics_context_set_fill_color(ctx, PF_BACKGND);
		// graphics_fill_rect(ctx, bounds, 0, GCornerNone);
  
		if(PF_DATE_BORDER==NULL) {
				PF_DATE_BORDER = gpath_create(&PF_DATE_BORDER_INFO);
		}
		graphics_context_set_stroke_color(ctx, PF_BORDER);
		gpath_draw_outline(ctx, PF_DATE_BORDER);

		graphics_context_set_text_color(ctx, PF_FOREGND);
		graphics_draw_text(ctx, date_buffer,
						fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD),
						bounds,
						GTextOverflowModeWordWrap,
						GTextAlignmentCenter,
						NULL);
}

/* EOF */
