#include <pebble.h>
#include "all.h"
#include "pf_moon.h"

char moon_buffer[12];
int last_moon;


void update_moon (struct tm *tick_time, TimeUnits units_changed) {
		APP_LOG(APP_LOG_LEVEL_DEBUG, "update_battery");
		layer_mark_dirty(moon_layer);
}



GPath *PF_MOON_BORDER = NULL;
const GPathInfo PF_MOON_BORDER_INFO = {
  .num_points = 15,
  .points = (GPoint [])
				{{2,0}, {33,0}, {34,1}, {34,2}, {35,3}, {34,4}, {34,5}, {33,6}, {2,6}, {1,5}, {1,4}, {0,3}, {1,2}, {1,1}, {2,0}}
};



void draw_moon (Layer *layer, GContext *ctx) {
		GRect bounds = layer_get_bounds(layer);
		snprintf(message_buffer, sizeof(message_buffer), "draw_moon: %d,%d:%dx%d (%s)",
				bounds.origin.x, bounds.origin.y, bounds.size.w, bounds.size.h,
				layer_get_hidden(layer) ? "true" : "false");
		APP_LOG(APP_LOG_LEVEL_DEBUG, message_buffer);

		// graphics_context_set_fill_color(ctx, PF_BACKGND);
		// graphics_fill_rect(ctx, bounds, 0, GCornerNone);
  
    if(PF_MOON_BORDER==NULL) {
        PF_MOON_BORDER = gpath_create(&PF_MOON_BORDER_INFO);
    }
    graphics_context_set_stroke_color(ctx, PF_BORDER);
    gpath_draw_outline(ctx, PF_MOON_BORDER);

		graphics_context_set_text_color(ctx, PF_FOREGND);
		graphics_draw_text(ctx, moon_buffer,
						fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD),
						bounds,
						GTextOverflowModeWordWrap,
						GTextAlignmentCenter,
						NULL);
}
