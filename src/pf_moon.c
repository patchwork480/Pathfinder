#include <pebble.h>
#include "all.h"
#include "pf_moon.h"

char moon_buffer[12];
int last_moon;


void init_moon () {
		last_moon = -1;
}


void update_moon (struct tm *tick_time, TimeUnits units_changed) {
		APP_LOG(APP_LOG_LEVEL_DEBUG, "update_battery");
		layer_mark_dirty(moon_layer);
}



GPath *PF_MOON_BORDER = NULL;
const GPathInfo PF_MOON_BORDER_INFO = {
	.num_points = 72,
	.points = (GPoint []) {
			{16,0}, {23,0}, {24,1}, {28,2}, {29,2}, {30,3}, {31,4}, {32,4},
			{33,5}, {34,6}, {35,7}, {35,8}, {36,9}, {37,10}, {37,11}, {38,12},
			{38,15}, {39,16}, {39,23}, {38,24}, {38,27}, {37,28}, {37,29}, {36,30},
			{35,31}, {35,32}, {34,33}, {33,34}, {32,35}, {31,35}, {30,36}, {29,37},
			{28,37}, {27,38}, {24,38}, {23,39}, {16,39}, {15,38}, {12,38}, {11,37},
			{10,37}, {9,36}, {8,35}, {7,35}, {6,34}, {5,33}, {4,32}, {4,31},
			{3,30}, {2,29}, {2,28}, {1,27}, {1,24}, {0,23}, {0,16}, {1,15},
			{1,12}, {2,11}, {2,10}, {3,9}, {4,8}, {4,7}, {5,6}, {6,5},
			{7,4}, {8,4}, {9,3}, {10,2}, {11,2}, {12,1}, {15,1}, {16,0}
	} };


