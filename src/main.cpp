#include <Arduino.h>
#include "Initialization.hpp"

#include "HTU21D.h"
#include "Oled.h"
#include <Adafruit_SSD1306.h>

sensor_readings* sensor  = new sensor_readings;
thermostat_settings* settings = new thermostat_settings;;
HTU21D htu;
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
OLED oled = OLED(&display, settings, sensor);

void setup()
{
  initGPIO();
  initI2C();
  initTimers();
  initWiFi();
  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
}

// the loop function runs over and over again forever
void loop()
{
}