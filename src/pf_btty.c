#include <pebble.h>
#include "all.h"
#include "pf_btty.h"


int charge_percent;
bool is_plugged;
bool is_charging;


void init_btty () {
		charge_percent = -1;
		is_plugged = false;
		is_charging = false;
}


void update_btty (BatteryChargeState charge) {
		if( (charge_percent != charge.charge_percent)
			|| (is_plugged != charge.is_plugged)
			|| (is_charging != charge.is_charging) ) {
				charge_percent = charge.charge_percent;
				is_plugged = charge.is_plugged;
				is_charging = charge.is_charging;
				layer_mark_dirty(btty_layer);
		}
}


GPath *PF_BTTY_BORDER = NULL;
const GPathInfo PF_BTTY_BORDER_INFO = {
	.num_points = 15,
	.points = (GPoint []) {
			{2,0}, {33,0}, {34,1}, {34,2}, {35,3}, {34,4}, {34,5}, {33,6}, {2,6}, {1,5}, {1,4}, {0,3}, {1,2}, {1,1}, {2,0}
	} };


GPath *PF_BTTY_STATII[PF_NUM_STATII] = {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL};
const GPathInfo PF_BTTY_STATII_INFO[PF_NUM_STATII] = {
		{ .num_points = 5, .points = (GPoint []) { {3,2}, { 3,2}, { 3,4}, {3,4}, {3,2} } },
		{ .num_points = 5, .points = (GPoint []) { {3,2}, { 5,2}, { 5,4}, {3,4}, {3,2} } },
		{ .num_points = 5, .points = (GPoint []) { {3,2}, { 8,2}, { 8,4}, {3,4}, {3,2} } },
		{ .num_points = 5, .points = (GPoint []) { {3,2}, {11,2}, {11,4}, {3,4}, {3,2} } },
		{ .num_points = 5, .points = (GPoint []) { {3,2}, {14,2}, {14,4}, {3,4}, {3,2} } },
		{ .num_points = 5, .points = (GPoint []) { {3,2}, {17,2}, {17,4}, {3,4}, {3,2} } },
		{ .num_points = 5, .points = (GPoint []) { {3,2}, {20,2}, {20,4}, {3,4}, {3,2} } },
		{ .num_points = 5, .points = (GPoint []) { {3,2}, {23,2}, {23,4}, {3,4}, {3,2} } },
		{ .num_points = 5, .points = (GPoint []) { {3,2}, {26,2}, {26,4}, {3,4}, {3,2} } },
		{ .num_points = 5, .points = (GPoint []) { {3,2}, {29,2}, {29,4}, {3,4}, {3,2} } },
		{ .num_points = 5, .points = (GPoint []) { {3,2}, {32,2}, {32,4}, {3,4}, {3,2} } }
};


void draw_btty (Layer *layer, GContext *ctx) {
		if(PF_BTTY_BORDER==NULL) {
				PF_BTTY_BORDER = gpath_create(&PF_BTTY_BORDER_INFO);
		}
		graphics_context_set_stroke_color(ctx, PF_BORDER);
		gpath_draw_outline(ctx, PF_BTTY_BORDER);

		int btty_status = charge_percent / PF_STATUS_WID;
		if(PF_BTTY_STATII[btty_status]==NULL) {
				PF_BTTY_STATII[btty_status] = gpath_create(&PF_BTTY_STATII_INFO[btty_status]);
		}
		graphics_context_set_fill_color(ctx, PF_FOREGND);
		gpath_draw_filled(ctx, PF_BTTY_STATII[btty_status]);
}


GPath *PF_PLUG_SYMBOL = NULL;
const GPathInfo PF_PLUG_SYMBOL_INFO = {
	.num_points = 17,
	.points = (GPoint []) {
			{0,2}, {2,2}, {2,0}, {3,0}, {3,2}, {5,2}, {5,0}, {6,0},
			{6,2}, {8,2}, {8,3}, {5,6}, {5,8}, {3,8}, {3,6}, {0,3},
            {0,2}
	} };



void draw_plug (Layer *layer, GContext *ctx) {
		if(is_plugged) {
				if(PF_PLUG_SYMBOL==NULL) {
						PF_PLUG_SYMBOL = gpath_create(&PF_PLUG_SYMBOL_INFO);
				}
				graphics_context_set_fill_color(ctx, PF_FOREGND);
				gpath_draw_filled(ctx, PF_PLUG_SYMBOL);
		}
}


GPath *PF_CHRG_SYMBOL = NULL;
const GPathInfo PF_CHRG_SYMBOL_INFO = {
	.num_points = 14,
	.points = (GPoint []) {
			{3,0}, {7,0}, {5,2}, {6,3}, {7,3}, {2,8}, {2,7}, {3,6},
			{3,4}, {1,4}, {2,3}, {2,2}, {3,1}, {3,0}
	} };


GPath *PF_CMPL_SYMBOL = NULL;
const GPathInfo PF_CMPL_SYMBOL_INFO = {
	.num_points = 18,
	.points = (GPoint []) {
			{1,5}, {2,4}, {4,6}, {5,5}, {5,4}, {6,3}, {6,2}, {7,1},
			{8,0}, {8,1}, {7,2}, {7,3}, {6,4}, {6,5}, {5,6}, {5,7},
			{4,8}, {1,5}
	} };


void draw_chrg (Layer *layer, GContext *ctx) {
		if(is_plugged) {
				if(charge_percent==100) {
						if(PF_CMPL_SYMBOL==NULL) {
								PF_CMPL_SYMBOL = gpath_create(&PF_CMPL_SYMBOL_INFO);
						}
						graphics_context_set_fill_color(ctx, PF_FOREGND);
						gpath_draw_filled(ctx, PF_CMPL_SYMBOL);
				} else if(is_charging) {
						if(PF_CHRG_SYMBOL==NULL) {
								PF_CHRG_SYMBOL = gpath_create(&PF_CHRG_SYMBOL_INFO);
						}
						graphics_context_set_fill_color(ctx, PF_FOREGND);
						gpath_draw_filled(ctx, PF_CHRG_SYMBOL);
				}
		}
}


/* EOF */

