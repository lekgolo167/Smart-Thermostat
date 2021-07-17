#pragma once

#include <stdint.h>
#include <Arduino.h>
#include <Adafruit_SSD1306.h>

#include "Constants.hpp"
#include "Thermostat.hpp"

#define OLED_NUM_MENUS 7

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define BUFFER_SIZE SCREEN_HEIGHT*SCREEN_WIDTH/8

#define OLED_TITLE_X      0
#define OLED_TITLE_Y      0 

#define OLED_LINE_1_X     0
#define OLED_LINE_1_Y     17

#define OLED_LINE_2_X     0
#define OLED_LINE_2_Y     26

#define OLED_LINE_3_X     0
#define OLED_LINE_3_Y     35

#define OLED_LINE_4_X     0
#define OLED_LINE_4_Y     44

#define FONT_SIZE_TITLE   2
#define FONT_SIZE_LINE    1

class OLED {
public:
	OLED(Adafruit_SSD1306* display, thermostat_settings* settings, sensor_readings* sensor);
	~OLED();
	void update_oled();
	static void isr_button_A();
	static void isr_button_B();
	static void isr_rotary_btn();
	static void isr_rotary();
	static void isr_motion();
private:
	void oled_draw_logo();
	void menu_sensor_data();
	void menu_sample_settings();
	void menu_set_temperature();
	void menu_set_thresholds();
	void menu_motion_settings();
	void menu_date_and_time();
	void menu_current_cycle();

	void update_user_settings();
	void update_temporary_setting_value();
	void bound_scroll_counter(int8_t low, int8_t high, uint8_t height);

	Adafruit_SSD1306* m_display;
	thermostat_settings* m_settings;
	sensor_readings* m_sensor;
	inline static int8_t oled_scroll_counter;
	inline static int8_t oled_menu_state;
	int8_t oled_menu_item;
	inline static int8_t temporary_setting;
	char buffer[25];
	inline static bool edit_oled_menu;
	bool oled_screen_ON;
	inline static bool update_temporary;
	inline static bool save_temporary;
	static int8_t line_selection[];
	enum menu_items { TARGET, THRESHOLDLOWER, THRESHOLDUPPER, BASELINE, TOTALSAMPLES, SAMPLEPERIOD, SCREENTIMEOUT, MOTIONDETECTION, SYNCRTC, CHANGEHOUR};

};
