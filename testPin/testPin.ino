#define DHTPIN 17

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
   pinMode(DHTPIN,INPUT);
  Serial.println("DHT22 sensor!");
}

void loop() {
  // put your main code here, to run repeatedly:
  int a0= analogRead(DHTPIN);
  Serial.println(a0);
  delay(2000);
}
