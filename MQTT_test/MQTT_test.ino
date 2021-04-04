#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
 
//#define BUILTIN_LED 2
 
// Update these with values suitable for your network.
 
const char* ssid = "wu;
const char* password = "1342346379";
const char* mqtt_server = "TLVWVUDCK6.iotcloud.tencentdevices.com";
const char* device_id = "TLVWVUDCK6Esp32A01";
const char* device_name = "TLVWVUDCK6Esp32A01;12010126;NNH7E;1651131011";
const char* device_password = "f7a3fb5ce4f2627864e96935cd312dd35be044e65793dc27d152c858d191d733;hmacsha256";
const char* device_pub_sub = "TLVWVUDCK6/Esp32A01/data";


 
WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg_buf[200];
int value = 0;  //
//char one_type3_header[] = {'0x03','0x00','0x46'};
char dataTemplete[]="{"temperature":25.5,"time":%d}";
char msgJson[75];
char debug_buf[200];
int i;
unsigned short json_len=0;
uint8_t* packet_p;
uint8_t debug_buffer_start_index = 0;
 
 
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
    digitalWrite(BUILTIN_LED, HIGH);  // Turn the LED off by making the voltage HIGH
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
 
void setup() {
  pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output, where do it esp32 get gpio2 as led
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);  //not 1883 , one net use the port of 6002 as mqtt server
  client.connect(device_id,device_name,device_password);
  client.setCallback(callback);
}
 
void loop() {
 
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
 
  long now = millis();
  if (now - lastMsg > 2000) {
    lastMsg = now;
    ++value;
    //snprintf (msgJson, 75, "hello world #%ld", value);
    snprintf(msgJson,40,dataTemplete,22);
    json_len=strlen(msgJson); //packet length count the end char '\0'
    msg_buf[0]=char(0x03);  //palyLoad packet byte 1, one_net mqtt Publish packet payload byte 1, type3 , json type2
    msg_buf[1]=char(json_len>>8);  //high 8 bits of json_len (16bits as short int type)
    msg_buf[2]=char(json_len&0xff); //low 8 bits of json_len (16bits as short int type)
   // snprintf(msg_buf+3,40,dataTemplete,value);
   
   memcpy(msg_buf+3,msgJson,strlen(msgJson));
   msg_buf[3+strlen(msgJson)] = 0;
    Serial.print("Publish message: ");
    Serial.println(msgJson);
    client.publish("$dp",msg_buf,3+strlen(msgJson),false); // msg_buf as payload length which may have a "0x00"byte
     
    //debug one_net packet
    packet_p = client.getBufferPointer();
    for(i = 0 ; i< 200;i++)
    {
     //sprintf(debug_buf,"0x%02x ",msg_buf[i]);
     sprintf(debug_buf,"0x%02x ",packet_p[i]);
     Serial.print(debug_buf);
    }
    Serial.println();
    for(i = 0 ; i< 200;i++)
    {
     sprintf(debug_buf,"0x%02x ",msg_buf[i]);
     //sprintf(debug_buf,"0x%02x ",packet_p[i]);
     Serial.print(debug_buf);
    }
    Serial.println();
    debug_buffer_start_index=client.getDebugVar();
    Serial.println(debug_buffer_start_index);
  }
}
