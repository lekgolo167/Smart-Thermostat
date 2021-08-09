#include "Thermostat.hpp"


Thermostat::Thermostat(tm* clk, thermostat_settings* settings, sensor_readings* sensor) {
	m_time = clk;
	m_settings = settings;
	m_sensor = sensor;
	m_settings->baseline_temperature = 55.0;
	m_settings->lower_threshold = 1.0;
	m_settings->upper_threshold = 1.0;
	m_settings->target_temperature = 70.0;
	m_settings->sample_period_sec = 30;
	m_settings->total_samples = 5;
	m_settings->screen_timeout_sec = 15;
	m_settings->motion_timeout_sec = 172800;

	int id = -1;
	for (uint8_t day = 0; day < 7; day++){
		m_days[day] = new CycleList();
		m_days[day]->push_back(*new cycle{id--, 0, 0, 60.0});
	}
}

void Thermostat::initialize() {
	htu.begin();
	sample_air();
	m_settings->current_cycle = m_days[m_time->tm_wday]->find_next_cycle(m_time->tm_hour, m_time->tm_min);
	m_settings->current_cycle->id = 0;

	m_sample_avg_index = 0;
	for (int i = 0; i < 20; i++) {
		m_temperature_samples[i] = m_sensor->temperature_F;
	}
	m_temperatures_sum = m_sensor->temperature_F * 5.0;

}

void Thermostat::update_cycle() {
	uint8_t today = m_time->tm_wday;
	cycle* loaded_cycle = m_days[today]->find_next_cycle(m_time->tm_hour, m_time->tm_min);

	if (loaded_cycle->id != m_settings->current_cycle->id) {
		m_settings->current_cycle = loaded_cycle;
		m_settings->target_temperature = loaded_cycle->temp_F;

		// TODO stop temporary timer
		
	}
}

void Thermostat::run_cycle() {
	float room_temperature = calc_avg_room_temperature();
	update_cycle();
	bool motion_detected = motion_timeout_check();

	if (motion_detected && room_temperature <= (m_settings->target_temperature - m_settings->lower_threshold)) {
		toggle_furnace_relay(true);
	}
	else if (room_temperature >= (m_settings->target_temperature + m_settings->upper_threshold)) {
		toggle_furnace_relay(false);
	}
	else if (room_temperature <= (m_settings->baseline_temperature - m_settings->lower_threshold)) {
		toggle_furnace_relay(true);
	}
	else if (!motion_detected && room_temperature >= (m_settings->baseline_temperature + m_settings->upper_threshold)) {
		toggle_furnace_relay(false);
	}

}

void Thermostat::toggle_furnace_relay(bool power_ON) {
	if (power_ON != m_furnace_ON) {
		if (power_ON) {
			m_furnace_start_time = mktime(m_time);
			digitalWrite(FURNACE_RELAY_PIN, HIGH);
		}
		else {
			m_furnace_runtime = mktime(m_time) - m_furnace_start_time;
			digitalWrite(FURNACE_RELAY_PIN, LOW);
			// TODO send runtime to server
		}
		m_furnace_ON = power_ON;
		// send furnace state to server
	}

}

float Thermostat::calc_avg_room_temperature() {
	float old_temperature = m_temperature_samples[m_sample_avg_index];
	m_temperature_samples[m_sample_avg_index++] = m_sensor->temperature_F;
	if (m_sample_avg_index >= m_settings->total_samples) {
		m_sample_avg_index = 0;
	}
	m_temperatures_sum += m_sensor->temperature_F;
	m_temperatures_sum -= old_temperature;

	m_sensor->average_temperature = m_temperatures_sum / m_settings->total_samples;
	return m_sensor->average_temperature;
}

void Thermostat::sample_air() {
	m_sensor->temperature_C = htu.readTemperature();
	m_sensor->temperature_F = 9.0/5.0 * m_sensor->temperature_C + 32.0;
	m_sensor->humidity = htu.readHumidity();
}

bool Thermostat::motion_timeout_check() {
	return false;
}

bool Thermostat::check_server_for_updates() {
	int server_IDs[7];

	get_day_IDs(server_IDs);

	for (uint8_t day = 0; day < 7; day++) {
		if (server_IDs[day] != m_days[day]->m_dayID) {

			m_days[day]->update_cycles(day);

			if (m_time->tm_wday == day) {
				stop_tempoaray_timer();
			}
		}
	}
}

void Thermostat::stop_tempoaray_timer() {

}