GPath *PF_MOON_PHASES[PF_NUM_PHASES] = {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL};
const GPathInfo PF_MOON_PHASES_INFO[PF_NUM_PHASES] = {
		{ .num_points = 0, .points = (GPoint []) {
		} },
		{ .num_points = 58, .points = (GPoint []) {
				{26,1}, {28,2}, {29,2}, {30,3}, {31,4}, {32,4}, {33,5}, {34,6},
				{35,7}, {35,8}, {36,9}, {37,10}, {37,11}, {38,12}, {38,15}, {39,16},
				{39,23}, {38,24}, {38,27}, {37,28}, {37,29}, {36,30}, {35,31}, {35,32},
				{34,33}, {33,34}, {32,35}, {31,35}, {30,36}, {29,37}, {28,37}, {27,38},
				{26,38}, {27,37}, {28,36}, {29,35}, {30,34}, {31,33}, {32,32}, {32,31},
				{33,30}, {33,29}, {34,28}, {34,25}, {35,24}, {35,15}, {34,14}, {34,11},
				{33,10}, {33,9}, {32,8}, {32,7}, {31,6}, {30,5}, {29,4}, {28,3},
				{27,2}, {26,1}
		} },
		{ .num_points = 62, .points = (GPoint []) {
				{22,0}, {23,0}, {24,1}, {28,2}, {29,2}, {30,3}, {31,4}, {32,4},
				{33,5}, {34,6}, {35,7}, {35,8}, {36,9}, {37,10}, {37,11}, {38,12},
				{38,15}, {39,16}, {39,23}, {38,24}, {38,27}, {37,28}, {37,29}, {36,30},
				{35,31}, {35,32}, {34,33}, {33,34}, {32,35}, {31,35}, {30,36}, {29,37},
				{28,37}, {27,38}, {24,38}, {23,39}, {22,39}, {23,39}, {24,38}, {25,37},
				{26,36}, {26,35}, {27,34}, {27,33}, {28,32}, {28,31}, {29,30}, {29,26},
				{30,25}, {30,14}, {29,13}, {29,9}, {28,8}, {28,7}, {27,6}, {27,5},
				{26,4}, {26,3}, {25,2}, {24,1}, {23,0}, {22,0}
		} },
		{ .num_points = 52, .points = (GPoint []) {
				{21,0}, {23,0}, {24,1}, {28,2}, {29,2}, {30,3}, {31,4}, {32,4},
				{33,5}, {34,6}, {35,7}, {35,8}, {36,9}, {37,10}, {37,11}, {38,12},
				{38,15}, {39,16}, {39,23}, {38,24}, {38,27}, {37,28}, {37,29}, {36,30},
				{35,31}, {35,32}, {34,33}, {33,34}, {32,35}, {31,35}, {30,36}, {29,37},
				{28,37}, {27,38}, {24,38}, {23,39}, {21,39}, {22,38}, {22,37}, {23,36},
				{23,34}, {24,33}, {24,29}, {25,28}, {25,11}, {24,10}, {24,6}, {23,5},
				{23,3}, {22,2}, {22,1}, {21,0}
		} },
		{ .num_points = 38, .points = (GPoint []) {
				{20,0}, {23,0}, {24,1}, {28,2}, {29,2}, {30,3}, {31,4}, {32,4},
				{33,5}, {34,6}, {35,7}, {35,8}, {36,9}, {37,10}, {37,11}, {38,12},
				{38,15}, {39,16}, {39,23}, {38,24}, {38,27}, {37,28}, {37,29}, {36,30},
				{35,31}, {35,32}, {34,33}, {33,34}, {32,35}, {31,35}, {30,36}, {29,37},
				{28,37}, {27,38}, {24,38}, {23,39}, {20,39}, {20,0}
		} },
		{ .num_points = 52, .points = (GPoint []) {
				{19,0}, {23,0}, {24,1}, {28,2}, {29,2}, {30,3}, {31,4}, {32,4},
				{33,5}, {34,6}, {35,7}, {35,8}, {36,9}, {37,10}, {37,11}, {38,12},
				{38,15}, {39,16}, {39,23}, {38,24}, {38,27}, {37,28}, {37,29}, {36,30},
				{35,31}, {35,32}, {34,33}, {33,34}, {32,35}, {31,35}, {30,36}, {29,37},
				{28,37}, {27,38}, {24,38}, {23,39}, {19,39}, {18,38}, {18,37}, {17,36},
				{17,34}, {16,33}, {16,29}, {15,28}, {15,11}, {16,10}, {16,6}, {17,5},
				{17,3}, {18,2}, {18,1}, {19,0}
		} },
		{ .num_points = 62, .points = (GPoint []) {
				{18,0}, {23,0}, {24,1}, {28,2}, {29,2}, {30,3}, {31,4}, {32,4},
				{33,5}, {34,6}, {35,7}, {35,8}, {36,9}, {37,10}, {37,11}, {38,12},
				{38,15}, {39,16}, {39,23}, {38,24}, {38,27}, {37,28}, {37,29}, {36,30},
				{35,31}, {35,32}, {34,33}, {33,34}, {32,35}, {31,35}, {30,36}, {29,37},
				{28,37}, {27,38}, {24,38}, {23,39}, {18,39}, {17,38}, {16,38}, {15,37},
				{14,36}, {14,35}, {13,34}, {13,33}, {12,32}, {12,31}, {11,30}, {11,26},
				{10,25}, {10,14}, {11,13}, {11,9}, {12,8}, {12,7}, {13,6}, {13,5},
				{14,4}, {14,3}, {15,2}, {16,1}, {17,1}, {18,0}
		} },
		{ .num_points = 66, .points = (GPoint []) {
				{17,0}, {23,0}, {24,1}, {28,2}, {29,2}, {30,3}, {31,4}, {32,4},
				{33,5}, {34,6}, {35,7}, {35,8}, {36,9}, {37,10}, {37,11}, {38,12},
				{38,15}, {39,16}, {39,23}, {38,24}, {38,27}, {37,28}, {37,29}, {36,30},
				{35,31}, {35,32}, {34,33}, {33,34}, {32,35}, {31,35}, {30,36}, {29,37},
				{28,37}, {27,38}, {24,38}, {23,39}, {17,39}, {16,38}, {14,38}, {13,37},
				{12,36}, {11,35}, {10,34}, {9,33}, {8,32}, {8,31}, {7,30}, {7,29},
				{6,28}, {6,25}, {5,24}, {5,15}, {6,14}, {6,11}, {7,10}, {7,9},
				{8,8}, {8,7}, {9,6}, {10,5}, {11,4}, {12,3}, {13,2}, {14,1},
				{16,1}, {17,0}
		} },
		{ .num_points = 72, .points = (GPoint []) {
				{23,0}, {16,0}, {15,1}, {11,2}, {10,2}, {9,3}, {8,4}, {7,4},
				{6,5}, {5,6}, {4,7}, {4,8}, {3,9}, {2,10}, {2,11}, {1,12},
				{1,15}, {0,16}, {0,23}, {1,24}, {1,27}, {2,28}, {2,29}, {3,30},
				{4,31}, {4,32}, {5,33}, {6,34}, {7,35}, {8,35}, {9,36}, {10,37},
				{11,37}, {12,38}, {15,38}, {16,39}, {23,39}, {24,38}, {27,38}, {28,37},
				{29,37}, {30,36}, {31,35}, {32,35}, {33,34}, {34,33}, {35,32}, {35,31},
				{36,30}, {37,29}, {37,28}, {38,27}, {38,24}, {39,23}, {39,16}, {38,15},
				{38,12}, {37,11}, {37,10}, {36,9}, {35,8}, {35,7}, {34,6}, {33,5},
				{32,4}, {31,4}, {30,3}, {29,2}, {28,2}, {27,1}, {24,1}, {23,0}
		} },
		{ .num_points = 66, .points = (GPoint []) {
				{22,0}, {16,0}, {15,1}, {11,2}, {10,2}, {9,3}, {8,4}, {7,4},
				{6,5}, {5,6}, {4,7}, {4,8}, {3,9}, {2,10}, {2,11}, {1,12},
				{1,15}, {0,16}, {0,23}, {1,24}, {1,27}, {2,28}, {2,29}, {3,30},
				{4,31}, {4,32}, {5,33}, {6,34}, {7,35}, {8,35}, {9,36}, {10,37},
				{11,37}, {12,38}, {15,38}, {16,39}, {22,39}, {23,38}, {25,38}, {26,37},
				{27,36}, {28,35}, {29,34}, {30,33}, {31,32}, {31,31}, {32,30}, {32,29},
				{33,28}, {33,25}, {34,24}, {34,15}, {33,14}, {33,11}, {32,10}, {32,9},
				{31,8}, {31,7}, {30,6}, {29,5}, {28,4}, {27,3}, {26,2}, {25,1},
				{23,1}, {22,0}
		} },
		{ .num_points = 62, .points = (GPoint []) {
				{21,0}, {16,0}, {15,1}, {11,2}, {10,2}, {9,3}, {8,4}, {7,4},
				{6,5}, {5,6}, {4,7}, {4,8}, {3,9}, {2,10}, {2,11}, {1,12},
				{1,15}, {0,16}, {0,23}, {1,24}, {1,27}, {2,28}, {2,29}, {3,30},
				{4,31}, {4,32}, {5,33}, {6,34}, {7,35}, {8,35}, {9,36}, {10,37},
				{11,37}, {12,38}, {15,38}, {16,39}, {21,39}, {22,38}, {23,38}, {24,37},
				{25,36}, {25,35}, {26,34}, {26,33}, {27,32}, {27,31}, {28,30}, {28,26},
				{29,25}, {29,14}, {28,13}, {28,9}, {27,8}, {27,7}, {26,6}, {26,5},
				{25,4}, {25,3}, {24,2}, {23,1}, {22,1}, {21,0}
		} },
		{ .num_points = 52, .points = (GPoint []) {
				{20,0}, {16,0}, {15,1}, {11,2}, {10,2}, {9,3}, {8,4}, {7,4},
				{6,5}, {5,6}, {4,7}, {4,8}, {3,9}, {2,10}, {2,11}, {1,12},
				{1,15}, {0,16}, {0,23}, {1,24}, {1,27}, {2,28}, {2,29}, {3,30},
				{4,31}, {4,32}, {5,33}, {6,34}, {7,35}, {8,35}, {9,36}, {10,37},
				{11,37}, {12,38}, {15,38}, {16,39}, {20,39}, {21,38}, {21,37}, {22,36},
				{22,34}, {23,33}, {23,29}, {24,28}, {24,11}, {23,10}, {23,6}, {22,5},
				{22,3}, {21,2}, {21,1}, {20,0}
		} },
		{ .num_points = 38, .points = (GPoint []) {
				{19,0}, {16,0}, {15,1}, {11,2}, {10,2}, {9,3}, {8,4}, {7,4},
				{6,5}, {5,6}, {4,7}, {4,8}, {3,9}, {2,10}, {2,11}, {1,12},
				{1,15}, {0,16}, {0,23}, {1,24}, {1,27}, {2,28}, {2,29}, {3,30},
				{4,31}, {4,32}, {5,33}, {6,34}, {7,35}, {8,35}, {9,36}, {10,37},
				{11,37}, {12,38}, {15,38}, {16,39}, {19,39}, {19,0}
		} },
		{ .num_points = 52, .points = (GPoint []) {
				{18,0}, {16,0}, {15,1}, {11,2}, {10,2}, {9,3}, {8,4}, {7,4},
				{6,5}, {5,6}, {4,7}, {4,8}, {3,9}, {2,10}, {2,11}, {1,12},
				{1,15}, {0,16}, {0,23}, {1,24}, {1,27}, {2,28}, {2,29}, {3,30},
				{4,31}, {4,32}, {5,33}, {6,34}, {7,35}, {8,35}, {9,36}, {10,37},
				{11,37}, {12,38}, {15,38}, {16,39}, {18,39}, {17,38}, {17,37}, {16,36},
				{16,34}, {15,33}, {15,29}, {14,28}, {14,11}, {15,10}, {15,6}, {16,5},
				{16,3}, {17,2}, {17,1}, {18,0}
		} },
		{ .num_points = 62, .points = (GPoint []) {
				{17,0}, {16,0}, {15,1}, {11,2}, {10,2}, {9,3}, {8,4}, {7,4},
				{6,5}, {5,6}, {4,7}, {4,8}, {3,9}, {2,10}, {2,11}, {1,12},
				{1,15}, {0,16}, {0,23}, {1,24}, {1,27}, {2,28}, {2,29}, {3,30},
				{4,31}, {4,32}, {5,33}, {6,34}, {7,35}, {8,35}, {9,36}, {10,37},
				{11,37}, {12,38}, {15,38}, {16,39}, {17,39}, {16,39}, {15,38}, {14,37},
				{13,36}, {13,35}, {12,34}, {12,33}, {11,32}, {11,31}, {10,30}, {10,26},
				{9,25}, {9,14}, {10,13}, {10,9}, {11,8}, {11,7}, {12,6}, {12,5},
				{13,4}, {13,3}, {14,2}, {15,1}, {16,0}, {17,0}
		} },
		{ .num_points = 58, .points = (GPoint []) {
				{13,1}, {11,2}, {10,2}, {9,3}, {8,4}, {7,4}, {6,5}, {5,6},
				{4,7}, {4,8}, {3,9}, {2,10}, {2,11}, {1,12}, {1,15}, {0,16},
				{0,23}, {1,24}, {1,27}, {2,28}, {2,29}, {3,30}, {4,31}, {4,32},
				{5,33}, {6,34}, {7,35}, {8,35}, {9,36}, {10,37}, {11,37}, {12,38},
				{13,38}, {12,37}, {11,36}, {10,35}, {9,34}, {8,33}, {7,32}, {7,31},
				{6,30}, {6,29}, {5,28}, {5,25}, {4,24}, {4,15}, {5,14}, {5,11},
				{6,10}, {6,9}, {7,8}, {7,7}, {8,6}, {9,5}, {10,4}, {11,3},
				{12,2}, {13,1}
		} }
};


void draw_moon (Layer *layer, GContext *ctx) {
		if( last_moon > -1 ) {
				last_moon = last_moon % PF_NUM_PHASES;
				if(PF_MOON_PHASES[last_moon]==NULL) {
						PF_MOON_PHASES[last_moon] = gpath_create(&PF_MOON_PHASES_INFO[last_moon]);
				}
				graphics_context_set_fill_color(ctx, PF_FOREGND);
				graphics_context_set_stroke_color(ctx, PF_FOREGND);
				gpath_draw_filled(ctx, PF_MOON_PHASES[last_moon]);
				gpath_draw_outline(ctx, PF_MOON_PHASES[last_moon]);
		}

		if(PF_MOON_BORDER==NULL) {
				PF_MOON_BORDER = gpath_create(&PF_MOON_BORDER_INFO);
		}
		graphics_context_set_stroke_color(ctx, PF_BORDER);
		gpath_draw_outline(ctx, PF_MOON_BORDER);
}


/* EOF */
