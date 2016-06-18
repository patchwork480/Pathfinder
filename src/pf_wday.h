#pragma once


#define PF_WDAY_ADJ_X	PBL_IF_ROUND_ELSE(3,0)
#define PF_WDAY_ADJ_Y	PBL_IF_ROUND_ELSE(7+3,0)
#define PF_WDAY_X		72+PF_WDAY_ADJ_X
#define PF_WDAY_Y		21+PF_WDAY_ADJ_Y
#define PF_WDAY_W		48
#define PF_WDAY_H		20

#define PF_WDAY_LETTER_W 13
#define PF_WDAY_LETTER_H 14
#define PF_WDAY_LETTER_Y PF_WDAY_Y + 3
#define PF_WDAY_LETTER_X PF_WDAY_X + 6


extern Layer *wday_layer;
extern char message_buffer[64];


extern char wday_buffer[12];
extern int last_wday;


extern void init_wday ();
extern void update_wday (struct tm *tick_wday, TimeUnits units_changed);
extern void draw_wday (Layer *layer, GContext *ctx);


/* EOF */
