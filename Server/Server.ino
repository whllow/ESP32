#include <WiFi.h>
#include "ESPAsyncWebServer.h" //引入相应库

const char *ssid = "wu";
const char *password = "1342346379";

AsyncWebServer server(80); //声明WebServer对象

void handleRoot(AsyncWebServerRequest *request) //回调函数
{
  Serial.println("User requested.");
  request->send(200, "text/plain", "Hello World!"); //向客户端发送响应和内容
}

void handleRedirect(AsyncWebServerRequest *request) //回调函数
{
  Serial.println("User requested.");
  request->redirect("https://home.cnblogs.com/u/whllow");
}


void setup()
{
  Serial.begin(115200);
  Serial.println();

  WiFi.mode(WIFI_STA);
  WiFi.setSleep(false);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected");
  Serial.print("IP Address:");
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, handleRoot); //注册链接"/"与对应回调函数
  server.on("/wu", HTTP_GET, handleRedirect);
  server.begin(); //启动服务器

  Serial.println("Web server started");
}

void loop(){}
