#include "Oled.h"

OLED::OLED(Adafruit_SSD1306* display, thermostat_settings* settings, sensor_readings* sensor) {
	m_settings = settings;
	m_sensor = sensor;
	m_display = display;// new Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
	//m_display->begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS, -1, true);
	m_display->setTextColor(SSD1306_WHITE);
	edit_oled_menu = false;
	oled_menu_item = 0;
	oled_menu_state = 1;
	oled_screen_ON = true;
	oled_scroll_counter = 0;
	String s;
}

OLED::~OLED() {

}

void OLED::update_oled() {
	if (update_temporary) {
		update_temporary = false;
		update_temporary_setting_value();
	}
	else if (save_temporary) {
		save_temporary = false;
		update_user_settings();
	}

	switch (oled_menu_state) {
		case 0: {
			oled_draw_logo();
			break;
		}
		case 1: {
			menu_set_temperature();
			break;
		}
		case 2: {
			menu_sensor_data();
			break;
		}
		case 3: {
			menu_set_thresholds();
			break;
		}
		case 4: {
			menu_sample_settings();
			break;
		}
		case 5: {
			menu_motion_settings();
			break;
		}
		case 6: {
			menu_date_and_time();
			break;
		}
		case 7: {
			menu_current_cycle();
			break;
		}
		default: {
			if (oled_menu_state > 7 || oled_menu_state < 0) {
				oled_menu_state = 0;
			}
			update_oled();
			break;
		}
	}
}

void OLED::isr_button_A() {
	Serial.println("Forward");

	// // Change to the previous menu
	oled_menu_state++;
	// // reset scroll counter so it starts at the top and not where it was before
	oled_scroll_counter = 0;
	// // TODO callback to update OLED display outside of interrupt
}

void OLED::isr_button_B() {
	Serial.println("Back");
	// // Change to the previous menu
oled_menu_state--;
	// // reset scroll counter so it starts at the top and not where it was before
oled_scroll_counter = 0;
	// // TODO callback to update OLED display outside of interrupt
}

void OLED::isr_rotary_btn() {
Serial.println("ISR ROTARY BTN");
	edit_oled_menu = !edit_oled_menu;

	// If editing, get the corrisponding variable and copy it to a temporary variable
	if(edit_oled_menu) {
		update_temporary = true;
		Serial.println("Edit menu");
	}
	else { // If not editing set the temporary to the corrisponding var
		save_temporary = true;
		Serial.println("Save menu");
	}
}

void OLED::isr_rotary() {

	PinStatus rotary_A_state = digitalRead(ROTARY_A_PIN);
	PinStatus rotary_B_state = digitalRead(ROTARY_B_PIN);
	int8_t direction = 0;
	Serial.print("A: ");
	Serial.print(rotary_A_state);
	Serial.print(", B: ");
	Serial.print(rotary_B_state);
	if (rotary_A_state && !rotary_B_state) { // CCW
		--direction;
		Serial.println("--");
	}
	else if (rotary_A_state && rotary_B_state) { // CW
		++direction;
		Serial.println("++");
	}
	if (edit_oled_menu) {
		Serial.print("Temporary: ");
		temporary_setting += direction;
		Serial.println(temporary_setting);
	}
	else {
		Serial.print("Scroll counter: ");
		oled_scroll_counter += direction;
		Serial.println(oled_scroll_counter);
	}
	// TODO call back to update OLED
}

void OLED::isr_motion() {

}

void OLED::menu_set_temperature() {
	int8_t items[] = { -1, TARGET };

	// Clear OLED buffer
	m_display->clearDisplay();
	m_display->setTextSize(FONT_SIZE_TITLE);
	m_display->setCursor(0,0);

	// Draw the title
	m_display->println("Edit Temp");

	// Convert temperature to string
	sprintf(buffer, "Air:%.1fF\367", m_sensor->temperature_F);
	// Draw room temperature label at line 1
	m_display->setCursor(1,OLED_LINE_1_Y);
	m_display->println(buffer);

	// Convert target temperature to string
	if (edit_oled_menu && oled_menu_item == TARGET) {
		sprintf(buffer, "Set:%d.0F\367", temporary_setting);
	}
	else {
		sprintf(buffer, "Set:%.1fF\367", m_settings->target_temperature);
	}

	// Draw target temperature at line 3
	m_display->setCursor(1,OLED_LINE_3_Y);
	m_display->println(buffer);

	// Confine the scroll line of the menu
	bound_scroll_counter(3, 3, 16);

	// Save which item we are editing
	oled_menu_item = items[(oled_scroll_counter-2)];

	// Send the buffer to OLED RAM
	m_display->display();
}

