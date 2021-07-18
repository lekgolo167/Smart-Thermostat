#pragma once

#include <Wire.h>
#include <Arduino.h>
#include <RTCZero.h>

#include "Constants.hpp"
#include "Oled.h"

void initI2C();

void initGPIO(OLED& oled);

void initTimers();

void initWiFi();