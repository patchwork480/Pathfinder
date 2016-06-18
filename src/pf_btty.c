#include <pebble.h>
#include "all.h"
#include "pf_btty.h"


int last_charge_pct;
bool last_plugged;
bool last_charging;
char battery_buffer[10];


void update_battery (BatteryChargeState charge) {
		APP_LOG(APP_LOG_LEVEL_DEBUG, "update_battery");
		snprintf(battery_buffer, sizeof(battery_buffer), "%s %02d %s",
						charge.is_plugged ? "@" : "+",
						charge.charge_percent,
						charge.is_charging ? "@" : "+"
						);
		last_charge_pct = charge.charge_percent;
		last_plugged = charge.is_plugged;
		last_charging = charge.is_charging;
		layer_mark_dirty(btty_layer);
}


GPath *PF_BTTY_BORDER = NULL;
const GPathInfo PF_BTTY_BORDER_INFO = {
  .num_points = 15,
  .points = (GPoint [])
				{{2,0}, {33,0}, {34,1}, {34,2}, {35,3}, {34,4}, {34,5}, {33,6}, {2,6}, {1,5}, {1,4}, {0,3}, {1,2}, {1,1}, {2,0}}
};


void draw_battery (Layer *layer, GContext *ctx) {
		GRect bounds = layer_get_bounds(layer);
		snprintf(message_buffer, sizeof(message_buffer), "draw_battery: %d,%d:%dx%d (%s)",
				bounds.origin.x, bounds.origin.y, bounds.size.w, bounds.size.h,
				layer_get_hidden(layer) ? "true" : "false");
		APP_LOG(APP_LOG_LEVEL_DEBUG, message_buffer);

		snprintf(message_buffer, sizeof(message_buffer), " - Drawing: ``%s''",
				battery_buffer);
		APP_LOG(APP_LOG_LEVEL_DEBUG, message_buffer);

		// graphics_context_set_fill_color(ctx, PF_BACKGND);
		// graphics_fill_rect(ctx, bounds, 0, GCornerNone);
  
    if(PF_BTTY_BORDER==NULL) {
        PF_BTTY_BORDER = gpath_create(&PF_BTTY_BORDER_INFO);
    }
    graphics_context_set_stroke_color(ctx, PF_BORDER);
    gpath_draw_outline(ctx, PF_BTTY_BORDER);

		graphics_context_set_text_color(ctx, PF_FOREGND);
		graphics_draw_text(ctx, battery_buffer,
						fonts_get_system_font(FONT_KEY_GOTHIC_18),
						bounds,
						GTextOverflowModeWordWrap,
						GTextAlignmentCenter,
						NULL);
}


