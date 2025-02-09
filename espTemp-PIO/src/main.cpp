/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com/esp8266-dht11dht22-temperature-and-humidity-web-server-with-arduino-ide/
*********/
#include <Arduino.h>

#include "config.h"

/* Add a file in this directory, called 'wifiConfig.h'
    This file should include two lines, setting your SSID and wifi password:

    const char* ssid = "SSID_name";
    const char* password = "Wifi_password";

    Update these with values suitable for your network.
*/

#include "wifiConfig.h"

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

  /***********
   * Screen
   ***********/
#if SCREEN
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
  dht.setup(dhtPin, DHTesp::dhtType);

  /***********
   * Wifi
   ***********/
  // setup_wifi();

#if MQTT
  wifiConnectHandler = WiFi.onStationModeGotIP(onWifiConnect);
  wifiDisconnectHandler = WiFi.onStationModeDisconnected(onWifiDisconnect);
#endif

  /***********
   * MQTT
   ***********/
#if MQTT
  mqttClient.onConnect(onMqttConnect);
  mqttClient.onDisconnect(onMqttDisconnect);
  mqttClient.onSubscribe(onMqttSubscribe);
  mqttClient.onUnsubscribe(onMqttUnsubscribe);
  mqttClient.onMessage(onMqttMessage);
  mqttClient.onPublish(onMqttPublish);
  mqttClient.setServer(MQTT_HOST, MQTT_PORT);
#endif

  connectToWifi();

  /***********
   * Web server
   ***********/
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
              request->send(200, "text/plain", String(sensor1Name).c_str()); });

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

  // Start server
  server.begin();
}

void loop()
{
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval)
  {
    previousMillis = currentMillis; // save the last time you updated the DHT values

    float newT = dht.getTemperature(); // read temperature as Celsius (the default)

    if (isnan(newT))
    { // if temperature read failed, don't change t value
      Serial.println("Failed to read temperature from DHT sensor!");
    }
    else
    {
      t = newT;
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
      Serial.print("Humidity: ");
      Serial.println(h);
    }
  }
}
