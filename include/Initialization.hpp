#pragma once

#include <Wire.h>
#include <Arduino.h>
#include <RTCZero.h>
#include <WiFiNINA.h>

#include "Constants.hpp"
#include "WiFiSecrets.h"
#include "Timers.hpp"
#include "MesgQueue.hpp"

void initI2C();

void initGPIO();

void initTimers();

void initWiFi();

void initRTC(RTCZero& rtc);