#pragma once


#define PF_TIME_X		(0)
#define PF_TIME_Y		(60)
#define PF_TIME_W		(144)
#define PF_TIME_H		(49)


extern Layer *time_layer;


extern char time_buffer[9];
extern int pf_hour;
extern int pf_min;
extern int pf_sec;


extern void init_time ();
extern void deinit_time ();
extern void draw_time (Layer *layer, GContext *ctx);


/* EOF */
