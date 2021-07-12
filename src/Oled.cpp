#include "Oled.h"

OLED::OLED() {
	edit_oled_menu = false;
	oled_menu_item = 0;
	oled_menu_state = 0;
	oled_screen_ON = true;
	oled_scroll_counter = 0;
}

OLED::~OLED() {

}

void OLED::update_oled() {
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
	// Clear OLED buffer
	clear_oled_buffer();

	// Draw the title
	sd1306_draw_string(OLED_TITLE_X, OLED_TITLE_Y, "Sensor Data", FONT_SIZE_TITLE, white_pixel);

	// Convert celcius temperature to string
	sprintf(buffer, "HDC1080:  %.1f C�\0", sensor->temp_C);

	// Draw celcius temperature at line 1
	sd1306_draw_string(OLED_LINE_1_X, OLED_LINE_1_Y, buffer, FONT_SIZE_LINE, white_pixel);

	// Convert fahrenheit temperature to string
	sprintf(buffer, "HDC1080:  %.1f F�\0", sensor->temp_F);

	// Draw fahrenheit temperature at line 2
	sd1306_draw_string(OLED_LINE_2_X, OLED_LINE_2_Y, buffer, FONT_SIZE_LINE, white_pixel);

	// Convert humidity to string
	sprintf(buffer, "Humidity: %.1f %%\0", sensor->humidity);

	// Draw humidity at line 3
	sd1306_draw_string(OLED_LINE_3_X, OLED_LINE_3_Y, buffer, FONT_SIZE_LINE, white_pixel);

	// Convert average temperature to string
	sprintf(buffer, "Average:  %.1f F�\0", averageTemp_F);

	// Draw humidity at line 3
	sd1306_draw_string(OLED_LINE_4_X, OLED_LINE_4_Y, buffer, FONT_SIZE_LINE, white_pixel);

	// Send the buffer to OLED RAM
	sd1306_refresh();
}

void OLED::menu_sample_settings() {
	int8_t items[] = { -1, TOTALSAMPLES, SAMPLEPERIOD };

	// Clear OLED buffer
	clear_oled_buffer();

	// Draw the title
	sd1306_draw_string(OLED_TITLE_X, OLED_TITLE_Y, "Settings", FONT_SIZE_TITLE, white_pixel);

	// Switch between edited value and set value
	if (edit_oled_menu && oled_menu_item == TOTALSAMPLES) {
		sprintf(buffer, "Total Samples: %d\0", temporary_setting);
	}
	else {
		sprintf(buffer, "Total Samples: %d\0", settings->totalSamples);
	}
	// Draw total samples at line 1
	sd1306_draw_string(OLED_LINE_1_X, OLED_LINE_1_Y, buffer, FONT_SIZE_LINE, white_pixel);

	// Switch between edited value and set value
	if (edit_oled_menu && oled_menu_item == SAMPLEPERIOD) {
		sprintf(buffer, "Sample Period: %ds\0", temporary_setting);
		
	}
	else {
		sprintf(buffer, "Sample Period: %ds\0", settings->samplePeriod.tv_sec);

	}
	// Draw sample period in seconds at line 2
	sd1306_draw_string(OLED_LINE_2_X, OLED_LINE_2_Y, buffer, FONT_SIZE_LINE, white_pixel);

	// Confine the scroll line of the menu
	bound_scroll_counter(1, 2, 9);

	// Save which item we are editing
	oled_menu_item = items[oled_scroll_counter];

	// Send the buffer to OLED RAM
	sd1306_refresh();
}

