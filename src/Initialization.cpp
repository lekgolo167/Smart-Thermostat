#include <Wire.h>

#include "Initialization.hpp"
#include "Constants.hpp"

void  initI2C()
{
  Wire.setClock(I2C_FREQ);
  Wire.begin();
}

void initGPIO()
{
  // Buttons
  pinMode(BUTTON_A_PIN, INPUT);
  //attachInterrupt(digitalPinToInterrupt(BUTTON_A_PIN), isr, RISING);
  pinMode(BUTTON_B_PIN, INPUT);
  //attachInterrupt(digitalPinToInterrupt(BUTTON_B_PIN), isr, RISING);
  // Rotary Enocder
  pinMode(ROTARY_A_PIN, INPUT);
  //attachInterrupt(digitalPinToInterrupt(ROTARY_A_PIN), isr, RISING);
  pinMode(ROTARY_B_PIN, INPUT);
  pinMode(ROTARY_BTN_PIN, INPUT);
  //attachInterrupt(digitalPinToInterrupt(ROTARY_BTN_PIN), isr, RISING);
  // Motion Sensor
  pinMode(MOTION_SENSOR_PIN, INPUT_PULLDOWN);
  //attachInterrupt(digitalPinToInterrupt(MOTION_SENSOR_PIN), isr, RISING);
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