void OLED::menu_sensor_data() {
	// Clear OLED buffer
	m_display->clearDisplay();
	m_display->setTextSize(FONT_SIZE_TITLE);
	m_display->setCursor(0,0);

	// Draw the title
	m_display->println("Sensors");
	m_display->setTextSize(FONT_SIZE_LINE);

	// Convert celcius temperature to string
	sprintf(buffer, "HDC1080:  %.1f C\367", m_sensor->temperature_C);

	// Draw celcius temperature at line 1
	m_display->setCursor(1,OLED_LINE_1_Y);
	m_display->println(buffer);

	// Convert fahrenheit temperature to string
	sprintf(buffer, "HDC1080:  %.1f F\367", m_sensor->temperature_F);

	// Draw fahrenheit temperature at line 2
	m_display->setCursor(1,OLED_LINE_2_Y);
	m_display->println(buffer);

	// Convert humidity to string
	sprintf(buffer, "Humidity: %.1f %%", m_sensor->humidity);

	// Draw humidity at line 3
	m_display->setCursor(1,OLED_LINE_3_Y);
	m_display->println(buffer);

	// Convert average temperature to string
	sprintf(buffer, "Average:  %.1f F\367", m_sensor->average_temperature);

	// Draw humidity at line 4
	m_display->setCursor(1,OLED_LINE_4_Y);
	m_display->println(buffer);

	// Send the buffer to OLED RAM
	m_display->display();
}

void OLED::menu_sample_settings() {
	int8_t items[] = { -1, TOTALSAMPLES, SAMPLEPERIOD };

	// Clear OLED buffer
	m_display->clearDisplay();
	m_display->setTextSize(FONT_SIZE_TITLE);
	m_display->setCursor(0,0);

	// Draw the title
	m_display->println("Settings");
	m_display->setTextSize(FONT_SIZE_LINE);

	// Switch between edited value and set value
	if (edit_oled_menu && oled_menu_item == TOTALSAMPLES) {
		sprintf(buffer, "Total Samples: %d", temporary_setting);
	}
	else {
		sprintf(buffer, "Total Samples: %d", m_settings->total_samples);
	}
	// Draw total samples at line 1
	m_display->setCursor(1,OLED_LINE_1_Y);
	m_display->println(buffer);

	// Switch between edited value and set value
	if (edit_oled_menu && oled_menu_item == SAMPLEPERIOD) {
		sprintf(buffer, "Sample Period: %ds", temporary_setting);
		
	}
	else {
		sprintf(buffer, "Sample Period: %ds", m_settings->sample_period_sec);

	}
	// Draw sample period in seconds at line 2
	m_display->setCursor(1,OLED_LINE_2_Y);
	m_display->println(buffer);

	// Confine the scroll line of the menu
	bound_scroll_counter(1, 2, 9);

	// Save which item we are editing
	oled_menu_item = items[oled_scroll_counter];

	// Send the buffer to OLED RAM
	m_display->display();
}

