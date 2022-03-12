#include <Arduino.h>
#include <Adafruit_SSD1306.h>
#include <RTCZero.h>
#include <queue>
#include <WIFIUdp.h>

#include "Initialization.hpp"
#include "Oled.hpp"
#include "MesgQueue.hpp"
#include "Timers.hpp"
#include "Messenger.hpp"
#include "History.hpp"
#include "Weather.hpp"

sensor_readings *sensor = new sensor_readings;
thermostat_settings *settings = new thermostat_settings;
tm *clk = new tm;
RTCZero rtc;
Messenger messenger;
History history;
Weather weather;
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
OLED oled = OLED(&display, clk, &history, &weather, settings, sensor);
Thermostat thermostat = Thermostat(clk, settings, sensor);
std::queue<int> msg_queue;

const int BUFF_SIZE = 256;
char packetBuffer[BUFF_SIZE]; //buffer to hold incoming packet

//this function gets called by the interrupt at <sampleRate>Hertz
void TC4_Handler(void)
{
  // USER CODE HERE
  msg_queue.push(SAMPLE_AIR);
  // END OF USER CODE
  TC4->COUNT32.INTFLAG.bit.MC0 = 1; //Writing a 1 to INTFLAG.bit.MC0 clears the interrupt so that it will run again
}

void TC3_Handler(void)
{
  // USER CODE HERE
  if (millis() - thermostat.get_motion_timestamp() > settings->screen_timeout_millis)
  {
      msg_queue.push(NO_MOTION);
  }
  // END OF USER CODE
  TC3->COUNT16.INTFLAG.bit.MC0 = 1; //Writing a 1 to INTFLAG.bit.MC0 clears the interrupt so that it will run again
}

void service_msg_queue();
void printWifiStatus();

void setup()
{
  Serial.begin(9600);
  global_msg_queue = &msg_queue;
  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
  initGPIO();
  initI2C();
  initTimers();
  initWiFi();
  printWifiStatus();
  initRTC(rtc);
  thermostat.initialize();
  messenger.initialize();
  history.initialize(sensor->temperature_F);
  msg_queue.push(GET_EPOCH);
  msg_queue.push(RTC_UPDATE);
  msg_queue.push(SAMPLE_AIR);
  msg_queue.push(UPDATE_SCHEDULE);
  msg_queue.push(OLED_ON);
}

// the loop function runs over and over again forever
void loop()
{
  service_msg_queue();
}

