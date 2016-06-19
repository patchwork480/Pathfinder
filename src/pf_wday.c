#include <pebble.h>
#include "pf_scheme.h"
#include "pf_wday.h"


char wday_buffer[12];
int last_wday;


char *strupr (char *str) {
		char *s;
		for(s = str; *s; s++) {
				if(('a' <= *s) && (*s <= 'z')) {
						*s = 'A' + (*s - 'a');
				}
		}
		return str;
}


void init_wday () {
		last_wday = -1;
}


void deinit_wday () {
}


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


const char *PF_WDAY_LETTERS[26][PF_GLYPH_ROWS] = {
		{ ".***.", "*...*", "*...*", "*****", "*...*", "*...*", "*...*" },
		{ "****.", "*...*", "*...*", "****.", "*...*", "*...*", "****." },
		{ ".***.", "*...*", "*....", "*....", "*....", "*...*", ".***." },
		{ "***..", "*..*.", "*...*", "*...*", "*...*", "*..*.", "***.." },
		{ "*****", "*....", "*....", "****.", "*....", "*....", "*****" },
		{ "*****", "*....", "*....", "****.", "*....", "*....", "*...." },
		{ ".***.", "*...*", "*....", "*..**", "*....", "*...*", ".****" },
		{ "*...*", "*...*", "*...*", "*****", "*...*", "*...*", "*...*" },
		{ "*****", "..*..", "..*..", "..*..", "..*..", "..*..", "*****" },
		{ "*****", "...*.", "...*.", "...*.", "*..*.", "*..*.", ".***." },
		{ "*...*", "*...*", "*..*.", "***..", "*..*.", "*...*", "*...*" },
		{ "*....", "*....", "*....", "*....", "*....", "*....", "*****" },
		{ "*...*", "**.**", "*.*.*", "*.*.*", "*...*", "*...*", "*...*" },
		{ "*...*", "**..*", "*.*.*", "*.*.*", "*.*.*", "*..**", "*...*" },
		{ ".***.", "*...*", "*...*", "*...*", "*...*", "*...*", ".***." },
		{ "****.", "*...*", "*...*", "****.", "*....", "*....", "*...." },
		{ ".***.", "*...*", "*...*", "*...*", "*.*.*", "*..*.", ".**.*" },
		{ "****.", "*...*", "*...*", "****.", "*..*.", "*...*", "*...*" },
		{ ".***.", "*...*", "*....", ".***.", "....*", "*...*", ".***." },
		{ "*****", "..*..", "..*..", "..*..", "..*..", "..*..", "..*.." },
		{ "*...*", "*...*", "*...*", "*...*", "*...*", "*...*", ".***." },
		{ "*...*", "*...*", "*...*", ".*.*.", ".*.*.", ".*.*.", "..*.." },
		{ "*...*", "*...*", "*.*.*", "*.*.*", "*.*.*", "*.*.*", ".*.*." },
		{ "*...*", "*...*", ".*.*.", "..*..", ".*.*.", "*...*", "*...*" },
		{ "*...*", "*...*", ".*.*.", "..*..", "..*..", "..*..", "..*.." },
		{ "*****", "....*", "...*.", "..*..", ".*...", "*....", "*****" },
};


void wday_letter (GContext *ctx, const char letter, const int x, const int y ) {
		int index = ((int)letter) - ((int)'A');
		int px, py;
		for( int r = 0; r < PF_GLYPH_ROWS; r++ ) {
				for( int c = 0; c < PF_GLYPH_ROW_WID; c++ ) {
						if( PF_WDAY_LETTERS[index][r][c] == '*' ) {
								py = y + ( r * 2 );
								px = x + ( c * 2 );
								graphics_draw_pixel(ctx, (GPoint){px,py} );
								graphics_draw_pixel(ctx, (GPoint){px+1,py} );
								graphics_draw_pixel(ctx, (GPoint){px,py+1} );
								graphics_draw_pixel(ctx, (GPoint){px+1,py+1} );
						}
				}
		}
}


void draw_wday (Layer *layer, GContext *ctx) {
		if(PF_WDAY_BORDER==NULL) {
				PF_WDAY_BORDER = gpath_create(&PF_WDAY_BORDER_INFO);
		}
		graphics_context_set_stroke_color(ctx, scheme.border);
		gpath_draw_outline(ctx, PF_WDAY_BORDER);

		graphics_context_set_stroke_color(ctx, scheme.foregnd);

		for( int k = 0; k < PF_WDAY_WID; k++ ) {
				wday_letter( ctx, wday_buffer[k],
						PF_WDAY_LETTER_X + (k * PF_WDAY_LETTER_W), PF_WDAY_LETTER_Y );
		}
}


/* EOF */