void OLED::menu_set_thresholds() {
	int8_t items[] = {-1, THRESHOLDLOWER, THRESHOLDUPPER, BASELINE};

	// Clear OLED buffer
	m_display->clearDisplay();
	m_display->setTextSize(FONT_SIZE_TITLE);
	m_display->setCursor(0,0);

	// Draw the title
	m_display->println("Settings");
	m_display->setTextSize(FONT_SIZE_LINE);
	// Switch between edited value and set value
	if (edit_oled_menu && oled_menu_item == THRESHOLDLOWER) {
		sprintf(buffer, "Thresh Lower:  %d.0 F\367", temporary_setting);
	}
	else {
		sprintf(buffer, "Thresh Lower:  %.1f F\367", m_settings->lower_threshold);
	}
	// Draw lower threshold at line 1
	m_display->setCursor(1,OLED_LINE_1_Y);
	m_display->println(buffer);

	// Switch between edited value and set value
	if (edit_oled_menu && oled_menu_item == THRESHOLDUPPER) {
		sprintf(buffer, "Thresh Upper:  %d.0 F\367", temporary_setting);
	}
	else {
		sprintf(buffer, "Thresh Upper:  %.1f F\367", m_settings->upper_threshold);
	}
	// Draw upper threshold at line 2
	m_display->setCursor(1,OLED_LINE_2_Y);
	m_display->println(buffer);

	// Switch between edited value and set value
	if (edit_oled_menu && oled_menu_item == BASELINE) {
		sprintf(buffer, "Baseline:     %d.0 F\367", temporary_setting);
	}
	else {
		sprintf(buffer, "Baseline:     %.1f F\367", m_settings->baseline_temperature);
	}

	// Draw baseline temperautre at line 3
	m_display->setCursor(1,OLED_LINE_3_Y);
	m_display->println(buffer);

	// Confine the scroll line of the menu
	bound_scroll_counter(1, 3, 9);

	// Save which item we are editing
	oled_menu_item = items[oled_scroll_counter];

	// Send the buffer to OLED RAM
	m_display->display();
}

void OLED::menu_motion_settings() {
	int8_t items[] = { -1, SCREENTIMEOUT, MOTIONDETECTION };

	// Clear OLED buffer
	m_display->clearDisplay();
	m_display->setTextSize(FONT_SIZE_TITLE);
	m_display->setCursor(0,0);
	
	// Draw the title
	m_display->println("Settings");
	m_display->setTextSize(FONT_SIZE_LINE);

	// Switch between edited value and set value
	if (edit_oled_menu && oled_menu_item == SCREENTIMEOUT) {
		sprintf(buffer, "Screen Timeout: %ds", temporary_setting);
	}
	else {
		sprintf(buffer, "Screen Timeout: %ds", m_settings->screen_timeout_sec);
	}
	// Draw a screen timeout at line 1
	m_display->setCursor(1,OLED_LINE_1_Y);
	m_display->println(buffer);

	// Switch between edited value and set value
	if (edit_oled_menu && oled_menu_item == MOTIONDETECTION) {
		sprintf(buffer, "Away Time: %d hr", temporary_setting);
	}
	else {
		// Also, covnert seconds to hours
		sprintf(buffer, "Away Time: %d hr", m_settings->motion_timeout_sec / 3600);
	}
	// Draw away time at line 2
	m_display->setCursor(1,OLED_LINE_2_Y);
	m_display->println(buffer);

	// Confine the scroll line of the menu
	bound_scroll_counter(1, 2, 9);

	// Save which item we are editing
	oled_menu_item = items[oled_scroll_counter];

	// Send the buffer to OLED RAM
	m_display->display();
}

void OLED::menu_date_and_time() {

	int8_t items[] = { -1, -1,SYNCRTC, CHANGEHOUR };

	// Clear OLED buffer
	m_display->clearDisplay();
	m_display->setTextSize(FONT_SIZE_TITLE);
	m_display->setCursor(0,0);
	
	// Draw the title
	m_display->println("Time");
	m_display->setTextSize(FONT_SIZE_LINE);

	// Draw date at line 1
	//m_display->println(displayTimeBuffer);

	// Draw sync option on line 2
	m_display->println("Sync RTC Time  'OK'");

	// Switch between edited value and set value
	if (edit_oled_menu && oled_menu_item == CHANGEHOUR) {
		sprintf(buffer, "Hour set +/-: %d hr", temporary_setting);
	}
	else {
		// Also, covnert seconds to hours
		sprintf(buffer, "Hour set +/-: %d hr", 0);
	}

	// Draw sync option on line 2
	m_display->println(buffer);

	// Draw timezone name
	char* timezone_name = getenv("TZ");
	m_display->println(timezone_name);


	// Confine the scroll line of the menu
	bound_scroll_counter(2, 3, 9);

	// Save which item we are editing
	oled_menu_item = items[oled_scroll_counter];

	// Send the buffer to OLED RAM
	m_display->display();
}

