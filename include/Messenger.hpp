#pragma once

#include <stdint.h>
#include <WiFiNINA.h>
#include <WIFIUdp.h>

#include "parson.h"

class Messenger
{
private:
	// Local listening port
	const uint16_t LOCAL_PORT = 2390;
	const uint16_t LOCAL_HB_PORT = 2391;

	const uint16_t SERVER_GET_PORT = 5000;
	const uint16_t SERVER_POST_PORT = 1880;
	const uint16_t SERVER_HB_PORT = 1887;

	// IP address of server
	IPAddress m_remoteIP;

	// UDP sockets
	WiFiUDP m_udp_hb;
	WiFiUDP m_udp_msg;

	// Methods
	bool check_server_available(const char* service);

public:
	Messenger(/* args */);
	~Messenger();

	// Methods
	void initialize();
	void post_request(const char *path, char *msg, int len);
	int get_request(const char *path, char *buffer, size_t size);
	int check_inbox();
	float get_temporary_temperature();
	void get_day_ids(int *id_array);
	uint32_t get_epoch();
};



const inline char* SERVER_ADDRESS = "192.168.0.238";

const inline char* URL_GET_TEMPORARY = "/getTemporary";
const inline char* URL_GET_DAY_IDS = "/getDayIDs";
const inline char* URL_GET_CYCLES = "/getCycles/%d";
const inline char* URL_GET_EPOCH = "/getEpoch";

const inline char* URL_TEMPERATURE = "/temp";
const inline char* URL_STATS = "/stats";
const inline char* URL_MOTION = "/motion";
const inline char* URL_RUNTIME = "/runtime";
const inline char* URL_FURNANCE_STATE = "/furnaceState";

const inline char* POST_TEMPERATURE = "TEMP=%f&HUM=%f";
const inline char* POST_STATS = "TARGET=%f&THRESH_L=%f&THRESH_H=%f";
const inline char* POST_MOTION = "MOTION=%d";
const inline char* POST_RUNTIME = "RUNTIME=%d";
const inline char* POST_FURNACE_STATE = "F_State=%d";