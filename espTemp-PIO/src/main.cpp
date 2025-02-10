/*********
 * Jon Sagebrand
 * Credits to Rui Santos
 * Read his tutorials at
 * https://randomnerdtutorials.com/esp8266-dht11dht22-temperature-and-humidity-web-server-with-arduino-ide/ and
 * https://RandomNerdTutorials.com/esp8266-nodemcu-mqtt-publish-bme680-arduino/
 *********/
#include <Arduino.h>

#include "config.h"

/***********
 * Add a file in this directory, called 'secrets.h'
 * You can copy the 'secrets.h.template'
 * This file should include the following lines:
 *
 * #define WIFI_SSID "<your SSID>"
 * #define WIFI_PASSWORD "<your wifi password>"
 *
 * #define MQTT_USER "<username for the mqtt broker>"
 * #define MQTT_PASSWORD "<password for the mqtt broker>"
 *
 * Update these with values suitable for your network.
 ***********/

#include "secrets.h"

#include "wifi.h"

#if MQTT
#include "mqtt.h"
#endif

#include "webServer.h"
#include "dht.h"

#if SCREEN
#include "screen.h"
#endif

void setup()
{
  Serial.begin(serial_speed); // serial port for debugging purposes
  Serial.println("Serial started.");

  /***********
   * Screen
   ***********/
#if SCREEN
  Serial.println("Setting up screen ...");
  Wire.begin(SDA, SCL);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3D);

  // Wire.setClock(400000L);   // uncomment this to set I2C clock to 400kHz

  display.display(); // display the splashscreen
  delay(500);

  display.clearDisplay();

  drawText(1, 10, 10, "Hello World!");
  delay(500);

  display.clearDisplay();
#endif

  /***********
   * DHT config
   ***********/
  Serial.println("Setting up DHT sensor ...");
  dht.setup(dhtPin, DHTesp::dhtType);

  /***********
   * Wifi
   ***********/
  // setup_wifi();

#if MQTT
  Serial.println("Setting up wifi ...");
  wifiConnectHandler = WiFi.onStationModeGotIP(onWifiConnect);
  wifiDisconnectHandler = WiFi.onStationModeDisconnected(onWifiDisconnect);
#endif

  /***********
   * MQTT
   ***********/
#if MQTT
  Serial.println("Setting up mqtt ...");
  mqttClient.onConnect(onMqttConnect);
  mqttClient.onDisconnect(onMqttDisconnect);
  // mqttClient.onSubscribe(onMqttSubscribe);
  // mqttClient.onUnsubscribe(onMqttUnsubscribe);
  // mqttClient.onMessage(onMqttMessage);
  mqttClient.onPublish(onMqttPublish);
  mqttClient.setServer(MQTT_HOST, MQTT_PORT);
  // mqttClient.setCredentials(MQTT_USER, MQTT_PASSWORD);
  mqttClient.setCredentials(MQTT_USER, MQTT_PASSWORD).setClientId(device_name);
#endif

  Serial.println("Connecting to wifi ...");
  connectToWifi();

  /***********
   * Web server
   ***********/
  Serial.println("Setting up web server ...");
  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send_P(200, "text/html", index_html, processor); });
  server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send_P(200, "text/plain", String(t).c_str()); });
  server.on("/humidity", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send_P(200, "text/plain", String(h).c_str()); });

  server.on("/count.php", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send_P(200, "text/plain", String(numberOfSensors).c_str()); });

  // Send a GET request to <IP>/get?message=<message>
  server.on("/name.php", HTTP_GET, [](AsyncWebServerRequest *request)
            {
              String message;
              if (request->hasParam(PARAM_MESSAGE))
              {
                message = request->getParam(PARAM_MESSAGE)->value();
              }
              else
              {
                message = "No message sent";
              }
              //request->send(200, "text/plain", "Hello, GET: " + message);
              request->send(200, "text/plain", String(device_name).c_str()); });

  server.on("/value.php", HTTP_GET, [](AsyncWebServerRequest *request)
            {
              String message;
              if (request->hasParam(PARAM_MESSAGE))
              {
                message = request->getParam(PARAM_MESSAGE)->value();
              }
              else
              {
                message = "No message sent";
              }
              request->send(200, "text/plain", String(t).c_str()); });

  server.onNotFound(notFound);

  Serial.println("Starting web server ...");
  server.begin(); // start server

  Serial.println("Setup finished.");
  Serial.println("Entering main loop ...");
  Serial.println();
}

void loop()
{
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval)
  {
    previousMillis = currentMillis; // save the last time you updated the DHT values

    Serial.println("Reading temperature and humidity ...");

    float newT = dht.getTemperature(); // read temperature as Celsius (the default)

    if (isnan(newT))
    { // if temperature read failed, don't change t value
      Serial.println("Failed to read temperature from DHT sensor!");
    }
    else
    {
      t = newT;

      uint16_t packetIdPub1 = mqttClient.publish(MQTT_PUB_TEMP, 1, true, String(t).c_str());
      Serial.printf("Publishing on topic %s at QoS 1, packetId: %i ", MQTT_PUB_TEMP, packetIdPub1);
      Serial.printf("Message: %.2f \n", t);

      Serial.print("Temperature: ");
      Serial.println(t);
    }

    float newH = dht.getHumidity(); // read Humidity

    if (isnan(newH))
    { // if humidity read failed, don't change h value
      Serial.println("Failed to read humidity from DHT sensor!");
    }
    else
    {
      h = newH;

      uint16_t packetIdPub2 = mqttClient.publish(MQTT_PUB_HUM, 1, true, String(h).c_str());
      Serial.printf("Publishing on topic %s at QoS 1, packetId: %i ", MQTT_PUB_HUM, packetIdPub2);
      Serial.printf("Message: %.2f \n", h);

      Serial.print("Humidity: ");
      Serial.println(h);
    }
  }
}
