#include <Arduino.h>
#include "Initialization.hpp"

void setup()
{
  initGPIO();
  initI2C();
  initTimers();
  initWiFi();
}

// the loop function runs over and over again forever
void loop()
{
}