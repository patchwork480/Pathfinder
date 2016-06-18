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
  .num_points = 15,
  .points = (GPoint [])
				{{2,0}, {33,0}, {34,1}, {34,2}, {35,3}, {34,4}, {34,5}, {33,6}, {2,6}, {1,5}, {1,4}, {0,3}, {1,2}, {1,1}, {2,0}}
};



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
