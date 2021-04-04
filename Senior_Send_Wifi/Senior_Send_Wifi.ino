#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include <HTTPClient.h>
HTTPClient http;
const char *ssid = "MyEsp32";
const char *password = "1342346379";

void handleServer(AsyncWebServerRequest *request) //回调函数
{
  Serial.println("User requested.");
  request->send(200, "text/plain", "Hello World!"); //向客户端发送响应和内容
}
void handleClientRequest(AsyncWebServerRequest *request) //回调函数
{
    
}

AsyncWebServer server(80);
void setup(){
  Serial.begin(115200);
  WiFi.softAP(ssid, password);
  Serial.println();
  Serial.print("IP address: ");
  Serial.println(WiFi.softAPIP());
 
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  
//  Serial.print("IP address: ");
//  Serial.println(WiFi.localIP());
  server.on("/Server", HTTP_GET, handleServer); //注册链接"/"与对应回调函数
  server.on("/ClientRequest", HTTP_GET, handleClientRequest);
  
  server.begin();
}
void loop(){}
