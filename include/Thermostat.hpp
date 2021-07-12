#pragma once

#include<RTCZero.h>

#include "CycleList.hpp"
#include "Server.hpp"
#include "Constants.hpp"

RTCZero rtc;

struct sensor_readings {
	float temperature_F;
	float temperature_C;
	float average_temperature;
	float humidity;
};

struct thermostat_settings {
	float target_temperature;
	float lower_threshold;
	float upper_threshold;
	float baseline_temperature;
	uint16_t sample_period_sec;
	uint16_t screen_timeout_sec;
	uint16_t motion_timeout_sec;
	uint8_t total_samples;
	cycle_t* current_cycle;
};

class Thermostat {
public:
	Thermostat();
	void run_cycle();

private:

	void update_cycle();
	bool check_server_for_updates();
	bool motion_timeout_check();
	void stop_tempoaray_timer();
	void toggle_furnace_relay(bool power_ON);

	thermostat_settings m_settings;
	bool m_furnace_ON;
	uint32_t m_furnace_start_time;
	uint32_t m_furnace_runtime;
	CycleList* m_days[7];
};
