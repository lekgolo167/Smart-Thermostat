#pragma once

#include <stdint.h>

typedef struct {
	const uint8_t* icon;
	int8_t high;
	int8_t low;
} weather_data_t;

class Weather
{
	public:
		Weather();
		~Weather();
		void get_weather();
		void set_current_weather(int hr);
		weather_data_t* get_current_weather();
		weather_data_t* get_forecast(int day);
	private:
		const uint8_t* get_icon(int icon);
		weather_data_t* current_weather;
		weather_data_t* hourly_data[25];
		weather_data_t* forecast_data[3];
};