void OLED::menu_set_temperature() {
	int8_t items[] = { -1, TARGET };

	// Clear OLED buffer
	clear_oled_buffer();

	// Draw the title
	sd1306_draw_string(OLED_TITLE_X, OLED_TITLE_Y, "Edit Temp", FONT_SIZE_TITLE, white_pixel);

	// Convert temperature to string
	sprintf(buffer, "Air: %.1fF�\0", sensor->temp_F);

	// Draw room temperature label at line 1
	sd1306_draw_string(OLED_LINE_1_X, OLED_LINE_1_Y, buffer, FONT_SIZE_TITLE, white_pixel);

	// Convert target temperature to string
	if (edit_oled_menu && oled_menu_item == TARGET) {
		sprintf(buffer, "Set: %d.0F�\0", temporary_setting);
	}
	else {
		sprintf(buffer, "Set: %.1fF�\0", settings->targetTemp_F);
	}

	// Draw target temperature at line 2
	sd1306_draw_string(OLED_LINE_2_X, OLED_LINE_3_Y, buffer, FONT_SIZE_TITLE, white_pixel);

	// Confine the scroll line of the menu
	bound_scroll_counter(3, 3, 15);

	// Save which item we are editing
	oled_menu_item = items[(oled_scroll_counter-2)];

	// Send the buffer to OLED RAM
	sd1306_refresh();
}

void OLED::menu_set_thresholds() {
	int8_t items[] = {-1, THRESHOLDLOWER, THRESHOLDUPPER, BASELINE};

	// Clear OLED buffer
	clear_oled_buffer();

	// Draw the title
	sd1306_draw_string(OLED_TITLE_X, OLED_TITLE_Y, "Settings", FONT_SIZE_TITLE, white_pixel);

	// Switch between edited value and set value
	if (edit_oled_menu && oled_menu_item == THRESHOLDLOWER) {
		sprintf(buffer, "Thresh Lower:  %d.0 F�\0", temporary_setting);
	}
	else {
		sprintf(buffer, "Thresh Lower:  %.1f F�\0", settings->lower_threshold);
	}
	// Draw lower threshold at line 1
	sd1306_draw_string(OLED_LINE_1_X, OLED_LINE_1_Y, buffer, FONT_SIZE_LINE, white_pixel);

	// Switch between edited value and set value
	if (edit_oled_menu && oled_menu_item == THRESHOLDUPPER) {
		sprintf(buffer, "Thresh Upper:  %d.0 F�\0", temporary_setting);
	}
	else {
		sprintf(buffer, "Thresh Upper:  %.1f F�\0", settings->upper_threshold);
	}
	// Draw upper threshold at line 2
	sd1306_draw_string(OLED_LINE_2_X, OLED_LINE_2_Y, buffer, FONT_SIZE_LINE, white_pixel);

	// Switch between edited value and set value
	if (edit_oled_menu && oled_menu_item == BASELINE) {
		sprintf(buffer, "Baseline:     %d.0 F�\0", temporary_setting);
	}
	else {
		sprintf(buffer, "Baseline:     %.1f F�\0", settings->baselineTemp_F);
	}

	// Draw baseline temperautre at line 3
	sd1306_draw_string(OLED_LINE_3_X, OLED_LINE_3_Y, buffer, FONT_SIZE_LINE, white_pixel);

	// Confine the scroll line of the menu
	bound_scroll_counter(1, 3, 9);

	// Save which item we are editing
	oled_menu_item = items[oled_scroll_counter];

	// Send the buffer to OLED RAM
	sd1306_refresh();
}

void OLED::menu_motion_settings() {
	int8_t items[] = { -1, SCREENTIMEOUT, MOTIONDETECTION };

	// Clear OLED buffer
	clear_oled_buffer();

	// Draw the title
	sd1306_draw_string(OLED_TITLE_X, OLED_TITLE_Y, "Settings", FONT_SIZE_TITLE, white_pixel);

	// Switch between edited value and set value
	if (edit_oled_menu && oled_menu_item == SCREENTIMEOUT) {
		sprintf(buffer, "Screen Timeout: %ds\0", temporary_setting);
	}
	else {
		sprintf(buffer, "Screen Timeout: %ds\0", settings->screenTimeoutSec);
	}
	// Draw a screen timeout at line 1
	sd1306_draw_string(OLED_LINE_1_X, OLED_LINE_1_Y, buffer, FONT_SIZE_LINE, white_pixel);

	// Switch between edited value and set value
	if (edit_oled_menu && oled_menu_item == MOTIONDETECTION) {
		sprintf(buffer, "Away Time: %d hr\0", temporary_setting);
	}
	else {
		// Also, covnert seconds to hours
		sprintf(buffer, "Away Time: %d hr\0", settings->motionDetectorSec / 3600);
	}
	// Draw away time at line 2
	sd1306_draw_string(OLED_LINE_2_X, OLED_LINE_2_Y, buffer, FONT_SIZE_LINE, white_pixel);

	// Confine the scroll line of the menu
	bound_scroll_counter(1, 2, 9);

	// Save which item we are editing
	oled_menu_item = items[oled_scroll_counter];

	// Send the buffer to OLED RAM
	sd1306_refresh();
}

