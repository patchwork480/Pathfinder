#pragma once


#define PF_BTTY_ADJ_Y	(PBL_IF_ROUND_ELSE(14,0))
#define PF_BTTY_X		(54)
#define PF_BTTY_Y		(157-PF_BTTY_ADJ_Y)
#define PF_BTTY_W		(36)
#define PF_BTTY_H		(7)


#define PF_PLUG_ADJ_Y	(PBL_IF_ROUND_ELSE(14,0))
#define PF_PLUG_X		(43)
#define PF_PLUG_Y		(156-PF_PLUG_ADJ_Y)
#define PF_PLUG_W		(9)
#define PF_PLUG_H		(9)


#define PF_CHRG_ADJ_Y	(PBL_IF_ROUND_ELSE(14,0))
#define PF_CHRG_X		(92)
#define PF_CHRG_Y		(156-PF_CHRG_ADJ_Y)
#define PF_CHRG_W		(9)
#define PF_CHRG_H		(9)


#define PF_NUM_STATII	(11)
#define PF_STATUS_WID	(10)


extern Layer *btty_layer;
extern Layer *plug_layer;
extern Layer *chrg_layer;


extern int last_charge_pct;
extern bool last_plugged;
extern bool last_charging;

extern void init_btty ();
extern void deinit_btty ();
extern void update_btty (BatteryChargeState charge);
extern void draw_btty (Layer *layer, GContext *ctx);
extern void draw_plug (Layer *layer, GContext *ctx);
extern void draw_chrg (Layer *layer, GContext *ctx);


/* EOF */
