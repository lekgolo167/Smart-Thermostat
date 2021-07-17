#include <Wire.h>

#include "Initialization.hpp"
#include "Constants.hpp"
#include "Oled.h"

void  initI2C()
{
  Wire.setClock(I2C_FREQ);
  Wire.begin();
}

void initGPIO(OLED& oled)
{
  // Buttons
  pinMode(BUTTON_A_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(BUTTON_A_PIN), oled.isr_button_A, RISING);
  pinMode(BUTTON_B_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(BUTTON_B_PIN), oled.isr_button_B, RISING);
  // Rotary Enocder
  pinMode(ROTARY_A_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(ROTARY_A_PIN), oled.isr_rotary, RISING);
  pinMode(ROTARY_B_PIN, INPUT);
  pinMode(ROTARY_BTN_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(ROTARY_BTN_PIN), oled.isr_rotary_btn, RISING);
  // Motion Sensor
  pinMode(MOTION_SENSOR_PIN, INPUT_PULLDOWN);
  attachInterrupt(digitalPinToInterrupt(MOTION_SENSOR_PIN), oled.isr_motion, RISING);
  // Furnace Relay
  pinMode(FURNACE_RELAY_PIN, OUTPUT);
  digitalWrite(FURNACE_RELAY_PIN, LOW);
}

void initTimers()
{

}

void initWiFi()
{

}
