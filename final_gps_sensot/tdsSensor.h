
#ifndef tdssensor_h
#define tdssensor_h

class tdsSensor
{
public:
  
  // setup(dhtPin) is deprecated, auto detection is not working well on ESP32. Use setup(dhtPin, DHTesp::DHT11) instead!
  tdsSensor(int pin);

  float readtds();
  protected:
  int _pin;
  float TU=0.0;
  float TU_value=0.0;
  float TU_calibration=0.0;
  float temp_data=25.0;
  float K_Value=3347.19;
};

#endif
