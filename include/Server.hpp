#pragma once

#include <WiFiNINA.h>
#include <WIFIUdp.h>

#include "Constants.hpp"

void post_request(const char *url, char *msg, int len);

int get_request(const char *path, char *buffer, size_t size);

float get_temporary_temperature();

void get_day_ids(int *id_array);

uint32_t get_epoch();
