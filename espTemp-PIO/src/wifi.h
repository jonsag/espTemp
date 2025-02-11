#include <ESP8266WiFi.h>

void connectToWifi()
{
  Serial.println("Connecting to Wi-Fi...");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
}

String convertDecimalToHex(long n)
{
  String hexNum;
  long remainder;

  while (n > 0)
  {

    remainder = n % 16;
    n = n / 16;

    if (remainder < 10)
    {
      hexNum = String(remainder) + hexNum;
    }

    switch (remainder)
    {

    case 10:
      hexNum = "A" + hexNum;
      break;

    case 11:
      hexNum = "B" + hexNum;
      break;

    case 12:
      hexNum = "C" + hexNum;
      break;

    case 13:
      hexNum = "D" + hexNum;
      break;

    case 14:
      hexNum = "E" + hexNum;
      break;

    case 15:
      hexNum = "F" + hexNum;
      break;
    }
  }
  return hexNum;
}

void get_chip_ID()
{
#ifdef ESP8266
  chip_id = ESP.getChipId();
#endif
#ifdef ESP32
  uint64_t macAddress = ESP.getEfuseMac();
  uint64_t macAddressTrunc = macAddress << 40;
  chip_id = macAddressTrunc >> 40;
#endif

  chip_id_HEX = convertDecimalToHex(chip_id);
}

/*void setup_wifi()
{
  delay(100);

  Serial.println("");
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("Web server port: ");
  Serial.println(serverPort);
  Serial.println();

  connectToMqtt();
}
*/