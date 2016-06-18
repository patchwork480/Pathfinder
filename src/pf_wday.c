#include <pebble.h>
#include "all.h"
#include "pf_wday.h"


char wday_buffer[12];
int last_wday;


void init_wday () {
		last_wday = -1;
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



#define GLYPH_ROWS		7
#define GLYPH_ROW_WID	5

const char *_XXX_ = ".***.";
const char *X___X = "*...*";
const char *XXXXX = "*****";
const char *XXXX_ = "****.";
const char *X____ = "*....";
const char *XXX__ = "***..";
const char *X__X_ = "*..*.";
const char *X__XX = "*..**";
const char *_XXXX = ".****";
const char *__X__ = "..*..";
const char *___X_ = "...*.";
const char *XX_XX = "**.**";
const char *X_X_X = "*.*.*";
const char *XX__X = "**..*";
const char *_XX_X = ".**.*";
const char *____X = "....*";
const char *_X_X_ = ".*.*.";
const char *_X___ = ".*...";


char *strupr (char *str) {
		char *s;
		for(s = str; *s; s++) {
				if(('a' <= *s) && (*s <= 'z')) {
						*s = 'A' + (*s - 'a');
				}
		}
		return str;
}


void wday_letter ( GContext *ctx, char letter, int x, int y ) {
		if( empty(PF_WKDAY_LETTERS[letter]) ) {
				return;
		}
		char *array[] = PF_WKDAY_LETTERS[letter];
		int px, py;
		for( int r = 0; r < GLYPH_ROWS; r++ ) {
				for( int c = 0; c < GLYPH_ROW_WID; c++ ) {
						if( array[r][c] == '*' ) {
								py = y + ( r * 2 );
								px = x + ( c * 2 );
								pts = array( px,py,  px+1,py,  px+1,py+1,  px,py+1,  px,py );
								gpath_draw_filled(ctx, pts, 5, black);
								gpath_draw_outline(ctx, pts, 5, $white);
						}
				}
		}
}



void draw_wday (Layer *layer, GContext *ctx) {
		GRect bounds = layer_get_bounds(layer);
		snprintf(message_buffer, sizeof(message_buffer), "draw_wday: %d,%d:%dx%d (%s)",
				bounds.origin.x, bounds.origin.y, bounds.size.w, bounds.size.h,
				layer_get_hidden(layer) ? "true" : "false");
		APP_LOG(APP_LOG_LEVEL_DEBUG, message_buffer);

		snprintf(message_buffer, sizeof(message_buffer), " - Drawing: ``%s''",
				strupr(wday_buffer));
		APP_LOG(APP_LOG_LEVEL_DEBUG, message_buffer);

		if(PF_WDAY_BORDER==NULL) {
				PF_WDAY_BORDER = gpath_create(&PF_WDAY_BORDER_INFO);
		}
		graphics_context_set_stroke_color(ctx, PF_BORDER);
		gpath_draw_outline(ctx, PF_WDAY_BORDER);

		graphics_context_set_fill_color(ctx, PF_FOREGND);
		graphics_context_set_stroke_color(ctx, PF_FOREGND);

		for( int k = 0; k < strlen(wday_buffer); k++ ) {
				wday_letter( ctx, wday_buffer[k],
						PF_WKDAY_LETTER_X + (k * PF_WKDAY_LETTER_W), PF_WKDAY_LETTER_Y );
		}
}

/* EOF */
