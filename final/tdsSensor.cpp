#include "tdsSensor.h"
#include "Arduino.h"

tdsSensor::tdsSensor(int pin){
    _pin = pin;
  }
float tdsSensor::readtds(float tmpetValue){
	int pv[SCOUNT];
	for(int i = 0; i < SCOUNT; i++ ){
    pv[i] = analogRead(_pin);
    delay(40);
  }
  averageVoltage = getMedianNum(pv,SCOUNT)*3.3/65535;
  Serial.println(averageVoltage);
  float compensationCoefficient=1.0+0.02*(tmpetValue-25.0);    //temperature compensation formula: fFinalResult(25^C) = fFinalResult(current)/(1.0+0.02*(fTP-25.0));
  float compensationVolatge=averageVoltage/compensationCoefficient;  //temperature compensation
  tdsValue=(133.42*compensationVolatge*compensationVolatge*compensationVolatge - 255.86*compensationVolatge*compensationVolatge + 857.39*compensationVolatge)*0.5; //convert voltage value to tds value
  return tdsValue;
}
int tdsSensor::getMedianNum(int bArray[], int iFilterLen) 
{
      int bTab[iFilterLen];
      for (byte i = 0; i<iFilterLen; i++)
      bTab[i] = bArray[i];
      int i, j, bTemp;
      for (j = 0; j < iFilterLen - 1; j++) 
      {
        for (i = 0; i < iFilterLen - j - 1; i++) 
          {
            if (bTab[i] > bTab[i + 1]) 
            {
                bTemp = bTab[i];
                bTab[i] = bTab[i + 1];
                bTab[i + 1] = bTemp;
             }
          }
      }
      if ((iFilterLen & 1) > 0)
        bTemp = bTab[(iFilterLen - 1) / 2];
      else
        bTemp = (bTab[iFilterLen / 2] + bTab[iFilterLen / 2 - 1]) / 2;
      return bTemp;
}
