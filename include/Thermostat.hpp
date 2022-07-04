#pragma once

#include <RTCZero.h>
#include <time.h>

#include "CycleList.hpp"
#include "Messenger.hpp"
#include "Constants.hpp"
#include "HDC1080.hpp"
#include "MesgQueue.hpp"
#include "Logging.hpp"

struct sensor_readings
{
	float temperature_F;
	float temperature_C;
	float average_temperature;
	float k_estimate;
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
	enum Temperature_Filters{
		KALMAN,
		AVERAGE,
		NONE
	};

	Thermostat(tm *clk, Logging* logger, thermostat_settings *settings, sensor_readings *sensor);
	void run_cycle();
	void initialize();
	void sample_air();
	void update_schedule(Messenger& messenger);
	uint32_t get_runtime();
	bool get_furnace_state();
	void start_temporary_override();
	void set_moition_timestamp();
	uint32_t get_motion_timestamp();
	void set_filter_method(int8_t filter);
	bool self_test_running();
	bool self_test_passed();
	void self_test();

private:
	void update_cycle();
	bool motion_timeout_check();
	void manage_temporary_override();
	void toggle_furnace_relay(bool power_ON);
	float calc_avg_room_temperature();
	float kalman_filter();
	float no_filter();
	float (Thermostat::*filter_method)(void);

	tm *m_time;
	HYGROI2C htu;
	Logging* m_logger;
	thermostat_settings *m_settings;
	sensor_readings *m_sensor;
	float m_temperature_samples[20];
	float m_temperatures_sum;
	int m_sample_avg_index;
	bool m_initialized_from_server;
	bool m_furnace_ON;
	bool m_override_ON;
	bool m_test_running;
	float m_std_deviation;
	float z_score;
	float estimated_t;
	float k;
	float p;
	float omega;
	float q;
	uint32_t m_test_start_time;
	uint32_t m_motion_timestamp;
	uint32_t m_furnace_start_time;
	uint32_t m_furnace_runtime;
	uint32_t m_temporary_start_time;
	CycleList *m_days[7];
};
