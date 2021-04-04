#define LIGHT 0

const byte interruptPin = 25;

volatile int interruptCounter = 0;

int numberOfInterrupts = 0;

portMUX_TYPE mux = portMUX_INITIALIZER_UNLOCKED;

void setup() {

  Serial.begin(9600);

  Serial.println("Monitoring interrupts: ");

  pinMode(interruptPin, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(interruptPin), handleInterrupt, FALLING);

}

void handleInterrupt() {

  portENTER_CRITICAL_ISR(&mux);

  interruptCounter++;
  delay(1000);
  portEXIT_CRITICAL_ISR(&mux);

}

void loop() {

  if(interruptCounter>0){

      portENTER_CRITICAL(&mux);

      interruptCounter--;

      portEXIT_CRITICAL(&mux);

      int val = analogRead(LIGHT);
      Serial.print("light:");
      Serial.print(val);
      Serial.println();
      Serial.println(interruptCounter);
      numberOfInterrupts++;
      Serial.print("An interrupt has occurred. Total: ");
      Serial.println(numberOfInterrupts);

  }
  delay(2000);
}
