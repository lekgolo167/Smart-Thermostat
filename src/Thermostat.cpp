#include "Thermostat.hpp"

Thermostat::Thermostat(tm *clk, thermostat_settings *settings, sensor_readings *sensor)
{
	m_time = clk;
	m_settings = settings;
	m_sensor = sensor;
	m_settings->baseline_temperature = 55.0;
	m_settings->lower_threshold = 1.0;
	m_settings->upper_threshold = 1.0;
	m_settings->target_temperature = 70.0;
	m_settings->sample_period_sec = 30;
	m_settings->total_samples = 5;
	m_settings->screen_timeout_millis = 15 * 1000;
	m_settings->override_timeout_millis = 60 * 60 * 1000;
	m_settings->motion_timeout_millis = 48 * 60 * 60 * 1000;

	m_furnace_ON = false;
	m_override_ON = false;
	m_furnace_runtime = 0;
	m_motion_timestamp = millis();

	int id = -1;
	for (uint8_t day = 0; day < 7; day++)
	{
		m_days[day] = new CycleList();
		m_days[day]->push_back(cycle{id--, 0, 0, 0, 0, 60.0});
	}
}

void Thermostat::initialize()
{
	htu.begin();
	sample_air();
	m_settings->current_cycle = m_days[0]->find_next_cycle(0, 0);
	m_settings->current_cycle->id = 0;

	m_sample_avg_index = 0;
	for (int i = 0; i < 20; i++)
	{
		m_temperature_samples[i] = m_sensor->temperature_F;
	}
	m_temperatures_sum = m_sensor->temperature_F * 5.0;
}

void Thermostat::update_cycle()
{
	uint8_t today = m_time->tm_wday;
	cycle *loaded_cycle = m_days[today]->find_next_cycle(m_time->tm_hour, m_time->tm_min);

	if (loaded_cycle->id != m_settings->current_cycle->id)
	{
		m_settings->current_cycle = loaded_cycle;
		if (!m_override_ON) {
			m_settings->target_temperature = loaded_cycle->temp_F;

			global_msg_queue->push(SEND_SERVER_STATS);
		}
		// temporary solution to keep rtc time correct as it loses 24 minutes per day
		global_msg_queue->push(GET_EPOCH);
	}
}

void Thermostat::run_cycle()
{
	float room_temperature = calc_avg_room_temperature();
	bool motion_detected = motion_timeout_check();
	manage_temporary_override();
	update_cycle();

	if (motion_detected && room_temperature <= (m_settings->target_temperature - m_settings->lower_threshold))
	{
		toggle_furnace_relay(true);
	}
	else if (room_temperature >= (m_settings->target_temperature + m_settings->upper_threshold))
	{
		toggle_furnace_relay(false);
	}
	else if (room_temperature <= (m_settings->baseline_temperature - m_settings->lower_threshold))
	{
		toggle_furnace_relay(true);
	}
	else if (!motion_detected && room_temperature >= (m_settings->baseline_temperature + m_settings->upper_threshold))
	{
		toggle_furnace_relay(false);
	}
}

void Thermostat::toggle_furnace_relay(bool power_ON)
{
	if (power_ON != m_furnace_ON)
	{
		if (power_ON)
		{
			m_furnace_start_time = millis();
			digitalWrite(FURNACE_RELAY_PIN, HIGH);
		}
		else
		{
			m_furnace_runtime = (millis() - m_furnace_start_time) / 1000; // convert to seconds
			digitalWrite(FURNACE_RELAY_PIN, LOW);
			global_msg_queue->push(SEND_SEVER_RUNTIME);
		}
		m_furnace_ON = power_ON;
		global_msg_queue->push(SEND_SERVER_FURNACE_STATE);
	}
}

float Thermostat::calc_avg_room_temperature()
{
	float old_temperature = m_temperature_samples[m_sample_avg_index];
	m_temperature_samples[m_sample_avg_index++] = m_sensor->temperature_F;
	if (m_sample_avg_index >= m_settings->total_samples)
	{
		m_sample_avg_index = 0;
	}
	m_temperatures_sum += m_sensor->temperature_F;
	m_temperatures_sum -= old_temperature;

	m_sensor->average_temperature = m_temperatures_sum / m_settings->total_samples;
	return m_sensor->average_temperature;
}

void Thermostat::sample_air()
{
	m_sensor->temperature_C = htu.readTemperature();
	m_sensor->temperature_F = 9.0 / 5.0 * m_sensor->temperature_C + 32.0;
	m_sensor->humidity = htu.readHumidity();
}

bool Thermostat::motion_timeout_check()
{
	if (millis() - m_motion_timestamp > m_settings->motion_timeout_millis)
	{
		return false;
	}
	return true;
}

void Thermostat::update_schedule(Messenger& messenger)
{
	int server_IDs[7];

	messenger.get_day_ids(server_IDs);

	for (uint8_t day = 0; day < 7; day++)
	{
		if (server_IDs[day] != m_days[day]->m_dayID)
		{
			m_days[day]->m_dayID = server_IDs[day];
			m_days[day]->update_cycles(day, messenger);

			if (m_time->tm_wday == day)
			{
				// if the day changed is today update settings current cycle pointer
				uint8_t today = m_time->tm_wday;
				cycle *loaded_cycle = m_days[today]->find_next_cycle(m_time->tm_hour, m_time->tm_min);

				m_settings->current_cycle = loaded_cycle;

				if (!m_override_ON) {
					m_settings->target_temperature = loaded_cycle->temp_F;

					global_msg_queue->push(SEND_SERVER_STATS);
				}
			} // end if (day == today)
		}
	} // end for loop
}

void Thermostat::manage_temporary_override() {
		if (m_override_ON && millis() - m_temporary_start_time > m_settings->override_timeout_millis) {
			m_override_ON = false;
			m_settings->target_temperature = m_settings->current_cycle->temp_F;
			global_msg_queue->push(SEND_SERVER_STATS);
		}
}

void Thermostat::start_temporary_override()
{
	m_override_ON = true;
	m_temporary_start_time = millis();
}

bool Thermostat::get_furnace_state() {
	return m_furnace_ON;
}

uint32_t Thermostat::get_runtime()
{
	return m_furnace_runtime;
}

void Thermostat::set_moition_timestamp()
{
	m_motion_timestamp = millis();
}

uint32_t Thermostat::get_motion_timestamp()
{
	return m_motion_timestamp;
}
