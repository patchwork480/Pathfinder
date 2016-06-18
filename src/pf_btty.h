#pragma once


#define PF_BTTY_ADJ_Y	PBL_IF_ROUND_ELSE(14,0)
#define PF_BTTY_X		54
#define PF_BTTY_Y		157-PF_BTTY_ADJ_Y
#define PF_BTTY_W		36
#define PF_BTTY_H		7


extern Layer *btty_layer;
extern char message_buffer[64];


extern char battery_buffer[10];
extern int last_charge_pct;
extern bool last_plugged;
extern bool last_charging;

extern void update_battery (BatteryChargeState charge);
extern void draw_battery (Layer *layer, GContext *ctx);


/* EOF */
