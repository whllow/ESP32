#include <HardwareSerial.h>

HardwareSerial MySerial(1);

void setup() {
    MySerial.begin(9600, SERIAL_8N1, 16, 17);
    //17接芯片上RX
    //16接芯片上TX
    Serial.begin(9600);
}

void loop() {
  
    while (MySerial.available() > 0) {
        uint8_t byteFromSerial = MySerial.read();
        // Do something
        Serial.println((char)byteFromSerial);
       
    }
    /*
    //Write something like that
    MySerial.write("hello0");
    delay(2000);
    */
}
