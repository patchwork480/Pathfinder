#pragma once


#define PF_TIME_X		(0)
#define PF_TIME_Y		(60)
#define PF_TIME_W		(144)
#define PF_TIME_H		(49)


extern Layer *time_layer;
extern char message_buffer[64];


extern char time_buffer[9];
extern int last_hour;
extern int last_min;
extern int last_sec;


extern void init_time ();
extern void deinit_time ();
extern void update_time (struct tm *tick_time, TimeUnits units_changed);
extern void draw_time (Layer *layer, GContext *ctx);


/* EOF */
