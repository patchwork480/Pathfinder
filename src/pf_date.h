#pragma once


#define PF_DATE_ADJ_Y	(PBL_IF_ROUND_ELSE(7,0))
#define PF_DATE_X		(24)
#define PF_DATE_Y		(119-PF_DATE_ADJ_Y)
#define PF_DATE_W		(96)
#define PF_DATE_H		(27)


extern Layer *date_layer;


extern char date_buffer[9];
extern int16_t pf_year;
extern int8_t pf_mon;
extern int8_t pf_mday;


extern void init_date ();
extern void deinit_date ();
extern void draw_date (Layer *layer, GContext *ctx);


/* EOF */
