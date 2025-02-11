// Import required libraries
#include <Arduino.h>

#include <Hash.h>
#include <Adafruit_Sensor.h>

#define SCREEN 0 // 1 if screen is present
#define MQTT 1   // 1 to send values to an mqtt broker

/***********
 * Sensors
 ***********/
#define numberOfSensors 1
#define device_name "ESP-2388C5" // ESP-01
//#define device_name "ESP-35E561" // ESP-01
//#define device_name "ESP-E0569F" // nodeMCU v2

/***********
 * DHT config
 ***********/
/* DHT type, valid types are:
AUTO_DETECT Try to detect which sensor is connected (default if 2nd parameter is not used)
DHT11
DHT22
AM2302 (Packaged DHT22)
RHT03 (Equivalent to DHT22)
*/
#define dhtType DHT22

// Connect DHT sensor to GPIO2
const int dhtPin = 2;

/***********
 * Web server
 ***********/
#define serverPort 8081

/***********
 * Screen
 ***********/
#if SCREEN
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// set I2C pins (SDA = GPIO3, SCL = GPIO0), default clock is 100kHz
#define SDA 3
#define SCL 0

#define OLED_RESET 1 // define SSD1306 OLED reset (TX pin)

Adafruit_SSD1306 display(OLED_RESET);

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif
#endif

/***********
 * MQTT
 ***********/
#if MQTT
#define MQTT_HOST IPAddress(192, 168, 68, 173) // IP of the mqtt broker
#define MQTT_PORT 1883                         // port the broker is listening to

String config_payload;

// MQTT Topics
#define MQTT_TOP_TOPIC "environment"

#define MQTT_PUB_TEMP "ESP-2388C5/temperature"
#define MQTT_PUB_HUM "ESP-2388C5/humidity"

//#define MQTT_PUB_TEMP "ESP-35E561/temperature"
//#define MQTT_PUB_HUM "ESP-35E561/humidity"

//#define MQTT_PUB_TEMP "ESP-E0569F/temperature"
//#define MQTT_PUB_HUM "ESP-E0569F/humidity"

#endif

/***********
 * Misc
 ***********/
// current temperature & humidity, updated in loop()
float t = 0.0;
float h = 0.0;

unsigned long previousMillis = 0; // will store last time DHT was updated

// Updates DHT readings every 10 seconds
#define interval 10000

// Serial speed
#define serial_speed 115200

uint32_t chip_id;
String chip_id_HEX;