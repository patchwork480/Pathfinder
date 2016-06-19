#include <pebble.h>
#include "pf_blue.h"


bool app_connected;
bool kit_connected;


void init_blue () {
        app_connected = false;
        kit_connected = false;
}


void deinit_blue () {
        app_connected = false;
        kit_connected = false;
}


void update_blue_app (bool connected) {
        app_connected = connection_service_peek_pebble_app_connection();
}


void update_blue_kit (bool connected) {
        kit_connected = connection_service_peek_pebblekit_connection();
}


void draw_blue (Layer *layer, GContext *ctx) {
}


/* EOF */
