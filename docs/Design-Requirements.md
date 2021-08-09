# Requirements
  * User settable target temperature
  * Auto turn-down feature after 'x' hours
  * Receive updates from a server
  * Other user customizable settings
  * Different schedule for each day
  * Temporary override
  * Temperature in C or F

# Classes
## Temperature Sensor
  * Configure sensor
  * Read temperature and humidity
  * Convert between C and F

## OLED Menu
  * Manage screen state (i.e. which screen to show or ON/OFF)
  * Service button interrupts
  * Edit settings

## Thermostat
  * Turn on furnace once below lower threshold
  * Turn off furnace once above upper threshold
  * Maintain baseline temperature
  * Check for server updates
  * Send sensor readings
  