void OLED::menu_date_and_time() {

	int8_t items[] = { -1, -1,SYNCRTC, CHANGEHOUR };

	struct timespec currentTime;
	if (clock_gettime(CLOCK_REALTIME, &currentTime) == -1) {
		Log_Debug("ERROR: clock_gettime failed with error code: %s (%d).\n", strerror(errno),
			errno);
		return;
	}
	char displayTimeBuffer[26];
	if (!asctime_r((localtime(&currentTime.tv_sec)), (char *restrict) & displayTimeBuffer)) {
		Log_Debug("ERROR: asctime_r failed with error code: %s (%d).\n", strerror(errno),
			errno);
		return;
	}
	// Remove the new line at the end of 'displayTimeBuffer'
	displayTimeBuffer[strlen(displayTimeBuffer) - 5] = '\0';

	// Clear OLED buffer
	clear_oled_buffer();

	// Draw the title
	sd1306_draw_string(OLED_TITLE_X, OLED_TITLE_Y, "Time", FONT_SIZE_TITLE, white_pixel);

	// Draw date at line 1
	sd1306_draw_string(OLED_LINE_1_X, OLED_LINE_1_Y, displayTimeBuffer, FONT_SIZE_LINE, white_pixel);

	// Draw sync option on line 2
	sd1306_draw_string(OLED_LINE_2_X, OLED_LINE_2_Y, "Sync RTC Time  'OK'", FONT_SIZE_LINE, white_pixel);

	// Switch between edited value and set value
	if (edit_oled_menu && oled_menu_item == CHANGEHOUR) {
		sprintf(buffer, "Hour set +/-: %d hr\0", temporary_setting);
	}
	else {
		// Also, covnert seconds to hours
		sprintf(buffer, "Hour set +/-: %d hr\0", 0);
	}

	// Draw sync option on line 2
	sd1306_draw_string(OLED_LINE_3_X, OLED_LINE_3_Y,  buffer, FONT_SIZE_LINE, white_pixel);

	// Draw timezone name
	char* timezone_name = getenv("TZ");
	sd1306_draw_string(OLED_LINE_3_X, OLED_LINE_4_Y, timezone_name, FONT_SIZE_LINE, white_pixel);


	// Confine the scroll line of the menu
	bound_scroll_counter(2, 3, 9);

	// Save which item we are editing
	oled_menu_item = items[oled_scroll_counter];

	// Send the buffer to OLED RAM
	sd1306_refresh();
}

void OLED::menu_current_cycle() {
	// Clear OLED buffer
	clear_oled_buffer();

	// Draw the title
	sd1306_draw_string(OLED_TITLE_X, OLED_TITLE_Y, "Cycle Info", FONT_SIZE_TITLE, white_pixel);

	// Draw start time on line 1
	sprintf(buffer, "Start time %02d:%02d\0", settings->currentCycle->start_hour, settings->currentCycle->start_min);
	sd1306_draw_string(OLED_LINE_1_X, OLED_LINE_1_Y, buffer, FONT_SIZE_LINE, white_pixel);
	
	// Draw end time on line 2
	if (settings->currentCycle->prev != NULL)
		sprintf(buffer, "End time   %02d:%02d\0", settings->currentCycle->prev->start_hour, settings->currentCycle->prev->start_min);
	else
		sprintf(buffer, "End time   %02d:%02d\0", 0,0);
	sd1306_draw_string(OLED_LINE_2_X, OLED_LINE_2_Y, buffer, FONT_SIZE_LINE, white_pixel);

	// Draw runtime on line 3
	sprintf(buffer, "Runtime %d min\0", furnaceRunTime / 60);
	sd1306_draw_string(OLED_LINE_3_X, OLED_LINE_3_Y, buffer, FONT_SIZE_LINE, white_pixel);

	// Send the buffer to OLED RAM
	sd1306_refresh();
}

