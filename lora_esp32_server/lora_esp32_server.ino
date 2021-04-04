#include <HardwareSerial.h>
#define PIN_A 0
#define PIN_D 2
HardwareSerial MySerial(1);

void setup() {
    MySerial.begin(9600, SERIAL_8N1, 16, 17);
    //17接芯片上RX
    //16接芯片上TX
    Serial.begin(9600);
}

void loop() {
  
    int val;
    val=analogRead(PIN_A);
    Serial.print("a:");
    Serial.print(val);
    
    
    //Write something like that
    MySerial.write(val);
    delay(2000);
   
}
