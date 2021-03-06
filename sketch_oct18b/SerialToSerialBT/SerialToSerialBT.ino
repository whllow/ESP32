//This example code is in the Public Domain (or CC0 licensed, at your option.)
//By Evandro Copercini - 2018
//
//This example creates a bridge between Serial and Classical Bluetooth (SPP)
//and also demonstrate that SerialBT have the same functionalities of a normal Serial

#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32test"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
  pinMode(5,OUTPUT);

  //digitalWrite(5,HIGH);
}

void loop() {
  if (SerialBT.available()) {
    //SerialBT.write(Serial.read());
   char data = SerialBT.read();
  if(data=='a'){
    digitalWrite(5,HIGH);
//    delay(3000);
//    digitalWrite(5,LOW);
    }
   if(data=='d'){
    digitalWrite(5,LOW);
    }
  }

  delay(50);
}
