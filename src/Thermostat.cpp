#include "Thermostat.hpp"


Thermostat::Thermostat() {
	rtc.begin();
	rtc.setTime(0,0,0);
	rtc.setDate(1,1,2021);
	// use this from server
	//rtc.setEpoch();

	for (uint8_t day; day < 6; day++){
		m_days[day]->push_back(*new cycle{-1, 0, 0, 60.0});
	}
}

void Thermostat::update_cycle() {
	uint8_t today = rtc.getDay();
	cycle* loaded_cycle = m_days[today]->find_next_cycle(rtc.getHours(), rtc.getMinutes());

	if (loaded_cycle->id != ) {

	}
}

void Thermostat::run_cycle() {
	float room_temperature;
	bool motion_detected = motion_timeout_check();

	update_cycle();

	if (motion_detected && room_temperature <= (m_settings.target_temperature - m_settings.lower_threshold)) {
		toggle_furnace_relay(true);
	}
	else if (room_temperature >= (m_settings.target_temperature + m_settings.upper_threshold)) {
		toggle_furnace_relay(false);
	}
	else if (room_temperature <= (m_settings.baseline_temperature - m_settings.lower_threshold)) {
		toggle_furnace_relay(true);
	}
	else if (!motion_detected && room_temperature >= (m_settings.baseline_temperature + m_settings.upper_threshold)) {
		toggle_furnace_relay(false);
	}

}

void Thermostat::toggle_furnace_relay(bool power_ON) {
	if (power_ON != m_furnace_ON) {
		if (power_ON) {
			m_furnace_start_time = rtc.getEpoch();
			digitalWrite(FURNACE_RELAY_PIN, HIGH);
		}
		else {
			m_furnace_runtime = rtc.getEpoch() - m_furnace_start_time;
			digitalWrite(FURNACE_RELAY_PIN, LOW);
		}
		m_furnace_ON = power_ON;
		// TODO send runtime to server and state
	}

};

bool Thermostat::check_server_for_updates() {
	int server_IDs[7];

	get_day_IDs(server_IDs);

	for (uint8_t day = 0; day < 7; day++) {
		if (server_IDs[day] != m_days[day]->m_dayID) {

			m_days[day]->update_cycles(day);

			if (rtc.getDay() == day) {
				stop_tempoaray_timer();
			}
		}
	}
}

void Thermostat::stop_tempoaray_timer() {

}