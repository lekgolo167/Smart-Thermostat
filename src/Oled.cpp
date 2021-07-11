#include "Oled.h"

OLED::OLED() {

}

OLED::~OLED() {

}

void OLED::update_oled() {

}

void OLED::isr_button_A() {
	// Change to the previous menu
	oled_menu_state++;
	// reset scroll counter so it starts at the top and not where it was before
	oled_scroll_counter = 0;
	// TODO callback to update OLED display outside of interrupt
}

void OLED::isr_button_B() {
	// Change to the previous menu
	oled_menu_state--;
	// reset scroll counter so it starts at the top and not where it was before
	oled_scroll_counter = 0;
	// TODO callback to update OLED display outside of interrupt
}

void OLED::isr_rotary_btn() {
	edit_oled_menu = !edit_oled_menu;

	// If editing, get the corrisponding variable and copy it to a temporary variable
	if(edit_oled_menu) {

	}
	else { // If not editing set the temporary to the corrisponding var

	}
}

void OLED::isr_rotary() {
	PinStatus rotary_A_state = digitalRead(ROTARY_A_PIN);
	PinStatus rotary_B_state = digitalRead(ROTARY_B_PIN);
	int8_t direction = 0;
	if (rotary_A_state && !rotary_B_state) { // CW
		++direction;
	}
	else if (rotary_A_state && rotary_B_state) { // CCW
		--direction;
	}
	if (edit_oled_menu) {
		temporary_setting += direction;
	}
	else {
		oled_scroll_counter += direction;
	}
	// TODO call back to update OLED
}

void OLED::isr_motion() {

}

void OLED::menu_sensor_data() {

}
void OLED::menu_sample_settings() {

}
void OLED::menu_set_temperature() {

}
void OLED::menu_set_thresholds() {

}
void OLED::menu_motion_settings() {

}
void OLED::menu_date_and_time() {

}
void OLED::menu_current_cycle() {

}

void OLED::bound_scroll_counter(int8_t low, int8_t high, uint8_t height) {

}

int8_t OLED::line_selection[] = { -20, OLED_LINE_1_Y,OLED_LINE_2_Y ,OLED_LINE_3_Y ,OLED_LINE_4_Y };