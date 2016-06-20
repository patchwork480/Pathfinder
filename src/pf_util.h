#pragma once


#define PF_NUM_DIGITS		(10)
#define PF_NUM_SEGMENTS		(7)


extern char message_buffer[32];


extern char *strupr (char *str);
extern bool DIGIT_SEGS[PF_NUM_DIGITS][PF_NUM_SEGMENTS];


/* EOF */
