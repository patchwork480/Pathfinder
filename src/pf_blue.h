#pragma once


#define PF_BLUE_ADJ_Y	(PBL_IF_ROUND_ELSE(7,0))
#define PF_BLUE_X		(70)
#define PF_BLUE_Y		(0+PF_BLUE_ADJ_Y)
#define PF_BLUE_W		(9)
#define PF_BLUE_H		(9)


extern Layer *blue_layer;


extern bool app_connected;
extern bool kit_connected;


extern void init_blue ();
extern void deinit_blue ();
extern void update_blue_app (bool connected);
extern void update_blue_kit (bool connected);
extern void draw_blue (Layer *layer, GContext *ctx);


/* EOF */