void service_msg_queue()
{

  while (!msg_queue.empty())
  {
    int msg = msg_queue.front();
    Serial.println("Servicing");
    Serial.println(msg);
    switch (msg)
    {
    case SAMPLE_AIR:
    {
      thermostat.sample_air();
      history.insert(sensor->temperature_F);
      thermostat.run_cycle();
      msg_queue.push(OLED_UPDATE);
      msg_queue.push(CHECK_FOR_UDP_MSG);
      msg_queue.push(SEND_SERVER_TEMPERATURE);
      break;
    }
    case RTC_UPDATE:
    {
      time_t current_time = rtc.getEpoch();
      tm *current_clk = localtime(&current_time);

      clk->tm_hour = current_clk->tm_hour;
      clk->tm_min = current_clk->tm_min;
      clk->tm_sec = current_clk->tm_sec;
      clk->tm_mon = current_clk->tm_mon;
      clk->tm_year = current_clk->tm_year;
      clk->tm_wday = current_clk->tm_wday;
      clk->tm_yday = current_clk->tm_yday;
      clk->tm_mday = current_clk->tm_mday;

      if (weather.is_new_day(clk->tm_wday))
      {
        msg_queue.push(GET_FORECAST);
      }
      weather.set_current_weather(clk->tm_hour);
      break;
    }
    case GET_EPOCH:
    {
      uint32_t epoch = messenger.get_epoch();
      if (epoch) {
        rtc.setEpoch(epoch);
      }
    }
    case UPDATE_SAMPLE_PERIOD:
    {
      TC4_reconfigure(settings->sample_period_sec);
    }
    case UPDATE_SAMPLE_SUM:
    {
      break;
    }
    case MOTION_DETECTED:
    {
      msg_queue.push(OLED_ON);
      msg_queue.push(SEND_SERVER_MOTION);
      thermostat.set_moition_timestamp();
      TC3_start_timer();
      break;
    }
    case NO_MOTION:
    {
      if (digitalRead(MOTION_SENSOR_PIN) != HIGH) {
        TC3_stop_timer();
        msg_queue.push(OLED_OFF);
      }
      else { // motion sensor is still high restart timer
        msg_queue.push(START_SCREEN_TIMEOUT);
      }
      break;
    }
    case START_SCREEN_TIMEOUT:
    {
      thermostat.set_moition_timestamp();
      TC3_start_timer();
      break;
    }
    case CHECK_FOR_UDP_MSG:
    {
      int msg = messenger.check_inbox();

      if (msg == 1)
      {
        msg_queue.push(GET_TEMPORARY_OVERRIDE);
      }
      else if (msg == 2)
      {
        msg_queue.push(UPDATE_SCHEDULE);
      }
      break;
    }
    case UPDATE_SCHEDULE:
    {
      thermostat.update_schedule(messenger);
      break;
    }
    case GET_FORECAST:
    {
      weather.get_weather(messenger, clk->tm_wday);
    }
    case START_TEMPORARY_OVERRIDE:
    {
      thermostat.start_temporary_override();
      break;
    }
    case GET_TEMPORARY_OVERRIDE:
    {
      float temperature = messenger.get_temporary_temperature();
      if (temperature > 0.0)
      {
        settings->target_temperature = temperature;
        msg_queue.push(START_TEMPORARY_OVERRIDE);
        msg_queue.push(SEND_SERVER_STATS);
      }
    }
    case SEND_SERVER_TEMPERATURE:
    {
      int len = sprintf(packetBuffer, POST_TEMPERATURE, sensor->temperature_F, sensor->humidity);
      messenger.post_request(URL_TEMPERATURE, packetBuffer, len);
      break;
    }
    case SEND_SERVER_STATS:
    {
      int len = sprintf(packetBuffer, POST_STATS, settings->target_temperature, settings->lower_threshold, settings->upper_threshold);
      messenger.post_request(URL_STATS, packetBuffer, len);
      break;
    }
    case SEND_SERVER_MOTION:
    {
      int len = sprintf(packetBuffer, POST_MOTION, 1);
      messenger.post_request(URL_MOTION, packetBuffer, len);
      break;
    }
    case SEND_SEVER_RUNTIME:
    {
      oled.set_runtime(thermostat.get_runtime());
      int len = sprintf(packetBuffer, POST_RUNTIME, thermostat.get_runtime());
      messenger.post_request(URL_STATS, packetBuffer, len);
      break;
    }
    case SEND_SERVER_FURNACE_STATE:
    {
      int len = sprintf(packetBuffer, POST_FURNACE_STATE, thermostat.get_furnace_state());
      messenger.post_request(URL_STATS, packetBuffer, len);
      break;
    }
    case OLED_ON:
    {
      oled.on();
      break;
    }
    case OLED_OFF:
    {
      oled.off();
      break;
    }
    case OLED_UPDATE:
    {
      oled.update();
      break;
    }
    case OLED_NEXT_MENU:
    {
      oled.next_menu();
      msg_queue.push(START_SCREEN_TIMEOUT);
      break;
    }
    case OLED_PREV_MENU:
    {
      oled.previous_menu();
      msg_queue.push(START_SCREEN_TIMEOUT);
      break;
    }
    case OLED_EDIT_MENU:
    {
      oled.edit();
      msg_queue.push(START_SCREEN_TIMEOUT);
      break;
    }
    case OLED_ROTARY_CCW:
    {
      oled.rotary_dial(-1);
      msg_queue.push(START_SCREEN_TIMEOUT);
      break;
    }
    case OLED_ROTARY_CW:
    {
      oled.rotary_dial(1);
      msg_queue.push(START_SCREEN_TIMEOUT);
      break;
    }
    default:
      break;
    } // end switch

    msg_queue.pop();
  }
  
}

void printWifiStatus() {

  // print the SSID of the network you're attached to:

  Serial.print("SSID: ");

  Serial.println(WiFi.SSID());

  // print your board's IP address:

  IPAddress ip = WiFi.localIP();

  Serial.print("IP Address: ");

  Serial.println(ip);

  // print the received signal strength:

  long rssi = WiFi.RSSI();

  Serial.print("signal strength (RSSI):");

  Serial.print(rssi);

  Serial.println(" dBm");
}
