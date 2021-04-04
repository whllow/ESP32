//PH模块输出范围调整为0~5.0，调整方法如下：
//将PH计放在PH为9.18的溶液中，旋转电位器，调整电压为2.12V
//将PH计放在PH为6.86的溶液中，旋转电位器，调整电压为2.52V
//将PH计放在PH为4.0的溶液中，旋转电位器，调整电压为3.0V

#include "PHSensor.h"
#include "Arduino.h"

PHSensor::PHSensor(int pin){
  _pin = pin;  
}


float PHSensor::getPHvalue(float tmpetValue){
  int pv[ARRY_LENGTH];
  float PH_VALUE = 0;
  for(int i = 0; i < ARRY_LENGTH; i++ ){
    pv[i] = analogRead(_pin);
    delay(1);
  }
  for(int i = 0; i < ARRY_LENGTH; i++){
    for(int k = i; k < ARRY_LENGTH; k++ ){
      if( pv[i] < pv[k] ){
        int tmp = pv[i];
        pv[i] = pv[k];
        pv[k] = tmp;
      }
    }
  }

  //温度补偿开始
  if( tmpetValue > 42 )  pv[ARRY_LENGTH/2] += 5;
  else if(tmpetValue > 28){
    pv[ARRY_LENGTH/2] += 5*(tmpetValue - 28)/14;
  }
  //温度补偿结束
  
  PH_VALUE = pv[ARRY_LENGTH/2];
  PH_VALUE = -5.887*(PH_VALUE*5/1024) + 21.677;  
  if(PH_VALUE > 14.1){
    PH_VALUE = 14.1;
  }
  if( PH_VALUE < 0 ){
    PH_VALUE = 0;
  }
  
  return PH_VALUE;

}
