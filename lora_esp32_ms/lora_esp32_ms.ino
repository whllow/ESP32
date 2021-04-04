#define SendData 0

const byte interruptPin = 25;
String str="#";
String myData = "hello";
char c;
volatile int interruptCounter = 0;

int numberOfInterrupts = 0;

portMUX_TYPE mux = portMUX_INITIALIZER_UNLOCKED;

void setup() {

  Serial.begin(9600);

  Serial.println("Monitoring interrupts: ");

  pinMode(interruptPin, INPUT_PULLUP);
  pinMode(SendData, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(interruptPin), handleInterrupt, FALLING);

}

void handleInterrupt() {

  portENTER_CRITICAL_ISR(&mux);
  str = (char)analogRead(interruptPin);
  while((c=(char)analogRead(interruptPin))!='')
    str += c;
  portEXIT_CRITICAL_ISR(&mux);

}

void loop() {

  if(str!="#"){
    Serial.println(str);
    str = "#";
    delay(2000);
    analogWrite(SendData,myData);
    }
  delay(2000);
}
