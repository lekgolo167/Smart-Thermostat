#pragma once

#include <Wire.h>
#include <Arduino.h>
#include <RTCZero.h>

#include "Constants.hpp"

void initI2C();

void initGPIO();

void initTimers();

void initWiFi();

void initRTC(RTCZero& rtc);