#include <pebble.h>
#include "pf_scheme.h"
#include "pf_blue.h"


bool app_connected;
bool kit_connected;


void init_blue () {
		app_connected = connection_service_peek_pebble_app_connection();
		kit_connected = connection_service_peek_pebblekit_connection();
}


void update_blue_app (bool connected) {
		app_connected = connection_service_peek_pebble_app_connection();
		layer_mark_dirty(blue_layer);
}


void update_blue_kit (bool connected) {
		kit_connected = connection_service_peek_pebblekit_connection();
		layer_mark_dirty(blue_layer);
}


GPath *PF_BLUE_SYMBOL = NULL;
const GPathInfo PF_BLUE_SYMBOL_INFO = {
	.num_points = 24,
	.points = (GPoint []) {
			{0,2}, {1,3}, {2,3}, {3,4}, {5,4}, {6,5}, {7,5}, {8,6},
			{7,7}, {6,7}, {5,8}, {4,8}, {4,0}, {5,0}, {6,1}, {7,1},
			{8,2}, {7,3}, {6,3}, {5,4}, {3,4}, {2,5}, {1,5}, {0,6}
	} };


void draw_blue (Layer *layer, GContext *ctx) {
		if(app_connected) {
				if(PF_BLUE_SYMBOL==NULL) {
						PF_BLUE_SYMBOL = gpath_create(&PF_BLUE_SYMBOL_INFO);
				}
				graphics_context_set_stroke_color(ctx, scheme.foregnd);
				gpath_draw_outline_open(ctx, PF_BLUE_SYMBOL);
		}
}


void deinit_blue () {
		if(PF_BLUE_SYMBOL != NULL) {
				gpath_destroy(PF_BLUE_SYMBOL);
				PF_BLUE_SYMBOL = NULL;
		}
}


/* EOF */
