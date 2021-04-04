
#define GpsSerial Serial
#define DebugSerial Serial

const int TrigPin = 25;
const int EchoPin = 26;
const int len = 27;
float cm;
void setup()
{
Serial.begin(9600);
pinMode(TrigPin, OUTPUT);
pinMode(EchoPin, INPUT);
}
void loop()
{
while (GpsSerial.available())
  {
    Serial.println(GpsSerial.read());
  }


//发一个10ms的高脉冲去触发TrigPin
digitalWrite(TrigPin, LOW);
delayMicroseconds(2);
digitalWrite(TrigPin, HIGH);
delayMicroseconds(10);
digitalWrite(TrigPin, LOW);


digitalWrite(TrigPin, LOW);
delayMicroseconds(2);
digitalWrite(TrigPin, HIGH);
delayMicroseconds(10);
digitalWrite(TrigPin, LOW);
  
cm = pulseIn(EchoPin, HIGH) / 58.0; //算成厘米
cm = (int(cm * 100.0)) / 100.0; //保留两位小数
Serial.print(cm);
Serial.print("cm");
Serial.println();
delay(500);
}
