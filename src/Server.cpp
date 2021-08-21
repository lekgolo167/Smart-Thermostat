#include "Server.hpp"
#include "parson.h"

void post_request(const char *path, char *msg, int len)
{
	// Prepare the client
	WiFiClient client;

	// Connect to the server
	if (client.connect(SERVER_ADDRESS, SERVER_POST_PORT))
	{
		// Connection established
		client.print("POST ");
		client.print(path);
		client.println(" HTTP/1.1");
		client.print("Host: ");
		client.print(SERVER_ADDRESS);
		client.print(":");
		client.println(SERVER_POST_PORT);
		client.println("Content-Type: application/x-www-form-urlencoded");
		client.print("Content-Length: ");
		client.println(len);
		client.println();
		client.println(msg);
		client.println();
	}

	client.stop();
		
}

int get_request(const char *path, char *buffer, size_t size)
{
	// Prepare the client
	WiFiClient client;
	int data_length = -1;

	// Connect to the server
	if (client.connect(SERVER_ADDRESS, SERVER_PORT))
	{
		// Connection established
		client.print("GET ");
		client.print(path);
		client.println(" HTTP/1.0");
		client.print("Host: ");
		client.print(SERVER_ADDRESS);
		client.print(":");
		client.println(SERVER_PORT);
		client.println();
	}
	else
	{
		// Failed dot connect
		Serial.println("FAILED TO CONNECT");
		client.stop();
		return -1;
	}

	// Listen and manage a timeout
	unsigned long startTime = millis();
	bool received = false;

	while ((millis() - startTime < 2000) && !received)
	{

		while (client.available())
		{
			received = true;
			// check for valid response
			if (!client.find("HTTP/1.0"))
			{
				return -1;
			}
			int status_code = client.parseInt();
			if (!client.find("Content-Length:"))
			{
				return -1;
			}
			int content_lenght = client.parseInt();
			// if HTTP status OK seek to the data portion of the response
			if (status_code == 200 && client.find("\n\r\n"))
			{
				Serial.println("READING DATA");
				data_length = client.readBytes(buffer, content_lenght);
				// set null terminator
				buffer[data_length] = '\0';
			}
		}
	}

	client.stop();

	return data_length;
}

float get_temporary_temperature()
{
	char buffer[256];
	float temperature = 0.0;
	if (get_request(URL_GET_TEMPORARY, buffer, 256) > 0)
	{
		JSON_Value *raw = json_parse_string(buffer);
		JSON_Object *obj = json_value_get_object(raw);
		temperature = (float)json_object_get_number(obj, "temporary");
		json_value_free(raw);
	}
	return temperature;
}

void get_day_ids(int *id_array)
{
	char buffer[256];
	if (get_request(URL_GET_DAY_IDS, buffer, 256) > 0)
	{
		JSON_Value *raw = json_parse_string(buffer);
		JSON_Object *obj = json_value_get_object(raw);
		char dates[7][4] = {"sun", "mon", "tue", "wed", "thu", "fri", "sat"};
		for (int i = 0; i < 7; i++)
		{
			id_array[i] = (int)json_object_get_number(obj, dates[i]);
		}
		json_value_free(raw);
	}
}

uint32_t get_epoch() {
	char buffer[256];
	uint32_t epoch = 0;
	if (get_request(URL_GET_EPOCH, buffer, 256) > 0)
	{
		JSON_Value *raw = json_parse_string(buffer);
		JSON_Object *obj = json_value_get_object(raw);
		epoch = (uint32_t)json_object_get_number(obj, "epoch");
		json_value_free(raw);
	}
	return epoch;
}