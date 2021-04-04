#include <dht11.h>     //引用dht11库文件，使得下面可以调用相关参数
#define DHT11PIN 2     //定义温湿度针脚号为8号引脚
//int ledPin=11;

void setup(){         //初始化设置
  Serial.begin(9600);      //设置波特率参数
  pinMode(DHT11PIN,OUTPUT);
}

void loop(){                          //循环
  int chk = DHT11.read(DHT11PIN);     //将读取到的值赋给chk
 
  int hum=(float)DHT11.humidity;      //将湿度值赋给hum
  Serial.print("hum:");
  Serial.print(hum);
  Serial.print("%/t");
 
  int tem=(float)DHT11.temperature;   //将湿度值赋给tem
  Serial.print(" tem:");
  Serial.print(tem);
  Serial.println("*C");
 delay(2000);
}
