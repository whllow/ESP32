
#ifndef phsensor_h
#define phsensor_h

class PHSensor
{
public:
  
  // setup(dhtPin) is deprecated, auto detection is not working well on ESP32. Use setup(dhtPin, DHTesp::DHT11) instead!
  PHSensor(int pin);

  float getPHvalue(float tmpetValue);
  
  protected:
  int _pin;
  int ARRY_LENGTH = 10;
};

#endif
