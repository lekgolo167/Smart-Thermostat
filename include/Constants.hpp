#pragma once

#include <stdint.h>

// Buttons
const uint8_t BUTTON_A_PIN = 9;
const uint8_t BUTTON_B_PIN = 10;

// Rotary Encoder
const uint8_t ROTARY_A_PIN = 2;
const uint8_t ROTARY_B_PIN = 4;
const uint8_t ROTARY_BTN_PIN = 3;

// Relay
const uint8_t FURNACE_RELAY_PIN = 13;

// Motion Sensor
const uint8_t MOTION_SENSOR_PIN = 11;

// I2C
const uint32_t I2C_FREQ = 400000;

// Local listening port
const uint16_t LOCAL_PORT = 2390;

// IP address of server
const u_int16_t SERVER_PORT = 5000;
const inline char* SERVER_ADDRESS = "192.168.0.238";
const inline char* URL_GET_TEMPORARY = "/getTemporary";
const inline char* URL_GET_DAY_IDS = "/getDayIDs";
const inline char* URL_TEMPERATURE = "/temp";
const inline char* URL_STATS = "/stats";
const inline char* URL_MOTION = "/motion";
const inline char* URL_RUNTIME = "/runtime";
const inline char* URL_FURNANCE_STATE = "/furnaceState";