void OLED::menu_current_cycle() {
	// Clear OLED buffer
	m_display->clearDisplay();
	m_display->setTextSize(FONT_SIZE_TITLE);
	m_display->setCursor(0,0);
	
	// Draw the title
	m_display->println("Cycle Info");
	m_display->setTextSize(FONT_SIZE_LINE);

	// Draw start time on line 1
	sprintf(buffer, "Start time %02d:%02d", m_settings->current_cycle->start_hour, m_settings->current_cycle->start_min);
	m_display->println(buffer);
	
	// Draw end time on line 2
	// TODO fix this
	// if (m_settings->current_cycle->prev != NULL)
	// 	sprintf(buffer, "End time   %02d:%02d", m_settings->current_cycle->prev->start_hour, m_settings->current_cycle->prev->start_min);
	// else
	// 	sprintf(buffer, "End time   %02d:%02d", 0,0);
	// m_display->println(buffer);

	// Draw runtime on line 3
	// TODO fix this
	// sprintf(buffer, "Runtime %d min", furnaceRunTime / 60);
	// m_display->println(buffer);

	// Send the buffer to OLED RAM
	m_display->display();
}



void OLED::update_user_settings() {
switch (oled_menu_item)
	{
	case TARGET:
	{
		if (temporary_setting >= m_settings->baseline_temperature && temporary_setting <= 95) {
			// TODO fix this
			// m_settings->temporaryTarget = m_settings->targetTemp_F;
			m_settings->target_temperature = temporary_setting;
			// startTemporaryTimer = true;
			//sprintf(CURLMessageBuffer, "TARGET=%f&THRESH_L=%f&THRESH_H=%f", m_settings->targetTemp_F, m_settings->lower_threshold, m_settings->upper_threshold);
			//sendCURL(URL_STATS, CURLMessageBuffer);
		}
	}
	break;
	case THRESHOLDLOWER:
	{
		if (temporary_setting >= 0 && temporary_setting <= 5) {
			m_settings->lower_threshold = temporary_setting;
			//sprintf(CURLMessageBuffer, "TARGET=%f&THRESH_L=%f&THRESH_H=%f", m_settings->targetTemp_F, m_settings->lower_threshold, m_settings->upper_threshold);
			//sendCURL(URL_STATS, CURLMessageBuffer);
		}
	}
	break;
	case THRESHOLDUPPER:
	{
		if (temporary_setting >= 0 && temporary_setting <= 5) {
			m_settings->upper_threshold = temporary_setting;
			//sprintf(CURLMessageBuffer, "TARGET=%f&THRESH_L=%f&THRESH_H=%f", m_settings->targetTemp_F, m_settings->lower_threshold, m_settings->upper_threshold);
			//sendCURL(URL_STATS, CURLMessageBuffer);
		}
	}
	break;
	case BASELINE:
	{
		if (temporary_setting >= 45 && temporary_setting <= 60)
			m_settings->baseline_temperature = temporary_setting;
	}
	break;
	case TOTALSAMPLES:
	{
		if (temporary_setting >= 1 && temporary_setting <= 20)
			m_settings->total_samples = temporary_setting;
	}
	break;
	case SAMPLEPERIOD:
	{
		if (temporary_setting >= 5 && temporary_setting <= 300) {
			// TODO fix this
			//reconfigureTimer = true;
			m_settings->sample_period_sec = temporary_setting;
		}
	}
	break;
	case SCREENTIMEOUT:
	{
		if (temporary_setting >= 1 && temporary_setting <= 180)
			m_settings->screen_timeout_sec = temporary_setting;
	}
	break;
	case MOTIONDETECTION:
	{
		if(temporary_setting >= 6 && temporary_setting <= 96)
			m_settings->motion_timeout_sec = temporary_setting * 3600; // convert to seconds from hours
	}
	case CHANGEHOUR:
	{
		// TODO fix this
		// if (temporary_setting >= -1 && temporary_setting <= 1) {

		// 	char* timezone_name = getenv("TZ");
		// 	timezone_name[4] += temporary_setting;
		// 	setenv("TZ", timezone_name, 1);
		// 	Log_Debug("Timezone name: %s", timezone_name);
		// }
	}
	break;
	default:
		break;
	}
}

