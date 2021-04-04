#include <Adafruit_SSD1306.h>
#include <splash.h>
#include <ArduinoJson.h>
#include <WiFi.h>
#include <HTTPClient.h>
HTTPClient http;

typedef struct{
  char content[1024];
  char author[50];
  }saoHua;
 saoHua OneLine;
unsigned long startTime = millis();

void setup() {
 
  Serial.begin(115200);

  WiFi.mode(WIFI_STA); //设置为STA模式
  WiFi.disconnect();   //断开当前可能的连接
  delay(1000);
 
  const char *ssid = "wu"; //你的网络名称，区分大小写
  const char *password = "1342346379"; //你的网络密码
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) //等待网络连接成功
  {
    if (millis() - startTime >= 15000) // 15秒连接超时
    {
      Serial.println("Timed Out...");
      break;
    }
    else
    {
     Serial.println("Connecting....");      
    }
    delay(500);
  }
}
 
void loop() {
 
  if (WiFi.status() == WL_CONNECTED)
  {
    http.begin("https://v1.hitokoto.cn/"); // 访问指定URL
 
    int httpCode = http.GET();
    if (httpCode == HTTP_CODE_OK) {
      String pageData = http.getString();
//      Serial.println(httpCode);
 //     Serial.println(pageData); // 网页内容
      DynamicJsonBuffer jsonBuffer;
      JsonObject& root = jsonBuffer.parseObject(pageData);
      if(root.success()){
          strcpy(OneLine.content,root["hitokoto"]);
          strcpy(OneLine.author,root["from"]);
        Serial.println(OneLine.content);
        Serial.print("from:");
        Serial.println(OneLine.author);
        }
        else{
          Serial.println("parse Error");
          }
    }
    else
    {
     Serial.println("Get Error");
    }
    http.end();
  }
  else
  {
    Serial.println("WIFI ERROR");
  }
 
  delay(5000);
}
