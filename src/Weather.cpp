#include "Weather.hpp"
#include "parson.h"


static const uint8_t icon_clear_day[288]{
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x01, 0x80, 0x00, 0x00,
	0x00, 0x00, 0x01, 0x80, 0x00, 0x00,
	0x00, 0x00, 0x01, 0x80, 0x00, 0x00,
	0x00, 0x00, 0x01, 0x80, 0x00, 0x00,
	0x00, 0x00, 0x01, 0x80, 0x00, 0x00,
	0x00, 0x20, 0x01, 0x80, 0x04, 0x00,
	0x00, 0x70, 0x01, 0x80, 0x0e, 0x00,
	0x00, 0x38, 0x00, 0x00, 0x1c, 0x00,
	0x00, 0x1c, 0x00, 0x00, 0x38, 0x00,
	0x00, 0x0e, 0x00, 0x00, 0x70, 0x00,
	0x00, 0x06, 0x03, 0xc0, 0x60, 0x00,
	0x00, 0x00, 0x1f, 0xf8, 0x00, 0x00,
	0x00, 0x00, 0x3e, 0x7c, 0x00, 0x00,
	0x00, 0x00, 0x70, 0x0e, 0x00, 0x00,
	0x00, 0x00, 0xe0, 0x07, 0x00, 0x00,
	0x00, 0x01, 0xc0, 0x03, 0x80, 0x00,
	0x00, 0x01, 0x80, 0x01, 0x80, 0x00,
	0x00, 0x01, 0x80, 0x01, 0x80, 0x00,
	0x00, 0x03, 0x80, 0x01, 0xc0, 0x00,
	0x0f, 0xe3, 0x00, 0x00, 0xc7, 0xf0,
	0x0f, 0xe3, 0x00, 0x00, 0xc7, 0xf0,
	0x00, 0x03, 0x80, 0x01, 0xc0, 0x00,
	0x00, 0x01, 0x80, 0x01, 0x80, 0x00,
	0x00, 0x01, 0x80, 0x01, 0x80, 0x00,
	0x00, 0x01, 0xc0, 0x03, 0x80, 0x00,
	0x00, 0x00, 0xe0, 0x07, 0x00, 0x00,
	0x00, 0x00, 0x70, 0x0e, 0x00, 0x00,
	0x00, 0x00, 0x3e, 0x7c, 0x00, 0x00,
	0x00, 0x00, 0x1f, 0xf8, 0x00, 0x00,
	0x00, 0x06, 0x03, 0xc0, 0x60, 0x00,
	0x00, 0x0e, 0x00, 0x00, 0x70, 0x00,
	0x00, 0x1c, 0x00, 0x00, 0x38, 0x00,
	0x00, 0x38, 0x00, 0x00, 0x1c, 0x00,
	0x00, 0x70, 0x01, 0x80, 0x0e, 0x00,
	0x00, 0x20, 0x01, 0x80, 0x04, 0x00,
	0x00, 0x00, 0x01, 0x80, 0x00, 0x00,
	0x00, 0x00, 0x01, 0x80, 0x00, 0x00,
	0x00, 0x00, 0x01, 0x80, 0x00, 0x00,
	0x00, 0x00, 0x01, 0x80, 0x00, 0x00,
	0x00, 0x00, 0x01, 0x80, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

static const uint8_t icon_clear_night[288]{
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x01, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x03, 0x80, 0x00, 0x00, 0x00,
	0x00, 0x07, 0xc0, 0x00, 0x00, 0x00,
	0x00, 0x03, 0x80, 0x00, 0x00, 0x00,
	0x00, 0x01, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x03, 0xe0, 0x00, 0x00,
	0x00, 0x00, 0x07, 0xe0, 0x00, 0x00,
	0x00, 0x00, 0x1e, 0x60, 0x00, 0x00,
	0x00, 0x00, 0x18, 0x60, 0x00, 0x00,
	0x01, 0x80, 0x70, 0x60, 0x00, 0x00,
	0x03, 0x80, 0x60, 0x60, 0x00, 0x00,
	0x03, 0xc0, 0xe0, 0x30, 0x00, 0x00,
	0x01, 0x01, 0xc0, 0x30, 0x00, 0x00,
	0x00, 0x01, 0x80, 0x38, 0x00, 0x00,
	0x00, 0x01, 0x80, 0x1c, 0x00, 0x00,
	0x00, 0x03, 0x80, 0x0e, 0x00, 0x00,
	0x00, 0x01, 0x00, 0x07, 0x00, 0x00,
	0x00, 0x03, 0x80, 0x03, 0x80, 0x00,
	0x00, 0x01, 0x00, 0x01, 0xf0, 0x00,
	0x00, 0x03, 0x80, 0x00, 0xff, 0x80,
	0x00, 0x01, 0x00, 0x00, 0x17, 0x80,
	0x00, 0x01, 0x80, 0x00, 0x03, 0x80,
	0x00, 0x01, 0xc0, 0x00, 0x01, 0x00,
	0x00, 0x00, 0xc0, 0x00, 0x03, 0x80,
	0x00, 0x00, 0xc0, 0x00, 0x07, 0x00,
	0x00, 0x00, 0xe0, 0x00, 0x0e, 0x00,
	0x00, 0x00, 0x70, 0x00, 0x1c, 0x00,
	0x00, 0x00, 0x3c, 0x00, 0x38, 0x00,
	0x00, 0x00, 0x1f, 0x00, 0x70, 0x00,
	0x00, 0x00, 0x07, 0xff, 0xe0, 0x00,
	0x00, 0x00, 0x01, 0xff, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x28, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

static const uint8_t icon_cloudy[288]{
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x50, 0x00, 0x00, 0x00,
	0x00, 0x03, 0xfe, 0x00, 0x00, 0x00,
	0x00, 0x03, 0x47, 0x00, 0x00, 0x00,
	0x00, 0x0e, 0x03, 0xaa, 0x38, 0x00,
	0x00, 0x0c, 0x00, 0xff, 0x1c, 0x00,
	0x0f, 0x9c, 0x00, 0xeb, 0x8e, 0xe0,
	0x1f, 0xd0, 0x00, 0x01, 0xc7, 0xf0,
	0x3a, 0xb8, 0x00, 0x00, 0xe2, 0x3c,
	0x60, 0x10, 0x00, 0x00, 0x60, 0x0c,
	0xe0, 0x38, 0x00, 0x00, 0x60, 0x0e,
	0x40, 0x10, 0x00, 0x00, 0x30, 0x06,
	0xc0, 0x38, 0x00, 0x00, 0x20, 0x02,
	0xc0, 0x10, 0x00, 0x00, 0x70, 0x07,
	0xc0, 0x18, 0x00, 0x00, 0x60, 0x06,
	0x40, 0x1c, 0x00, 0x00, 0x60, 0x06,
	0x60, 0x0e, 0x00, 0x00, 0xe0, 0x0e,
	0x70, 0x07, 0x00, 0x01, 0xc0, 0x1c,
	0x3a, 0xa3, 0xea, 0xaf, 0xaa, 0xb8,
	0x1f, 0xe1, 0x7f, 0xff, 0x1f, 0xf0,
	0x02, 0xa0, 0x2a, 0xaa, 0x2a, 0xa0,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

static const uint8_t icon_fog[288]{
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
	0x00, 0x20, 0x03, 0x00, 0x08, 0x00,
	0x00, 0x40, 0x03, 0x00, 0x1c, 0x00,
	0x00, 0xf8, 0x02, 0x00, 0x38, 0x00,
	0x00, 0x10, 0x00, 0x00, 0x70, 0x00,
	0x00, 0x3e, 0x00, 0x00, 0xe0, 0x00,
	0x00, 0x0c, 0x05, 0x40, 0xc0, 0x00,
	0x00, 0x08, 0x3f, 0xe8, 0x80, 0x00,
	0x00, 0x00, 0x75, 0x70, 0x00, 0x00,
	0x00, 0x00, 0xe0, 0x3e, 0x00, 0x00,
	0x00, 0x01, 0xc0, 0x04, 0x00, 0x00,
	0x00, 0x01, 0x80, 0x0e, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x03, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x03, 0x80, 0x00,
	0x07, 0xff, 0xf8, 0x01, 0x00, 0x00,
	0x0f, 0xff, 0xf8, 0x03, 0x8f, 0xe0,
	0x00, 0x00, 0x00, 0x01, 0x0f, 0xe0,
	0x00, 0x00, 0x00, 0x03, 0x80, 0x00,
	0x00, 0x00, 0x00, 0x01, 0x00, 0x00,
	0x00, 0x2a, 0xaa, 0x83, 0x80, 0x00,
	0x00, 0x3f, 0xff, 0xc7, 0x00, 0x00,
	0x00, 0x3f, 0xff, 0x8e, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x1c, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x38, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x10, 0x00, 0x00,
	0x02, 0xaa, 0xa8, 0x00, 0xe0, 0x00,
	0x07, 0xff, 0xf8, 0x00, 0xc0, 0x00,
	0x02, 0xae, 0xa8, 0x00, 0xf8, 0x00,
	0x00, 0x00, 0x01, 0x00, 0x10, 0x00,
	0x00, 0x00, 0x03, 0x00, 0x38, 0x00,
	0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

static const uint8_t icon_partly_cloudy_day[288]{
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x80, 0x00, 0x00, 0x00,
	0x00, 0x01, 0x80, 0x00, 0x00, 0x00,
	0x00, 0x01, 0x80, 0x00, 0x00, 0x00,
	0x00, 0x01, 0xc0, 0x00, 0x00, 0x00,
	0x00, 0x01, 0x80, 0x00, 0x00, 0x00,
	0x04, 0x01, 0x80, 0x10, 0x00, 0x00,
	0x0e, 0x01, 0x80, 0x30, 0x00, 0x00,
	0x07, 0x00, 0x00, 0x60, 0x00, 0x00,
	0x03, 0x80, 0x00, 0xe0, 0x00, 0x00,
	0x01, 0xc1, 0x41, 0x80, 0x00, 0x00,
	0x00, 0x8f, 0xf9, 0x80, 0x00, 0x00,
	0x00, 0x1d, 0x7c, 0x00, 0x00, 0x00,
	0x00, 0x38, 0x08, 0xba, 0x00, 0x00,
	0x00, 0x30, 0x01, 0x7f, 0x00, 0x00,
	0x00, 0x60, 0x03, 0xab, 0xe0, 0x00,
	0x00, 0x40, 0x07, 0x00, 0xc0, 0x00,
	0xfe, 0xe0, 0x0e, 0x00, 0xf0, 0x00,
	0x7c, 0x40, 0x1c, 0x00, 0x30, 0x00,
	0x20, 0xe0, 0x38, 0x00, 0x38, 0x00,
	0x00, 0x60, 0x10, 0x00, 0x1f, 0xc0,
	0x00, 0x70, 0x38, 0x00, 0x1f, 0xf8,
	0x00, 0x30, 0x10, 0x00, 0x10, 0x18,
	0x00, 0x3c, 0x38, 0x00, 0x00, 0x0e,
	0x00, 0x0c, 0x70, 0x00, 0x00, 0x04,
	0x00, 0xc3, 0xf8, 0x00, 0x00, 0x06,
	0x01, 0x83, 0x00, 0x00, 0x00, 0x03,
	0x03, 0x87, 0x00, 0x00, 0x00, 0x03,
	0x07, 0x06, 0x00, 0x00, 0x00, 0x03,
	0x0e, 0x0e, 0x00, 0x00, 0x00, 0x03,
	0x00, 0x04, 0x00, 0x00, 0x00, 0x03,
	0x00, 0x0e, 0x00, 0x00, 0x00, 0x03,
	0x00, 0x04, 0x00, 0x00, 0x00, 0x06,
	0x00, 0x0e, 0x00, 0x00, 0x00, 0x0e,
	0x00, 0x03, 0x00, 0x00, 0x00, 0x1c,
	0x00, 0x03, 0xfa, 0xba, 0xba, 0xf8,
	0x00, 0x00, 0xff, 0xff, 0xff, 0xc0,
	0x00, 0x00, 0x2a, 0xaa, 0xaa, 0x80,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

static const uint8_t icon_partly_cloudy_night[288]{
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x05, 0xf8, 0x00,
	0x00, 0x00, 0x00, 0x3f, 0xf8, 0x00,
	0x00, 0x00, 0x00, 0x70, 0x10, 0x00,
	0x00, 0x00, 0x01, 0xe0, 0x20, 0x00,
	0x00, 0x00, 0x03, 0x00, 0x60, 0x00,
	0x00, 0x00, 0x06, 0x00, 0xe0, 0x00,
	0x00, 0x00, 0x04, 0x00, 0x40, 0x00,
	0x00, 0x00, 0x18, 0x00, 0x80, 0x00,
	0x00, 0x00, 0x10, 0x00, 0xc0, 0x00,
	0x00, 0xfe, 0x00, 0x00, 0x80, 0x00,
	0x07, 0x17, 0x00, 0x01, 0x80, 0x00,
	0x0e, 0x03, 0x80, 0x01, 0x80, 0x00,
	0x18, 0x00, 0x40, 0x01, 0x80, 0x00,
	0x38, 0x00, 0x7f, 0xe1, 0x80, 0x00,
	0x30, 0x00, 0x30, 0x71, 0x80, 0x00,
	0x60, 0x00, 0x20, 0x38, 0x80, 0x00,
	0x40, 0x00, 0x00, 0x1c, 0xc0, 0x00,
	0xc0, 0x00, 0x00, 0x0c, 0xc0, 0x00,
	0x40, 0x00, 0x00, 0x04, 0x40, 0x00,
	0x80, 0x00, 0x00, 0x06, 0x60, 0x00,
	0xc0, 0x00, 0x00, 0x06, 0x60, 0x00,
	0xc0, 0x00, 0x00, 0x02, 0x30, 0x00,
	0x40, 0x00, 0x00, 0x02, 0x10, 0x00,
	0xc0, 0x00, 0x00, 0x02, 0x18, 0x00,
	0x40, 0x00, 0x00, 0x04, 0x0c, 0x00,
	0x60, 0x00, 0x00, 0x0e, 0x07, 0x00,
	0x30, 0x00, 0x00, 0x04, 0x01, 0x80,
	0x38, 0x00, 0x00, 0x08, 0x00, 0xe0,
	0x1c, 0x00, 0x00, 0x18, 0x00, 0x7c,
	0x0e, 0x00, 0x00, 0x30, 0x00, 0x0f,
	0x07, 0x51, 0x51, 0x60, 0x00, 0x06,
	0x00, 0xff, 0xff, 0x80, 0x00, 0x1c,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x70,
	0x00, 0x00, 0x00, 0x38, 0x02, 0xe0,
	0x00, 0x00, 0x00, 0x1f, 0x5f, 0x00,
	0x00, 0x00, 0x00, 0x03, 0xfa, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

static const uint8_t icon_partly_cloudy_rain[288]{
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x01, 0x80, 0x00, 0x00, 0x00,
	0x00, 0x01, 0x80, 0x00, 0x00, 0x00,
	0x00, 0x01, 0x80, 0x00, 0x00, 0x00,
	0x00, 0x01, 0x80, 0x00, 0x00, 0x00,
	0x04, 0x01, 0xc0, 0x10, 0x00, 0x00,
	0x0e, 0x01, 0x80, 0x38, 0x00, 0x00,
	0x07, 0x00, 0x00, 0x70, 0x00, 0x00,
	0x03, 0x80, 0x00, 0xe0, 0x00, 0x00,
	0x01, 0xc1, 0x41, 0xc0, 0x00, 0x00,
	0x00, 0x8f, 0xf9, 0x80, 0x00, 0x00,
	0x00, 0x1f, 0x78, 0x00, 0x00, 0x00,
	0x00, 0x38, 0x08, 0x3a, 0x00, 0x00,
	0x00, 0x70, 0x01, 0xff, 0x00, 0x00,
	0x00, 0x60, 0x03, 0xef, 0xc0, 0x00,
	0x00, 0x60, 0x07, 0x00, 0xe0, 0x00,
	0xfe, 0xe0, 0x0e, 0x00, 0x70, 0x00,
	0xfc, 0x40, 0x1c, 0x00, 0x30, 0x00,
	0x08, 0xe0, 0x18, 0x00, 0x38, 0x00,
	0x00, 0x60, 0x10, 0x00, 0x1f, 0x40,
	0x00, 0x70, 0x38, 0x00, 0x1f, 0xf0,
	0x00, 0x30, 0x10, 0x00, 0x1c, 0x78,
	0x00, 0x3c, 0x38, 0x00, 0x00, 0x1c,
	0x00, 0x0c, 0x70, 0x00, 0x00, 0x06,
	0x00, 0xc1, 0xf8, 0x00, 0x00, 0x06,
	0x01, 0xc3, 0x80, 0x00, 0x00, 0x07,
	0x03, 0x87, 0x00, 0x00, 0x00, 0x03,
	0x07, 0x06, 0x00, 0x00, 0x00, 0x03,
	0x0e, 0x0e, 0x00, 0x00, 0x00, 0x03,
	0x00, 0x04, 0x00, 0x00, 0x00, 0x03,
	0x00, 0x0e, 0x00, 0x00, 0x00, 0x06,
	0x00, 0x06, 0x00, 0x00, 0x00, 0x06,
	0x00, 0x06, 0x00, 0x00, 0x00, 0x0e,
	0x00, 0x07, 0x00, 0x00, 0x00, 0x1c,
	0x00, 0x03, 0xee, 0xee, 0xee, 0xf8,
	0x00, 0x01, 0xff, 0xff, 0xff, 0xf0,
	0x00, 0x00, 0x2a, 0xaa, 0xaa, 0x80,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x0c, 0x00, 0x03, 0x80,
	0x00, 0x00, 0x1c, 0x00, 0x03, 0x00,
	0x00, 0x00, 0x38, 0x00, 0x07, 0x00,
	0x00, 0x00, 0x10, 0x00, 0x04, 0x00,
	0x00, 0x00, 0x00, 0x06, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x0c, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x1c, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x18, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

static const uint8_t icon_rain[288]{
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x3f, 0x80, 0x00, 0x00,
	0x00, 0x00, 0xfd, 0xe0, 0x00, 0x00,
	0x00, 0x03, 0xe0, 0xf8, 0x00, 0x00,
	0x00, 0x03, 0x00, 0x18, 0x00, 0x00,
	0x00, 0x06, 0x00, 0x0e, 0x00, 0x00,
	0x00, 0x04, 0x00, 0x04, 0x00, 0x00,
	0x00, 0x0e, 0x00, 0x0e, 0xa8, 0x00,
	0x00, 0x0c, 0x00, 0x07, 0xfc, 0x00,
	0x00, 0x08, 0x00, 0x03, 0xaf, 0x80,
	0x00, 0x1c, 0x00, 0x00, 0x01, 0xc0,
	0x00, 0xb8, 0x00, 0x00, 0x00, 0xe0,
	0x01, 0x7c, 0x00, 0x00, 0x00, 0x60,
	0x03, 0xa8, 0x00, 0x00, 0x00, 0x20,
	0x07, 0x00, 0x00, 0x00, 0x00, 0x30,
	0x0e, 0x00, 0x00, 0x00, 0x00, 0x38,
	0x04, 0x00, 0x00, 0x00, 0x00, 0x30,
	0x0c, 0x00, 0x00, 0x00, 0x00, 0x30,
	0x0c, 0x00, 0x00, 0x00, 0x00, 0x30,
	0x0c, 0x00, 0x00, 0x00, 0x00, 0x30,
	0x0c, 0x00, 0x00, 0x00, 0x00, 0x70,
	0x0e, 0x00, 0x00, 0x00, 0x00, 0x60,
	0x06, 0x00, 0x00, 0x00, 0x00, 0xc0,
	0x07, 0x80, 0x00, 0x00, 0x03, 0xc0,
	0x03, 0xc0, 0x00, 0x00, 0x17, 0x00,
	0x01, 0xff, 0xff, 0xff, 0xfe, 0x00,
	0x00, 0x55, 0x55, 0x55, 0x54, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x03, 0x80, 0x80, 0x00,
	0x00, 0x0c, 0x07, 0x01, 0xc0, 0x00,
	0x00, 0x1c, 0x06, 0x03, 0x80, 0x00,
	0x00, 0x10, 0x00, 0x03, 0x00, 0x00,
	0x00, 0x20, 0x20, 0x02, 0x00, 0x00,
	0x00, 0x00, 0x70, 0x10, 0x00, 0x00,
	0x01, 0xc0, 0xe0, 0x38, 0x00, 0x00,
	0x03, 0x00, 0x40, 0x70, 0x00, 0x00,
	0x03, 0x00, 0x00, 0x60, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

static const uint8_t icon_sleet[288]{
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x5f, 0xc0, 0x00, 0x00,
	0x00, 0x00, 0xff, 0xe0, 0x00, 0x00,
	0x00, 0x01, 0xc0, 0x70, 0x00, 0x00,
	0x00, 0x03, 0x80, 0x38, 0x00, 0x00,
	0x00, 0x07, 0x00, 0x0c, 0x00, 0x00,
	0x00, 0x0e, 0x00, 0x0e, 0x00, 0x00,
	0x00, 0x04, 0x00, 0x06, 0x50, 0x00,
	0x00, 0x0c, 0x00, 0x03, 0xfe, 0x00,
	0x00, 0x1c, 0x00, 0x07, 0x57, 0x00,
	0x00, 0x08, 0x00, 0x02, 0x03, 0xc0,
	0x00, 0x1c, 0x00, 0x00, 0x00, 0x40,
	0x01, 0xf8, 0x00, 0x00, 0x00, 0xe0,
	0x01, 0xc4, 0x00, 0x00, 0x00, 0x70,
	0x07, 0x80, 0x00, 0x00, 0x00, 0x30,
	0x06, 0x00, 0x00, 0x00, 0x00, 0x30,
	0x0e, 0x00, 0x00, 0x00, 0x00, 0x30,
	0x0c, 0x00, 0x00, 0x00, 0x00, 0x10,
	0x0c, 0x00, 0x00, 0x00, 0x00, 0x38,
	0x0c, 0x00, 0x00, 0x00, 0x00, 0x30,
	0x0c, 0x00, 0x00, 0x00, 0x00, 0x20,
	0x0c, 0x00, 0x00, 0x00, 0x00, 0x60,
	0x0e, 0x00, 0x00, 0x00, 0x00, 0xe0,
	0x07, 0x00, 0x00, 0x00, 0x01, 0xc0,
	0x03, 0xaa, 0xaa, 0xaa, 0xaf, 0x80,
	0x01, 0xff, 0xff, 0xff, 0xfc, 0x00,
	0x00, 0xbf, 0xff, 0xff, 0xf8, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x40, 0x00, 0x00, 0x00, 0x00,
	0x00, 0xe0, 0x08, 0x00, 0x08, 0x00,
	0x01, 0xc0, 0x04, 0x00, 0x04, 0x00,
	0x03, 0x80, 0x0e, 0x00, 0x3c, 0x00,
	0x07, 0x00, 0x4c, 0xc0, 0x10, 0x00,
	0x0e, 0x00, 0xff, 0xc0, 0xf8, 0x00,
	0x00, 0x00, 0x3f, 0x00, 0x40, 0x00,
	0x00, 0x00, 0x3f, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x7f, 0xc0, 0x00, 0x00,
	0x00, 0x00, 0xef, 0xc0, 0x00, 0x00,
	0x00, 0x00, 0x44, 0x40, 0x00, 0x00,
	0x00, 0x00, 0x0e, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

static const uint8_t icon_snow[288]{
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x3f, 0x80, 0x00, 0x00,
	0x00, 0x00, 0xfd, 0xe0, 0x00, 0x00,
	0x00, 0x03, 0xe0, 0xf8, 0x00, 0x00,
	0x00, 0x03, 0x00, 0x18, 0x00, 0x00,
	0x00, 0x07, 0x00, 0x0c, 0x00, 0x00,
	0x00, 0x04, 0x00, 0x04, 0x00, 0x00,
	0x00, 0x0e, 0x00, 0x06, 0xa8, 0x00,
	0x00, 0x0c, 0x00, 0x07, 0xfc, 0x00,
	0x00, 0x08, 0x00, 0x03, 0xaf, 0x80,
	0x00, 0x1c, 0x00, 0x00, 0x01, 0xc0,
	0x00, 0x38, 0x00, 0x00, 0x00, 0xe0,
	0x01, 0xfc, 0x00, 0x00, 0x00, 0x60,
	0x03, 0xe8, 0x03, 0x00, 0x00, 0x60,
	0x07, 0x00, 0x03, 0x00, 0x00, 0x30,
	0x0e, 0x00, 0x0f, 0x80, 0x00, 0x30,
	0x04, 0x00, 0x07, 0x80, 0x00, 0x30,
	0x0c, 0x00, 0xb3, 0x3e, 0x00, 0x30,
	0x0c, 0x01, 0xf3, 0x1c, 0x00, 0x30,
	0x0c, 0x00, 0xfb, 0x7c, 0x00, 0x30,
	0x0c, 0x00, 0x5f, 0xfc, 0x00, 0x70,
	0x0e, 0x00, 0x0f, 0x80, 0x00, 0x60,
	0x06, 0x00, 0x4f, 0xc0, 0x00, 0xc0,
	0x07, 0x00, 0xff, 0xfc, 0x03, 0xc0,
	0x03, 0xc0, 0x73, 0x7c, 0x07, 0x00,
	0x01, 0xf9, 0xf3, 0x3e, 0x3e, 0x00,
	0x00, 0x50, 0xf3, 0x14, 0x10, 0x00,
	0x00, 0x00, 0x0f, 0x80, 0x00, 0x00,
	0x00, 0x00, 0x07, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x03, 0x00, 0x03, 0x00,
	0x01, 0x80, 0x01, 0x00, 0x03, 0xc0,
	0x01, 0xe0, 0x00, 0x00, 0x0f, 0xc0,
	0x01, 0xe0, 0x00, 0x00, 0x07, 0x00,
	0x03, 0xc0, 0x00, 0x80, 0x01, 0x80,
	0x00, 0x40, 0x01, 0x80, 0x00, 0x00,
	0x00, 0x00, 0x00, 0xf0, 0x00, 0x00,
	0x00, 0x00, 0x01, 0xc0, 0x00, 0x00,
	0x00, 0x02, 0x03, 0xe0, 0x60, 0x00,
	0x00, 0x07, 0x40, 0x40, 0x60, 0x00,
	0x00, 0x03, 0xe0, 0x00, 0x78, 0x00,
	0x00, 0x07, 0x80, 0x00, 0xf0, 0x00,
	0x00, 0x0f, 0x80, 0x00, 0xf0, 0x00,
	0x00, 0x01, 0x80, 0x00, 0x10, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

static const uint8_t icon_thunderstorm[288]{
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x0a, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x1f, 0x00, 0x00, 0x00,
	0x00, 0x00, 0xff, 0xe0, 0x00, 0x00,
	0x00, 0x01, 0xc0, 0x70, 0x00, 0x00,
	0x00, 0x03, 0x80, 0x38, 0x00, 0x00,
	0x00, 0x07, 0x00, 0x1c, 0x00, 0x00,
	0x00, 0x0e, 0x00, 0x0e, 0x00, 0x00,
	0x00, 0x0c, 0x00, 0x06, 0x50, 0x00,
	0x00, 0x0c, 0x00, 0x07, 0xfe, 0x00,
	0x00, 0x1c, 0x00, 0x03, 0x57, 0x00,
	0x00, 0x08, 0x00, 0x02, 0x03, 0x80,
	0x00, 0x5c, 0x00, 0x00, 0x00, 0xc0,
	0x00, 0xfc, 0x00, 0x00, 0x00, 0xe0,
	0x01, 0xd0, 0x00, 0x00, 0x00, 0x70,
	0x03, 0x80, 0x00, 0x00, 0x00, 0x30,
	0x06, 0x00, 0x00, 0x00, 0x00, 0x30,
	0x0e, 0x00, 0x00, 0x00, 0x00, 0x38,
	0x0c, 0x00, 0x00, 0x00, 0x00, 0x10,
	0x0c, 0x00, 0x00, 0x00, 0x00, 0x30,
	0x0c, 0x00, 0x00, 0x00, 0x00, 0x30,
	0x0c, 0x00, 0x00, 0x00, 0x00, 0x60,
	0x04, 0x00, 0x00, 0x00, 0x00, 0x60,
	0x0e, 0x00, 0x00, 0xf8, 0x00, 0xe0,
	0x07, 0x00, 0x01, 0xf0, 0x01, 0xc0,
	0x03, 0xea, 0x03, 0xe0, 0xaf, 0x80,
	0x01, 0xff, 0x07, 0xc1, 0xff, 0x00,
	0x00, 0x3f, 0x0f, 0x83, 0xf8, 0x00,
	0x00, 0x00, 0x1f, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x3f, 0xa0, 0x00, 0x00,
	0x00, 0x00, 0x1f, 0xe0, 0x00, 0x00,
	0x00, 0x38, 0x3b, 0xc0, 0x20, 0x00,
	0x00, 0x70, 0x07, 0x00, 0x70, 0x00,
	0x00, 0xe0, 0x0f, 0x00, 0xe0, 0x00,
	0x01, 0xc0, 0x04, 0x01, 0xc0, 0x00,
	0x03, 0x80, 0x08, 0x03, 0x80, 0x00,
	0x00, 0x00, 0x10, 0x03, 0x00, 0x00,
	0x00, 0x00, 0x20, 0x02, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

static const uint8_t icon_wind[288]{
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x07, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x3e, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x30, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x60, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x60, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x60, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x40, 0x00, 0x00, 0x00, 0x00,
	0x00, 0xe0, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x70, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x38, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x1f, 0xff, 0xfd, 0xff, 0xfc,
	0x00, 0x0f, 0xff, 0xff, 0xff, 0xfe,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x5f, 0xff, 0xdf, 0xff, 0xdf, 0xfc,
	0x7f, 0xff, 0xff, 0xff, 0xff, 0xfe,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x05, 0xff, 0xff, 0xff, 0xfc,
	0x00, 0x3f, 0xff, 0xff, 0xff, 0xfe,
	0x00, 0x70, 0x00, 0x00, 0x00, 0x00,
	0x00, 0xe0, 0x00, 0x00, 0x00, 0x00,
	0x01, 0xc0, 0x00, 0x00, 0x00, 0x00,
	0x03, 0x80, 0x00, 0x00, 0x00, 0x00,
	0x03, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x02, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x06, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x0e, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x04, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x0e, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x04, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x06, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x07, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x03, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x03, 0x80, 0x00, 0x00, 0x00, 0x00,
	0x01, 0xc0, 0x00, 0x00, 0x00, 0x00,
	0x00, 0xf8, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x1f, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x0f, 0x80, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

enum weather_icons
{
	CLEAR_DAY,
	CLEAR_NIGHT,
	RAIN,
	SNOW,
	SLEET,
	WIND,
	FOG,
	CLOUDY,
	PARTLY_CLOUDY_DAY,
	PARTLY_CLOUDY_NIGHT,
	THUNDERSTORM,
	HAIL
};

Weather::Weather()
{
	for (int hr = 0; hr < FORECAST_HOURS; hr++)
	{
		weather_data_t *wd = new weather_data_t{
			this->get_icon(hr % 12),
			int8_t(50 + hr),
			int8_t(45 + 0.2 * hr),
			0};

		hourly_data[hr] = wd;
	}

	for (int day = 0; day < FORECAST_DAYS; day++)
	{
		forecast_data[day] = hourly_data[day];
		forecast_data[day]->day = day;
	}

	current_weather = hourly_data[0];
	current_day = -1;
}

Weather::~Weather()
{

}

bool Weather::is_new_day(int day)
{
	return current_day != day;
}

const uint8_t* Weather::get_icon(int icon)
{
	switch (icon)
	{
	case CLEAR_DAY:
		return icon_clear_day;
		break;
	case CLEAR_NIGHT:
		return icon_clear_night;
		break;
	case RAIN:
		return icon_rain;
		break;
	case SNOW:
		return icon_snow;
		break;
	case SLEET:
		return icon_sleet;
		break;
	case WIND:
		return icon_wind;
		break;
	case FOG:
		return icon_fog;
		break;
	case CLOUDY:
		return icon_cloudy;
		break;
	case PARTLY_CLOUDY_DAY:
		return icon_partly_cloudy_day;
		break;
	case PARTLY_CLOUDY_NIGHT:
		return icon_partly_cloudy_night;
		break;
	case THUNDERSTORM:
		return icon_thunderstorm;
		break;
	case HAIL:
		return icon_partly_cloudy_rain;
		break;
	default:
		return icon_clear_day;
		break;
	}
}

void Weather::get_weather(Messenger& messenger, int today)
{
	char buffer[1024];

	int result = messenger.get_request(URL_GET_FORECAST, buffer, 1024);
	if (result < 1) {
		// request failed
		return;
	}
	current_day = today;
	
	JSON_Value* raw = json_parse_string(buffer);
	JSON_Object* obj = json_value_get_object(raw);
	JSON_Array* hourly_array = json_object_get_array(obj, "hourly");
	int hours = min(json_array_get_count(hourly_array), FORECAST_HOURS);

	for (int i=0; i < hours; i++) {
		JSON_Object* hour_obj = json_array_get_object(hourly_array, i);
		int icon = (int)json_object_get_number(hour_obj, "i");
		int temp = (int)json_object_get_number(hour_obj, "t");
		hourly_data[i]->icon = get_icon(icon);
		hourly_data[i]->high = temp;
	}

	JSON_Array* daily_array = json_object_get_array(obj, "daily");
	int days = min(json_array_get_count(daily_array), FORECAST_DAYS);
	for (int i=0; i < days; i++) {
		JSON_Object* daily_obj = json_array_get_object(daily_array, i);
		int day = (int)json_object_get_number(daily_obj, "d");
		int icon = (int)json_object_get_number(daily_obj, "i");
		int tH = (int)json_object_get_number(daily_obj, "H");
		int tL = (int)json_object_get_number(daily_obj, "L");
		forecast_data[i]->day = day;
		forecast_data[i]->icon = get_icon(icon);
		forecast_data[i]->high = tH;
		forecast_data[i]->low = tL;
	}
	json_value_free(raw);
}

void Weather::set_current_weather(int hr)
{
	if (hr >= 0 && hr <= 24)
	{
		current_weather = hourly_data[hr];
	}
}

weather_data_t* Weather::get_current_weather()
{
	return current_weather;
}

weather_data_t* Weather::get_forecast(int day)
{
	day--;
	if (day >= 0 && day <= 2)
	{
		return forecast_data[day];
	}
	else
	{
		return forecast_data[0];
	}
}
