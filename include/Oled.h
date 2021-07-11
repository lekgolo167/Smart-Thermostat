#pragma once

#include <stdint.h>
#include <Arduino.h>

#include "Constants.hpp"

#define OLED_NUM_MENUS 7

#define OLED_TITLE_X      0
#define OLED_TITLE_Y      0 
#define OLED_RECT_TITLE_X 0
#define OLED_RECT_TITLE_Y 0
#define OLED_RECT_TITLE_W 127
#define OLED_RECT_TITLE_H 18

#define OLED_LINE_1_X     0
#define OLED_LINE_1_Y     17

#define OLED_LINE_2_X     0
#define OLED_LINE_2_Y     27

#define OLED_LINE_3_X     0
#define OLED_LINE_3_Y     37

#define OLED_LINE_4_X     0
#define OLED_LINE_4_Y     47

#define FONT_SIZE_TITLE   2
#define FONT_SIZE_LINE    1

class OLED {
public:
	OLED();
	~OLED();
	void update_oled();
	void isr_button_A();
	void isr_button_B();
	void isr_rotary_btn();
	void isr_rotary();
	void isr_motion();
private:
	void menu_sensor_data();
	void menu_sample_settings();
	void menu_set_temperature();
	void menu_set_thresholds();
	void menu_motion_settings();
	void menu_date_and_time();
	void menu_current_cycle();

	void bound_scroll_counter(int8_t low, int8_t high, uint8_t height);

	int8_t oled_scroll_counter;
	int8_t oled_menu_state;
	int8_t oled_menu_item;
	int8_t temporary_setting;
	bool edit_oled_menu;
	bool oled_screen_ON;
	static int8_t line_selection[];
	enum menu_items { TARGET, THRESHOLDLOWER, THRESHOLDUPPER, BASELINE, TOTALSAMPLES, SAMPLEPERIOD, SCREENTIMEOUT, MOTIONDETECTION, SYNCRTC, CHANGEHOUR};

};
