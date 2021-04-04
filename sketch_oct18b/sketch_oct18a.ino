

#include<HardwareSerial.h>

HardwareSerial MySerial(1);
void setup() {
  // put your setup code here, to run once:
   MySerial.begin(115200,SERIAL_8N1,5,18);
}

void loop() {
  // put your main code here, to run repeatedly:
while (MySerial.available() > 0) {
        uint8_t byteFromSerial = MySerial.read();
        // Do something
    }
    
    //Write something like that
    MySerial.write("Hello World");
}
