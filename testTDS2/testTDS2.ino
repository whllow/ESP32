#include "tdsSensor.h"
#define DST 27
tdsSensor dstSe(DST);
void setup(void)
{
   
  
  adcAttachPin(DST);//将引脚连接到ADC
  adcStart(DST);//在连接的引脚总线上开始ADC转换
  analogReadResolution(16);//设置aliogRead返回值的分辨
  Serial.begin(9600); //Begin serial communication
  pinMode(TdsSensorPin,INPUT);
}


void loop(void)
{ 
   float tds = dstSe.readtds(27);
   Serial.print("tds:");
   Serial.println(tds);


}