void OLED::oled_draw_logo() {
	// Copy image_avnet to OLED buffer
	sd1306_draw_img(Image_avnet_bmp);

	// Send the buffer to OLED RAM
	sd1306_refresh();
}

void OLED::update_user_settings() {
switch (oled_menu_item)
	{
	case TARGET:
	{
		if (temporary_setting >= settings->baselineTemp_F && temporary_setting <= 95) {
			settings->temporaryTarget = settings->targetTemp_F;
			settings->targetTemp_F = temporary_setting;
			startTemporaryTimer = true;
			sprintf(CURLMessageBuffer, "TARGET=%f&THRESH_L=%f&THRESH_H=%f\0", settings->targetTemp_F, settings->lower_threshold, settings->upper_threshold);
			sendCURL(URL_STATS, CURLMessageBuffer);
		}
	}
	break;
	case THRESHOLDLOWER:
	{
		if (temporary_setting >= 0 && temporary_setting <= 5) {
			settings->lower_threshold = temporary_setting;
			sprintf(CURLMessageBuffer, "TARGET=%f&THRESH_L=%f&THRESH_H=%f\0", settings->targetTemp_F, settings->lower_threshold, settings->upper_threshold);
			sendCURL(URL_STATS, CURLMessageBuffer);
		}
	}
	break;
	case THRESHOLDUPPER:
	{
		if (temporary_setting >= 0 && temporary_setting <= 5) {
			settings->upper_threshold = temporary_setting;
			sprintf(CURLMessageBuffer, "TARGET=%f&THRESH_L=%f&THRESH_H=%f\0", settings->targetTemp_F, settings->lower_threshold, settings->upper_threshold);
			sendCURL(URL_STATS, CURLMessageBuffer);
		}
	}
	break;
	case BASELINE:
	{
		if (temporary_setting >= 45 && temporary_setting <= 60)
			settings->baselineTemp_F = temporary_setting;
	}
	break;
	case TOTALSAMPLES:
	{
		if (temporary_setting >= 1 && temporary_setting <= 20)
			settings->totalSamples = temporary_setting;
	}
	break;
	case SAMPLEPERIOD:
	{
		if (temporary_setting >= 5 && temporary_setting <= 300) {
			reconfigureTimer = true;
			struct timespec t = { temporary_setting, 0 };
			settings->samplePeriod = t;
		}
	}
	break;
	case SCREENTIMEOUT:
	{
		if (temporary_setting >= 1 && temporary_setting <= 180)
			settings->screenTimeoutSec = temporary_setting;
	}
	break;
	case MOTIONDETECTION:
	{
		if(temporary_setting >= 6 && temporary_setting <= 96)
			settings->motionDetectorSec = temporary_setting * 3600; // convert to seconds from hours
	}
	case CHANGEHOUR:
	{
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
		temporary_setting = settings->targetTemp_F;
	}
	break;
	case THRESHOLDLOWER:
	{
		temporary_setting = settings->lower_threshold;
	}
	break;
	case THRESHOLDUPPER:
	{
		temporary_setting = settings->upper_threshold;
	}
	break;
	case BASELINE:
	{
		temporary_setting = settings->baselineTemp_F;
	}
	break;
	case TOTALSAMPLES:
	{
		temporary_setting = settings->totalSamples;
	}
	break;
	case SAMPLEPERIOD:
	{
		temporary_setting = settings->samplePeriod.tv_sec;
	}
	break;
	case SCREENTIMEOUT:
	{
		temporary_setting = settings->screenTimeoutSec;
	}
	break;
	case MOTIONDETECTION:
	{
		temporary_setting = settings->motionDetectorSec/3600; // convert from seconds to hours
	}
	break;
	case CHANGEHOUR:
	{
		temporary_setting = 0;
	}
	break;
	case SYNCRTC:
	{
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
		sd1306_invert_line(0, OLED_WIDTH, line_selection[oled_scroll_counter] - 1, line_selection[oled_scroll_counter] + height);
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
