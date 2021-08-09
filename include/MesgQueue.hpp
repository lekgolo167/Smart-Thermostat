#pragma once

#include <queue>

inline std::queue<int> *global_msg_queue;

enum ThermostatMessages {
	SAMPLE_AIR,
	RTC_UPDATE,
	MOTION_DETECTED,
	SEND_SERVER_MSG,
	OLED_ON,
	OLED_OFF,
	OLED_UPDATE,
	OLED_NEXT_MENU,
	OLED_PREV_MENU,
	OLED_EDIT_MENU,
	OLED_ROTARY_CCW,
	OLED_ROTARY_CW
};
