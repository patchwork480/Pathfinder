#pragma once


#define PF_MOON_ADJ_X	(PBL_IF_ROUND_ELSE(7,0))
#define PF_MOON_ADJ_Y	(PBL_IF_ROUND_ELSE(7,0))
#define PF_MOON_X		(25+PF_MOON_ADJ_X)
#define PF_MOON_Y		(11+PF_MOON_ADJ_Y)
#define PF_MOON_W		(40)
#define PF_MOON_H		(40)


#define PF_NUM_PHASES	(16)


extern Layer *moon_layer;
extern char message_buffer[64];


extern char moon_buffer[12];
extern int last_moon;
extern int jul_date;


extern int julian_date (int year, int month, int day);


extern void init_moon ();
extern void deinit_moon ();
extern void update_moon (struct tm *tick_moon, TimeUnits units_changed);
extern void draw_moon (Layer *layer, GContext *ctx);


/* EOF */
