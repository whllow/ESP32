#include <WiFi.h>
#include <ArduinoJson.h>
#include "time.h"

const char* ssid = "wu";
const char* password = "1342346379";

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 8*3600;//这里采用UTC计时，中国为东八区，就是 8*60*60
const int   daylightOffset_sec = 8*3600;//同上

void printLocalTime()
{
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
  char str[40];
  float ph = 7.0;
  float  tds = 1400.0;
  float temper = 89.0;
  sprintf(str,"%d-%d-%d %d:%d:%d",1900+timeinfo.tm_year,timeinfo.tm_mon+1,timeinfo.tm_mday,timeinfo.tm_hour,timeinfo.tm_min,timeinfo.tm_sec);
    StaticJsonBuffer<100> jsonBuffer;
    JsonObject& root = jsonBuffer.createObject();
    root["device_id"] = "Esp32A01";
    root["time"] = str;
    root["PH"] = ph;
    root["TDS"] = tds;
    root["Temperature"] = temper;
    String output;
    root.printTo(output);
    Serial.println(output);
}

void setup()
{
  Serial.begin(9600);
  
  //connect to WiFi
  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }
  Serial.println(" CONNECTED");
  
  //init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  printLocalTime();

  //disconnect WiFi as it's no longer needed
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
}

void loop()
{
  delay(10000);
  printLocalTime();
}
