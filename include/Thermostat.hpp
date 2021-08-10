#pragma once

#include<RTCZero.h>
#include <time.h>

#include "CycleList.hpp"
#include "Server.hpp"
#include "Constants.hpp"
#include "HTU21D.hpp"
#include "MesgQueue.hpp"

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
	uint32_t motion_timeout_sec;
	uint8_t total_samples;
	cycle_t* current_cycle;
};

class Thermostat {
public:
	Thermostat(tm* clk, thermostat_settings* settings, sensor_readings* sensor);
	void run_cycle();
	void initialize();
	void sample_air();
	uint32_t get_runtime();
private:

	void update_cycle();
	bool check_server_for_updates();
	bool motion_timeout_check();
	void stop_tempoaray_timer();
	void toggle_furnace_relay(bool power_ON);
	float calc_avg_room_temperature();

	tm* m_time;
	HTU21D htu;
	thermostat_settings* m_settings;
	sensor_readings* m_sensor;
	float m_temperature_samples[20];
	float m_temperatures_sum;
	int m_sample_avg_index;
	bool m_furnace_ON;
	uint32_t m_furnace_start_time;
	uint32_t m_furnace_runtime;
	CycleList* m_days[7];
};
