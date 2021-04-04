#define yudi_d 2
 
 
void setup(){
   
Serial.begin(9600);
 
pinMode(A7,INPUT);
pinMode(yudi_d,INPUT);
}
  
void loop(){
   
int a0= analogRead(A7);
Serial.print(a0); Serial.print("--");
 
int d2=digitalRead(yudi_d);//读取按键状态并储存在变量中
Serial.println(d2);
 
delay(1000);
}
