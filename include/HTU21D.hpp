/* 
 HTU21D Humidity Sensor Library
 By: Nathan Seidle
 SparkFun Electronics
 Date: September 22nd, 2013
 License: This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).
 
 Get humidity and temperature from the HTU21D sensor.
 
 */
 

#if defined(ARDUINO) && ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#include <Wire.h>


class HTU21D {

public:
  HTU21D();

  //Public Functions
  void begin();
  float readHumidity(void);
  float readTemperature(void);
  void setResolution(byte resBits);
  void selfTest(bool enabled);

  //Public Variables
  static struct {
    // temperature and humidity resolutions (cannot be set independently)
    const byte TEMP_14b_RH_12b = 0b00000000;
    const byte TEMP_13b_RH_10b = 0b10000000;
    const byte TEMP_12b_RH_8 = 0b00000001;
    const byte TEMP_11b_RH_11b = 0b10000001;

  } HTU21D_Resolutions;

private:
  //Private Functions

  byte read_user_register(void);
  byte check_crc(uint16_t message_from_sensor, uint8_t check_value_from_sensor);

  //Private Variables
  static const byte HTDU21D_ADDRESS = 0x40;
  static const byte TRIGGER_TEMP_MEASURE_HOLD = 0xE3;
  static const byte TRIGGER_HUMD_MEASURE_HOLD = 0xE5;
  static const byte TRIGGER_TEMP_MEASURE_NOHOLD = 0xF3;
  static const byte TRIGGER_HUMD_MEASURE_NOHOLD = 0xF5;
  static const byte WRITE_USER_REG = 0xE6;
  static const byte READ_USER_REG = 0xE7;
  static const byte SOFT_RESET = 0xFE;
  static const byte HEATER_EN_BIT = 0x04;

};