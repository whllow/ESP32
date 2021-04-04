/* Arduino DS18B20温度传感器教程
 */
//Include libraries
#include <OneWire.h> 
#include <DallasTemperature.h>
#include <HardwareSerial.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>


#include "tdsSensor.h"
#include "PHSensor.h"


// Data wire is plugged into pin 2 on the Arduino
#define ONE_WIRE_BUS 26
#define DST 27
#define PH 25
#define BUILTIN_LED 2

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);
tdsSensor dstSe(DST);
PHSensor phSe(PH);

HardwareSerial MySerial(1);


const char* ssid = "wu";
const char* password = "1342346379";
const char* mqtt_server = "TLVWVUDCK6.iotcloud.tencentdevices.com";
const char* device_id = "TLVWVUDCK6Esp32A01";
const char* device_name = "TLVWVUDCK6Esp32A01;12010126;NNH7E;1651131011";
const char* device_password = "f7a3fb5ce4f2627864e96935cd312dd35be044e65793dc27d152c858d191d733;hmacsha256";
const char* device_pub_sub = "TLVWVUDCK6/Esp32A01/data";

const char* device_sid = "Esp32A01";


WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
#define MSG_BUFFER_SIZE  (50)
char msg[100];
int output_len = 0;;  //
int flag=1;



void setup(void)
{
   
  MySerial.begin(9600, SERIAL_8N1, 16, 17);//(16接tx)（17接rx）
  Serial.begin(9600); //Begin serial communication
  setup_wifi();   //wifi 连接
  client.setServer(mqtt_server, 1883);  //服务器连接端口
  client.connect(device_id,device_name,device_password); // 服务器连接密码和用户名
  client.setCallback(callback);   //回调函数
  sensors.begin();
}

void loop(void)
{ 
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  unsigned long now = millis();
  // 获取传感器的参数
  sensors.requestTemperatures();  
  float temper = sensors.getTempCByIndex(0); // Why "byIndex"? You can have more than one IC on the same bus. 0 refers to the first IC on the wire//Update value every 1 sec.
  float tds = dstSe.readtds();
  float ph = phSe.getPHvalue(temper);
  
 
//   buildFrame(strs,temper,ph,tds,Save_Data.latitude,Save_Data.longitude);

  //构建传感器字符串的参数 
    StaticJsonBuffer<100> jsonBuffer;
    JsonObject& root = jsonBuffer.createObject();
    root["device_id"] = "Esp32A01";
    root["time"] = now;
    root["PH"] = ph;
    root["TDS"] = tds;
    root["Temperature"] = temper;
    String output;
    root.printTo(output);
    Serial.print("Publish message: ");
    Serial.println(output);
   
    output.toCharArray(msg,output.length()+1);
    client.publish(device_pub_sub, msg);
    

  Serial.print("tds is: ");
  Serial.println(tds);
  Serial.print("Temperature is: ");
  Serial.println(temper);
  Serial.print("PH is: ");
  Serial.println(ph);
  if(flag == 0)
  {
    //没有WiFi 就是lora自主网络传输
    MySerial.write(msg);
    Serial.println("lora send");
  }
  else{
  //直接上传到mqtt服务器上
  
  if (now - lastMsg > 2000) {
    lastMsg = now;
    
    output_len = output.length() + 1;
    Serial.print("output length:");
    Serial.println(output_len);
    
   
  }


  }
  
  delay(2000);
}
    
char* dtostr2(char *str, float temper,float tds,float ph)
    {
        sprintf(str, "%.2f %.2f %.2f",temper,tds,ph);
        return str;
    }

char* buildFrame(char *str, float temper,float ph,float tds,char* latitude,char* longitude)
    {
        int i = 0;
        int sum = 0;
        int j = 0;
        sprintf(str, "%.2f %.2f %.2f ",temper,ph,tds);

        while(sum<3){
          if(str[i]==' ') sum++;
          i++;
        }
        while(latitude[j]!='\0')
          str[i++] = latitude[j++];
       j=0;
       str[i++] = ' '; 
       while(longitude[j]!='\0')
          str[i++] = longitude[j++];
        str[i] = '\0';   
        return str;
    }

void setup_wifi() {
 
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  randomSeed(micros());
 
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
 
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
 
  // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '1') {
    digitalWrite(BUILTIN_LED, LOW);   // Turn the LED on (Note that LOW is the voltage level
    // but actually the LED is on; this is because
    // it is active low on the ESP-01)
  } else {
//    digitalWrite(BUILTIN_LED, HIGH);  // Turn the LED off by making the voltage HIGH
  }
 
}
 
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    //String clientId = "设备_id";
    //clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(device_id,device_name,device_password)) {  //One net user name as product ID , and password as APIKey
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish(device_pub_sub, "hello world");
      // ... and resubscribe
      client.subscribe(device_pub_sub);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}


    
