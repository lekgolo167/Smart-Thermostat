#include <Arduino.h>
#include <Adafruit_SSD1306.h>
#include <RTCZero.h>

#include "Initialization.hpp"
#include "HTU21D.hpp"
#include "Oled.h"

sensor_readings* sensor  = new sensor_readings;
thermostat_settings* settings = new thermostat_settings;;
HTU21D htu;
RTCZero rtc;
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
OLED oled = OLED(&display, rtc, settings, sensor);

void setup()
{
  initGPIO(oled);
  initI2C();
  initTimers();
  initWiFi();
  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
}

// the loop function runs over and over again forever
void loop()
{
}