#pragma once


#define PF_DATE_ADJ_Y	(PBL_IF_ROUND_ELSE(7,0))
#define PF_DATE_X		(24)
#define PF_DATE_Y		(119-PF_DATE_ADJ_Y)
#define PF_DATE_W		(96)
#define PF_DATE_H		(27)


extern Layer *date_layer;
extern char message_buffer[64];


extern char date_buffer[12];
extern int last_year;
extern int last_mon;
extern int last_mday;


extern void init_date ();
extern void deinit_date ();
extern void update_date (struct tm *tick_date, TimeUnits units_changed);
extern void draw_date (Layer *layer, GContext *ctx);


/* EOF */
