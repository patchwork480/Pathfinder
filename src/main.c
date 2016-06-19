#include <pebble.h>
#include "pf_scheme.h"
#include "pf_time.h"
#include "pf_date.h"
#include "pf_wday.h"
#include "pf_btty.h"
#include "pf_moon.h"


char message_buffer[64];


static Window *main_window;
Layer *time_layer;
Layer *date_layer;
Layer *wday_layer;
Layer *btty_layer;
Layer *plug_layer;
Layer *chrg_layer;
Layer *moon_layer;


static void handle_time_changes (struct tm *tick_time, TimeUnits units_changed) {
		APP_LOG(APP_LOG_LEVEL_DEBUG, "handle_time_changes");
		if( last_mday != tick_time->tm_mday ) {
				last_year = tick_time->tm_year;
				last_mon = tick_time->tm_mon;
				last_mday = tick_time->tm_mday;
				strftime(date_buffer, sizeof(date_buffer), "%y %m-%d", tick_time);

				last_wday = tick_time->tm_wday;
				strftime(wday_buffer, sizeof(wday_buffer), "%a", tick_time);
				strupr(wday_buffer);

				snprintf(message_buffer, sizeof(message_buffer), "YMD: %d-%d-%d (%d)",
						last_year, last_mon, last_mday, last_wday);
				APP_LOG(APP_LOG_LEVEL_DEBUG, message_buffer);

				last_moon = tick_time->tm_mday;

				layer_mark_dirty(date_layer);
				layer_mark_dirty(wday_layer);
				layer_mark_dirty(moon_layer);
		}
		if( last_sec != tick_time->tm_sec ) {
				last_hour = tick_time->tm_hour;
				last_min = tick_time->tm_min;
				last_sec = tick_time->tm_sec;
				if(clock_is_24h_style()) {
						strftime(time_buffer, sizeof(time_buffer), "%k:%M:%S", tick_time);
				} else {
						strftime(time_buffer, sizeof(time_buffer), "%I:%M:%S", tick_time);
						if(time_buffer[0]=='0') {
								time_buffer[0] = ' ';
						}
				}

				snprintf(message_buffer, sizeof(message_buffer), "HMS: %d:%d:%d",
						last_hour, last_min, last_sec);
				APP_LOG(APP_LOG_LEVEL_DEBUG, message_buffer);

				layer_mark_dirty(time_layer);
		}
}


static void main_window_load (Window *window) {
		APP_LOG(APP_LOG_LEVEL_DEBUG, "main_window_load");

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

		// Force immediate draw
		time_t now = time(NULL);
		handle_time_changes(localtime(&now), YEAR_UNIT);
		BatteryChargeState battery_state = battery_state_service_peek();
		update_btty(battery_state);

		// Subscribe handlers
		tick_timer_service_subscribe(SECOND_UNIT, handle_time_changes);
		battery_state_service_subscribe(update_btty);
}


static void main_window_unload (Window *window) {
		// Unsubscribe handlers
		battery_state_service_unsubscribe();
		tick_timer_service_unsubscribe();
		// Destroy the layers
		layer_destroy(time_layer);
		layer_destroy(date_layer);
		layer_destroy(wday_layer);
		layer_destroy(btty_layer);
		layer_destroy(moon_layer);
}


static void init (void) {
		// Init the models
		scheme_light_on_dark(&scheme);
		init_time();
		init_date();
		init_wday();
		init_btty();
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
