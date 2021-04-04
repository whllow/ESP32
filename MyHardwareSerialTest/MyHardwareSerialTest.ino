#include <HardwareSerial.h>

char c;
char str[32] = {0};
int i = 0;
HardwareSerial MySerial(1);

void setup() {
   Serial.begin(9600);
    MySerial.begin(9600, SERIAL_8N1, 16, 17);//RX16,TX:17
}

void loop() {
    i=0;
    while (MySerial.available() > 0) {
        Serial.print("i:");
        Serial.println(i);
        c = M
        
        ySerial.read();
        str[i&31] = c;
        i++;     
        // Do something
    }
    if(i!=0){
      for(int j =0;j<i;j++){
        Serial.print(str[i]);
        }
        Serial.println();
        delay(3000);
        //Write something like that
    }
    Serial.println("=====");
    MySerial.write("hello");
    MySerial.flush();
    delay(3000);
}