void OLED::update_temporary_setting_value() {
switch (oled_menu_item)
	{
	case TARGET:
	{
		temporary_setting = m_settings->target_temperature;
	}
	break;
	case THRESHOLDLOWER:
	{
		temporary_setting = m_settings->lower_threshold;
	}
	break;
	case THRESHOLDUPPER:
	{
		temporary_setting = m_settings->upper_threshold;
	}
	break;
	case BASELINE:
	{
		temporary_setting = m_settings->baseline_temperature;
	}
	break;
	case TOTALSAMPLES:
	{
		temporary_setting = m_settings->total_samples;
	}
	break;
	case SAMPLEPERIOD:
	{
		temporary_setting = m_settings->sample_period_sec;
	}
	break;
	case SCREENTIMEOUT:
	{
		temporary_setting = m_settings->screen_timeout_sec;
	}
	break;
	case MOTIONDETECTION:
	{
		temporary_setting = m_settings->motion_timeout_sec/3600; // convert from seconds to hours
	}
	break;
	case CHANGEHOUR:
	{
		temporary_setting = 0;
	}
	break;
	case SYNCRTC:
	{
		// TODO fix this
		// if (clock_systohc() == -1) {
		// 	Log_Debug("ERROR: clock_systohc failed with error code: %s (%d).\n", strerror(errno),errno);
		// 	return;
		// }
		// edit_oled_menu = false;
		// Log_Debug("Synchronized system time to the RTC\n");
	}
	break;
	default:
		break;
	}
}

void OLED::bound_scroll_counter(int8_t low, int8_t high, uint8_t height) {
	if (oled_scroll_counter > high) {
		oled_scroll_counter = high;
	}
	else if (oled_scroll_counter < low -1) {
		oled_scroll_counter = low -1;
	}
	if (oled_scroll_counter >= low)
		m_display->fillRect(0, line_selection[oled_scroll_counter]-1,SCREEN_WIDTH, height, SSD1306_INVERSE);
}

int8_t OLED::line_selection[] = { -20, OLED_LINE_1_Y,OLED_LINE_2_Y ,OLED_LINE_3_Y ,OLED_LINE_4_Y };

// AVNET logoS
const uint8_t Image_avnet_bmp[BUFFER_SIZE] =
{
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,128,240,240,240,240, 48,  0,  0,112,
  240,240,240,224,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,112,
  240,240,240,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,224,240,240,
  240, 16,  0,  0,  0,  0,  0,  0,  0,  0,240,240,240,240,224,128,
	0,  0,  0,  0,  0,  0,  0,  0,240,240,240,240,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,240,240,240,240,112,112,112,112,112,112,
  112,112,112,112,112,  0,  0,  0,  0,  0,  0,  0,  0,112,112,112,
  112,112,112,112,240,240,240,240,112,112,112,112,112,112,  0,  0,
	0,  0,  0,  0,  0,224,252,255,255,255, 15,  1,  0,  0,  0,  0,
	3, 15,127,255,255,248,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	7, 31,255,255,254,240,  0,  0,  0,  0,224,248,255,255,127,  7,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,255,255,255,255, 15, 31,
  127,252,248,224,224,128,  0,  0,255,255,255,255,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,255,255,255,255,224,224,224,224,224,224,
  224,224,224,224,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,255,255,255,255,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,128,240,254,255,127, 15,  1,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  3, 31,255,255,252,224,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  7, 63,255,255,248,240,254,255,255, 31,  3,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,255,255,255,255,  0,  0,
	0,  1,  3, 15, 15, 63,126,252,255,255,255,255,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,255,255,255,255,129,129,129,129,129,129,
  129,129,129,129,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,255,255,255,255,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  7,  7,  7,  3,  0,  0,  0, 12, 14, 14, 14, 14, 14, 14,
   14, 14, 12,  0,  0,  0,  7,  7,  7,  7,  4,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  1,  7,  7,  7,  7,  1,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  7,  7,  7,  7,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  1,  3,  7,  7,  7,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,
	7,  7,  7,  7,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  7,  7,  7,  7,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
};
void OLED::oled_draw_logo() {
	m_display->clearDisplay();
	// Copy image_avnet to OLED buffer
	m_display->drawBitmap(0,0,Image_avnet_bmp,128,64,SSD1306_WHITE);
	// Send the buffer to OLED RAM
	m_display->display();

}