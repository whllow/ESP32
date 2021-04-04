#include <HardwareSerial.h>

HardwareSerial MySerial(1);

void setup() {
    MySerial.begin(9600, SERIAL_8N1, 16, 17);
    //17接芯片上RX
    //16接芯片上TX
    Serial.begin(9600);
}

void loop() {
    int i =0;
    while (MySerial.available() > 0) {
        int byteFromSerial = MySerial.read();
        // Do something
        Serial.print((char)byteFromSerial);
       i++;
    }
    if(i!=0)
      {
        Serial.println();
        i=0;
      }

}
