#ifndef gps_h
#define gps_h
//此处为了兼容其他的多串口Arduino板
#include <HardwareSerial.h>
#define GpsSerial Serial
#define DebugSerial Serial
#define gpsRxBufferLength  600
struct
{
  char GPS_Buffer[80];
  bool isGetData;   //是否获取到GPS数据
  bool isParseData; //是否解析完成
  char UTCTime[11];   //UTC时间
  char latitude[11];    //纬度
  char N_S[2];    //N/S
  char longitude[12];   //经度
  char E_W[2];    //E/W
  bool isUsefull;   //定位信息是否有效
} Save_Data;




class GPS
{
public:
  
  // setup(dhtPin) is deprecated, auto detection is not working well on ESP32. Use setup(dhtPin, DHTesp::DHT11) instead!
  GPS(int num);
  void errorLog(int num);
  void printGpsBuffer();
  void parseGpsBuffer();
  void gpsRead();
  void clrGpsRxBuffer(void);
  
  protected:
  char gpsRxBuffer[gpsRxBufferLength];
  unsigned int ii = 0;
};

#endif
