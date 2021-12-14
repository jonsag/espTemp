// Import required libraries
#include <Arduino.h>
#include <Hash.h>
#include <Adafruit_Sensor.h>

/***********
   Sensors
 ***********/
const int numberOfSensors = 1;
const String sensor1Name = "ESP-01 1";

/***********
   DHT config
 ***********/
/* DHT type, valid types are:
AUTO_DETECT Try to detect which sensor is connected (default if 2nd parameter is not used)
DHT11
DHT22
AM2302 (Packaged DHT22)
RHT03 (Equivalent to DHT22)
*/
#define dhtType AM2302
const int dhtPin = 2; // Connect DHT sensor to GPIO2

/***********
   Web server
 ***********/
const int serverPort = 8081;

/***********
   Misc
 ***********/
// current temperature & humidity, updated in loop()
float t = 0.0;
float h = 0.0;

unsigned long previousMillis = 0; // will store last time DHT was updated

// Updates DHT readings every 10 seconds
const long interval = 10000;
