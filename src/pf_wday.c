#include <pebble.h>
#include "pf_scheme.h"
#include "pf_wday.h"


#define PF_WDAY_LETTER_W	(13)
#define PF_WDAY_LETTER_H	(14)
#define PF_WDAY_LETTER_Y	(3)
#define PF_WDAY_LETTER_X	(6)


#define PF_WDAY_WID			(3)
#define PF_GLYPH_ROWS		(7)
#define PF_GLYPH_ROW_WID	(5)


char wday_buffer[4];
int8_t pf_wday;


void init_wday () {
		pf_wday = -1;
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


void wday_letter (GContext *ctx, const char letter, const uint8_t x, const uint8_t y ) {
		int8_t index = ((int8_t)letter) - ((int8_t)'A');
		uint8_t px, py;
		for( uint8_t r = 0; r < PF_GLYPH_ROWS; r++ ) {
				for( uint8_t c = 0; c < PF_GLYPH_ROW_WID; c++ ) {
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
		if(PF_WDAY_BORDER == NULL) {
				PF_WDAY_BORDER = gpath_create(&PF_WDAY_BORDER_INFO);
		}
		graphics_context_set_stroke_color(ctx, scheme.border);
		gpath_draw_outline(ctx, PF_WDAY_BORDER);

		graphics_context_set_stroke_color(ctx, scheme.foregnd);

		for( uint8_t k = 0; k < PF_WDAY_WID; k++ ) {
				wday_letter( ctx, wday_buffer[k],
						PF_WDAY_LETTER_X + (k * PF_WDAY_LETTER_W), PF_WDAY_LETTER_Y );
		}
}


void deinit_wday () {
		if(PF_WDAY_BORDER != NULL) {
				gpath_destroy(PF_WDAY_BORDER);
				PF_WDAY_BORDER = NULL;
		}
}


/* EOF */
