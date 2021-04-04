#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include <HTTPClient.h>
HTTPClient http;
const char *ssid = "MyEsp32";
const char *password = "1342346379";

const char *netssid = "wu";
const char *netpassword = "1342346379";

void handleRoot(AsyncWebServerRequest *request) //回调函数
{
  Serial.println("User requested.");
  request->send(200, "text/plain", "Hello World!"); //向客户端发送响应和内容
}
void handleRedirect(AsyncWebServerRequest *request) //回调函数
{
  Serial.println("hello");
  int param = request->params();
  for(int i=0;i<param;i++){
    AsyncWebParameter* p = request->getParam(i);
  if(p->isFile()){ //p->isPost() is also true
    Serial.printf("FILE[%s]: %s, size: %u\n", p->name().c_str(), p->value().c_str(), p->size());
  } else if(p->isPost()){
    Serial.printf("POST[%s]: %s\n", p->name().c_str(), p->value().c_str());
  } else { //GET
    Serial.printf("GET[%s]: %s\n", p->name().c_str(), p->value().c_str());
   
      Serial.println(p->value().c_str());
       http.begin(p->value().c_str());
       
       int httpCode = http.GET();
       if(httpCode == HTTP_CODE_OK) {
        String pageData = http.getString();
        Serial.println(pageData);
        request->send(200,"text/plain",pageData);
        }
       break;
  }
 }
}
AsyncWebServer server(80);
void setup(){
  Serial.begin(115200);
  WiFi.softAP(ssid, password);
  Serial.println();
  Serial.print("IP address: ");
  Serial.println(WiFi.softAPIP());
  
  WiFi.begin(netssid, netpassword);
 
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  
//  Serial.print("IP address: ");
//  Serial.println(WiFi.localIP());
  server.on("/", HTTP_GET, handleRoot); //注册链接"/"与对应回调函数
  server.on("/wu", HTTP_GET, handleRedirect);
  
  server.begin();
}
void loop(){}
