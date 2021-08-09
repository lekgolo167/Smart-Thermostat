#include "Initialization.hpp"
#include "Timers.hpp"
#include "MesgQueue.hpp"

static void isr_button_A() {
	Serial.println("Forward");
  global_msg_queue->push(OLED_NEXT_MENU);
}

static void isr_button_B() {
	Serial.println("Back");
  global_msg_queue->push(OLED_PREV_MENU);
}

static void isr_rotary_btn() {
  Serial.println("Edit");
  global_msg_queue->push(OLED_EDIT_MENU);
}

static void isr_rotary() {

	PinStatus rotary_A_state = digitalRead(ROTARY_A_PIN);
	PinStatus rotary_B_state = digitalRead(ROTARY_B_PIN);

	Serial.print("A: ");
	Serial.print(rotary_A_state);
	Serial.print(", B: ");
	Serial.print(rotary_B_state);
	if (rotary_A_state && !rotary_B_state) { // CCW
    global_msg_queue->push(OLED_ROTARY_CCW);
		Serial.println("--");
	}
	else if (rotary_A_state && rotary_B_state) { // CW
    global_msg_queue->push(OLED_ROTARY_CW);
		Serial.println("++");
	}

}

static void isr_motion() {
  global_msg_queue->push(MOTION_DETECTED);
}

static void isr_rtc_alarm() {
  global_msg_queue->push(RTC_UPDATE);
}

void  initI2C()
{
  Wire.setClock(I2C_FREQ);
  Wire.begin();
}

void initGPIO()
{
  // Buttons
  pinMode(BUTTON_A_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(BUTTON_A_PIN), isr_button_A, RISING);
  pinMode(BUTTON_B_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(BUTTON_B_PIN), isr_button_B, RISING);
  // Rotary Enocder
  pinMode(ROTARY_A_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(ROTARY_A_PIN), isr_rotary, RISING);
  pinMode(ROTARY_B_PIN, INPUT_PULLUP);
  pinMode(ROTARY_BTN_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(ROTARY_BTN_PIN), isr_rotary_btn, RISING);
  // Motion Sensor
  pinMode(MOTION_SENSOR_PIN, INPUT_PULLDOWN);
  attachInterrupt(digitalPinToInterrupt(MOTION_SENSOR_PIN), isr_motion, RISING);
  // // Furnace Relay
  pinMode(FURNACE_RELAY_PIN, OUTPUT);
  digitalWrite(FURNACE_RELAY_PIN, LOW);
}

void initTimers()
{
  TC4_configure(30, 3);
  TC4_start_timer();
}

void initWiFi()
{

}

void initRTC(RTCZero& rtc) {
  rtc.begin();
  rtc.setTime(23,58,0);
  rtc.setDate(8,8,21);

  rtc.setAlarmTime(1,0,0);
  rtc.enableAlarm(rtc.MATCH_SS);
  rtc.attachInterrupt(isr_rtc_alarm);
}