#include <pebble.h>
#include "all.h"
#include "pf_wday.h"


char wday_buffer[12];
int last_wday;


void update_wday (struct tm *tick_wday, TimeUnits units_changed) {
		APP_LOG(APP_LOG_LEVEL_DEBUG, "update_wday");
		layer_mark_dirty(wday_layer);
}



GPath *PF_WDAY_BORDER = NULL;
const GPathInfo PF_WDAY_BORDER_INFO = {
	.num_points = 23,
	.points = (GPoint []) {
			{4,0}, {43,0}, {44,1}, {45,2}, {46,3}, {46,8}, {47,9}, {46,10},
			{46,16}, {45,17}, {44,18}, {43,19}, {4,19}, {3,18}, {2,17}, {1,16},
			{1,10}, {0,9}, {1,8}, {1,3}, {2,2}, {3,1}, {4,0}
	} };



void draw_wday (Layer *layer, GContext *ctx) {
		GRect bounds = layer_get_bounds(layer);
		snprintf(message_buffer, sizeof(message_buffer), "draw_wday: %d,%d:%dx%d (%s)",
				bounds.origin.x, bounds.origin.y, bounds.size.w, bounds.size.h,
				layer_get_hidden(layer) ? "true" : "false");
		APP_LOG(APP_LOG_LEVEL_DEBUG, message_buffer);

		snprintf(message_buffer, sizeof(message_buffer), " - Drawing: ``%s''",
				wday_buffer);
		APP_LOG(APP_LOG_LEVEL_DEBUG, message_buffer);

		// graphics_context_set_fill_color(ctx, PF_BACKGND);
		// graphics_fill_rect(ctx, bounds, 0, GCornerNone);
  
		if(PF_WDAY_BORDER==NULL) {
				PF_WDAY_BORDER = gpath_create(&PF_WDAY_BORDER_INFO);
		}
		graphics_context_set_stroke_color(ctx, PF_BORDER);
		gpath_draw_outline(ctx, PF_WDAY_BORDER);

		graphics_context_set_text_color(ctx, PF_FOREGND);
		graphics_draw_text(ctx, wday_buffer,
						fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD),
						bounds,
						GTextOverflowModeWordWrap,
						GTextAlignmentCenter,
						NULL);
}

/* EOF */
