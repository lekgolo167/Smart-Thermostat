#include <Arduino.h>
#include <Adafruit_SSD1306.h>
#include <RTCZero.h>
#include <queue>
#include <WIFIUdp.h>

#include "Initialization.hpp"
#include "Oled.hpp"
#include "MesgQueue.hpp"
#include "Timers.hpp"

sensor_readings *sensor = new sensor_readings;
thermostat_settings *settings = new thermostat_settings;
tm *clk = new tm;
RTCZero rtc;
WiFiUDP udp;
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
OLED oled = OLED(&display, clk, settings, sensor);
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
  initWiFi(udp);
  printWifiStatus();
  initRTC(rtc);
  thermostat.initialize();
  msg_queue.push(RTC_UPDATE);
  msg_queue.push(SAMPLE_AIR);
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
      thermostat.run_cycle();
      msg_queue.push(OLED_UPDATE);
      msg_queue.push(CHECK_FOR_UDP_MSG);
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
      break;
    }
    case UPDATE_SAMPLE_PERIOD:
    {
      TC4_reconfigure(settings->sample_period_sec);
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
      TC3_stop_timer();
      msg_queue.push(OLED_OFF);
      break;
    }
    case CHECK_FOR_UDP_MSG:
    {
      int packet_size = udp.parsePacket();
      if (packet_size)
      {

        // read the packet into packetBufffer

        int len = udp.read(packetBuffer, BUFF_SIZE);

        if (len > 0)
        {

          packetBuffer[len] = 0;
          int msg = atoi(packetBuffer);
          if (msg == 1)
          {
            msg_queue.push(GET_TEMPORARY_OVERRIDE);
          }
          else if (msg == 2)
          {
            msg_queue.push(UPDATE_SCHEDULE);
          }
        }

        Serial.println("Contents:");

        Serial.println(packetBuffer);
      }
      break;
    }
    case UPDATE_SCHEDULE:
    {
      thermostat.update_schedule();
      break;
    }
    case START_TEMPORARY_OVERRIDE:
    {
      thermostat.start_temporary_override();
      break;
    }
    case GET_TEMPORARY_OVERRIDE:
    {
      float temperature = get_temporary_temperature();
      if (temperature > 0.0)
      {
        settings->temporary_target = temperature;
        msg_queue.push(START_TEMPORARY_OVERRIDE);
      }
    }
    case SEND_SERVER_TEMPERATURE:
    {
      break;
    }
    case SEND_SERVER_STATS:
    {
      //sprintf(CURLMessageBuffer, "TARGET=%f&THRESH_L=%f&THRESH_H=%f", m_settings->targetTemp_F, m_settings->lower_threshold, m_settings->upper_threshold);
      //sendCURL(URL_STATS, CURLMessageBuffer);
      break;
    }
    case SEND_SERVER_MOTION:
    {
      break;
    }
    case SEND_SEVER_RUNTIME:
    {
      oled.set_runtime(thermostat.get_runtime());
      break;
    }
    case SEND_SERVER_FURNACE_STATE:
    {
      break;
    }
    case OLED_ON:
    {
      thermostat.set_moition_timestamp();
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
      thermostat.set_moition_timestamp();
      oled.next_menu();
      break;
    }
    case OLED_PREV_MENU:
    {
      thermostat.set_moition_timestamp();
      oled.previous_menu();
      break;
    }
    case OLED_EDIT_MENU:
    {
      thermostat.set_moition_timestamp();
      oled.edit();
      break;
    }
    case OLED_ROTARY_CCW:
    {
      thermostat.set_moition_timestamp();
      oled.rotary_dial(-1);
      break;
    }
    case OLED_ROTARY_CW:
    {
      thermostat.set_moition_timestamp();
      oled.rotary_dial(1);
      break;
    }
    default:
      break;
    } // end switch

    msg_queue.pop();
  }
}
