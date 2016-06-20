#include <pebble.h>
#include "pf_scheme.h"
#include "pf_util.h"
#include "pf_astro.h"
#include "pf_time.h"
#include "pf_date.h"
#include "pf_wday.h"
#include "pf_btty.h"
#include "pf_blue.h"
#include "pf_moon.h"


static Window *main_window;
Layer *time_layer;
Layer *date_layer;
Layer *wday_layer;
Layer *btty_layer;
Layer *plug_layer;
Layer *chrg_layer;
Layer *blue_layer;
Layer *moon_layer;


static void update_time (struct tm *tick_time, TimeUnits units_changed) {
		if( pf_sec != tick_time->tm_sec ) {

				if( pf_mday != tick_time->tm_mday ) {
						pf_year = tick_time->tm_year;
						pf_mon = tick_time->tm_mon;
						pf_mday = tick_time->tm_mday;
						strftime(date_buffer, sizeof(date_buffer), "%y %m-%d", tick_time);

						pf_wday = tick_time->tm_wday;
						strftime(wday_buffer, sizeof(wday_buffer), "%a", tick_time);
						strupr(wday_buffer);

						pf_juldate = julian_date(pf_year, pf_mon, pf_mday);
						snprintf(message_buffer, sizeof(message_buffer), "Julian: %d", pf_juldate);
						APP_LOG(APP_LOG_LEVEL_DEBUG, message_buffer);
						pf_moon = moon_phase(pf_juldate);
				}

				pf_hour = tick_time->tm_hour;
				pf_min = tick_time->tm_min;
				pf_sec = tick_time->tm_sec;
				if(clock_is_24h_style()) {
						strftime(time_buffer, sizeof(time_buffer), "%k:%M:%S", tick_time);
				} else {
						strftime(time_buffer, sizeof(time_buffer), "%I:%M:%S", tick_time);
				}

				layer_mark_dirty(time_layer);
		}
}


static void main_window_load (Window *window) {
		// APP_LOG(APP_LOG_LEVEL_DEBUG, "main_window_load");

		// Set Window Background
		window_set_background_color(window, scheme.backgnd);

		// Get Root Layer of Window
		Layer *root_layer = window_get_root_layer(window);

		// Set the weekday layer
		wday_layer = layer_create(GRect(PF_WDAY_X, PF_WDAY_Y, PF_WDAY_W, PF_WDAY_H));
		layer_set_update_proc(wday_layer, draw_wday);
		layer_add_child(root_layer, wday_layer);

		// Set the moon layer
		moon_layer = layer_create(GRect(PF_MOON_X, PF_MOON_Y, PF_MOON_W, PF_MOON_H));
		layer_set_update_proc(moon_layer, draw_moon);
		layer_add_child(root_layer, moon_layer);

		// Set the time layer
		time_layer = layer_create(GRect(PF_TIME_X, PF_TIME_Y, PF_TIME_W, PF_TIME_H));
		layer_set_update_proc(time_layer, draw_time);
		layer_add_child(root_layer, time_layer);

		// Set the date layer
		date_layer = layer_create(GRect(PF_DATE_X, PF_DATE_Y, PF_DATE_W, PF_DATE_H));
		layer_set_update_proc(date_layer, draw_date);
		layer_add_child(root_layer, date_layer);

		// Set the battery layer
		btty_layer = layer_create(GRect(PF_BTTY_X, PF_BTTY_Y, PF_BTTY_W, PF_BTTY_H));
		layer_set_update_proc(btty_layer, draw_btty);
		layer_add_child(root_layer, btty_layer);

		// Set the plugged layer
		plug_layer = layer_create(GRect(PF_PLUG_X, PF_PLUG_Y, PF_PLUG_W, PF_PLUG_H));
		layer_set_update_proc(plug_layer, draw_plug);
		layer_add_child(root_layer, plug_layer);

		// Set the charge layer
		chrg_layer = layer_create(GRect(PF_CHRG_X, PF_CHRG_Y, PF_CHRG_W, PF_CHRG_H));
		layer_set_update_proc(chrg_layer, draw_chrg);
		layer_add_child(root_layer, chrg_layer);

		// Set the blue layer
		blue_layer = layer_create(GRect(PF_BLUE_X, PF_BLUE_Y, PF_BLUE_W, PF_BLUE_H));
		layer_set_update_proc(blue_layer, draw_blue);
		layer_add_child(root_layer, blue_layer);

		// Force immediate draw
		time_t now = time(NULL);
		update_time(localtime(&now), YEAR_UNIT);
		BatteryChargeState battery_state = battery_state_service_peek();
		update_btty(battery_state);
		update_blue_app(false);
		update_blue_kit(false);

		// Subscribe handlers
		tick_timer_service_subscribe(SECOND_UNIT, update_time);
		battery_state_service_subscribe(update_btty);
		connection_service_subscribe((ConnectionHandlers) {
			.pebble_app_connection_handler = update_blue_app,
			.pebblekit_connection_handler = update_blue_kit
		});
}


static void main_window_unload (Window *window) {
		// Unsubscribe handlers
		connection_service_unsubscribe();
		battery_state_service_unsubscribe();
		tick_timer_service_unsubscribe();
		// Destroy the layers
		layer_destroy(time_layer);
		layer_destroy(date_layer);
		layer_destroy(wday_layer);
		layer_destroy(btty_layer);
		layer_destroy(plug_layer);
		layer_destroy(chrg_layer);
		layer_destroy(blue_layer);
		layer_destroy(moon_layer);
}


static void init (void) {
		// Init the models
		scheme_light_on_dark(&scheme);
		init_time();
		init_date();
		init_wday();
		init_btty();
		init_blue();
		init_moon();
		// Create the window
		main_window = window_create();
		// Set the window handlers
		window_set_window_handlers(main_window, (WindowHandlers) {
				.load = main_window_load,
				.unload = main_window_unload,
		});
		// Push the window
		window_stack_push(main_window, true);
}


static void deinit (void) {
		// De-init the models
		deinit_time();
		deinit_date();
		deinit_wday();
		deinit_btty();
		deinit_blue();
		deinit_moon();
		// Destroy the window
		window_destroy(main_window);
}


int main (void) {
		init();
		app_event_loop();
		deinit();
}


/* EOF */
