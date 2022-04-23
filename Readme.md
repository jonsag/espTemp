# espTemp

An ESP-01 module with a DHT22 temperature sensor  

Modified from [https://randomnerdtutorials.com/esp8266-dht11dht22-temperature-and-humidity-web-server-with-arduino-ide/](https://randomnerdtutorials.com/esp8266-dht11dht22-temperature-and-humidity-web-server-with-arduino-ide/)

## Hardware

Build according to schematics in KiCAD.  

![3dView](./KiCad/espTemp/espTemp.png)

## Software

Copy file wifiConfig.h.template in espTemp-PIO/src to wifiConfig.h.  
>$ cp espTemp-PIO/src/wifiConfig.h.template espTemp-PIO/src/wifiConfig.h

Edit the new file, entering your SSID and password.  
Compile and upload.  

Connect via serial (while module is still in  programmer) to find out IP and port.  
