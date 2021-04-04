#include "DHT.h"
#define DHTPIN 14
//our sensor is DHT22 type
#define DHTTYPE DHT11
//create an instance of DHT sensor

//light Sensor
#define PIN_D 2
#define PIN_A 0
//yuDi
#define yudi_d 5

DHT dht(DHTPIN, DHTTYPE);


void setup() {
 Serial.begin(9600);
  Serial.println("DHT22 sensor!");
  //call begin to start sensor
  dht.begin();


//yuDi
  pinMode(A7,INPUT);
  pinMode(yudi_d,INPUT);

}

void readDHT11(){
  //use the functions which are supplied by library.
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
     delay(2000);
    return;
  }
  // print the result to Terminal
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println(" *C ");
  //we delay a little bit for next read
  delay(2000);
  }
void readYuDi(){
  int a0= analogRead(A7);
  Serial.print(a0); Serial.print("--");
  int d2=digitalRead(yudi_d);//读取按键状态并储存在变量中
  Serial.println(d2);
  //delay(1000);
  }

  
void readLight(){
  int val;
  val=analogRead(PIN_A);
  Serial.print("a:");
  Serial.print(val);
  Serial.print(", d:");
  val=digitalRead(PIN_D);
  Serial.println(val);
  //delay(500);
  }



void loop() {
  readDHT11();
  readYuDi();
  readLight();
  Serial.println(" ");
  delay(2000);
  
}
