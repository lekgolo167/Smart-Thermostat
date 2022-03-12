#pragma once

#include <RTCZero.h>
#include <time.h>

#include "CycleList.hpp"
#include "Messenger.hpp"
#include "Constants.hpp"
#include "HTU21D.hpp"
#include "MesgQueue.hpp"

struct sensor_readings
{
	float temperature_F;
	float temperature_C;
	float average_temperature;
	float humidity;
};

struct thermostat_settings
{
	float target_temperature;
	float lower_threshold;
	float upper_threshold;
	float baseline_temperature;
	uint16_t sample_period_sec;
	uint32_t screen_timeout_millis;
	uint32_t override_timeout_millis;
	uint32_t motion_timeout_millis;
	uint8_t total_samples;
	cycle_t *current_cycle;
};

class Thermostat
{
public:
	Thermostat(tm *clk, thermostat_settings *settings, sensor_readings *sensor);
	void run_cycle();
	void initialize();
	void sample_air();
	void update_schedule(Messenger& messenger);
	uint32_t get_runtime();
	bool get_furnace_state();
	void start_temporary_override();
	void set_moition_timestamp();
	uint32_t get_motion_timestamp();

private:
	void update_cycle();
	bool motion_timeout_check();
	void manage_temporary_override();
	void toggle_furnace_relay(bool power_ON);
	float calc_avg_room_temperature();

	tm *m_time;
	HTU21D htu;
	thermostat_settings *m_settings;
	sensor_readings *m_sensor;
	float m_temperature_samples[20];
	float m_temperatures_sum;
	int m_sample_avg_index;
	bool m_initialized_from_server;
	bool m_furnace_ON;
	bool m_override_ON;
	uint32_t m_motion_timestamp;
	uint32_t m_furnace_start_time;
	uint32_t m_furnace_runtime;
	uint32_t m_temporary_start_time;
	CycleList *m_days[7];
};
