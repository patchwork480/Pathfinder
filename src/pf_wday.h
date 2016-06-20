#pragma once


#define PF_WDAY_ADJ_X	(PBL_IF_ROUND_ELSE(3,0))
#define PF_WDAY_ADJ_Y	(PBL_IF_ROUND_ELSE(7+3,0))
#define PF_WDAY_X		(72+PF_WDAY_ADJ_X)
#define PF_WDAY_Y		(21+PF_WDAY_ADJ_Y)
#define PF_WDAY_W		(48)
#define PF_WDAY_H		(20)


extern Layer *wday_layer;


extern char wday_buffer[4];
extern int pf_wday;


extern void init_wday ();
extern void deinit_wday ();
extern void draw_wday (Layer *layer, GContext *ctx);


/* EOF */
