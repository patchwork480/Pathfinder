#include <pebble.h>
#include "all.h"
#include "pf_moon.h"

char moon_buffer[12];
int last_moon;


void init_moon () {
		last_moon = -1;
}


void update_moon (struct tm *tick_time, TimeUnits units_changed) {
		APP_LOG(APP_LOG_LEVEL_DEBUG, "update_battery");
		layer_mark_dirty(moon_layer);
}



GPath *PF_MOON_BORDER = NULL;
const GPathInfo PF_MOON_BORDER_INFO = {
	.num_points = 72,
	.points = (GPoint []) {
			{16,0}, {23,0}, {24,1}, {28,2}, {29,2}, {30,3}, {31,4}, {32,4},
			{33,5}, {34,6}, {35,7}, {35,8}, {36,9}, {37,10}, {37,11}, {38,12},
			{38,15}, {39,16}, {39,23}, {38,24}, {38,27}, {37,28}, {37,29}, {36,30},
			{35,31}, {35,32}, {34,33}, {33,34}, {32,35}, {31,35}, {30,36}, {29,37},
			{28,37}, {27,38}, {24,38}, {23,39}, {16,39}, {15,38}, {12,38}, {11,37},
			{10,37}, {9,36}, {8,35}, {7,35}, {6,34}, {5,33}, {4,32}, {4,31},
			{3,30}, {2,29}, {2,28}, {1,27}, {1,24}, {0,23}, {0,16}, {1,15},
			{1,12}, {2,11}, {2,10}, {3,9}, {4,8}, {4,7}, {5,6}, {6,5},
			{7,4}, {8,4}, {9,3}, {10,2}, {11,2}, {12,1}, {15,1}, {16,0}
	} };



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
