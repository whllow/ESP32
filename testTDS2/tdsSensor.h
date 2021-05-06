
#ifndef tdssensor_h
#define tdssensor_h

class tdsSensor
{
public:
  
  // setup(dhtPin) is deprecated, auto detection is not working well on ESP32. Use setup(dhtPin, DHTesp::DHT11) instead!
  tdsSensor(int pin);

  float readtds(float tmpetValue);
  int getMedianNum(int bArray[], int iFilterLen);
  protected:
  int _pin;
  float averageVoltage=0.0;
  float tdsValue=0.0;
  int SCOUNT = 30;
};

#endif
