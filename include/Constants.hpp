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

// IP address of server
#define IP_ADDRESS_AND_PORT "192.168.0.27:1880"

#define URL_TEMPERATURE IP_ADDRESS_AND_PORT "/temp"
#define URL_STATS IP_ADDRESS_AND_PORT "/stats"
#define URL_MOTION IP_ADDRESS_AND_PORT "/motion"
#define URL_RUNTIME IP_ADDRESS_AND_PORT "/runtime"
#define URL_FURNANCE_STATE IP_ADDRESS_AND_PORT "/furnaceState"