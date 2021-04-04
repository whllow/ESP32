/* Arduino DS18B20温度传感器教程
 */
//Include libraries
#include <OneWire.h> 
#include <DallasTemperature.h>
#include <HardwareSerial.h>
#include <SoftwareSerial.h>
#include "tdsSensor.h"
#include "PHSensor.h"

// Data wire is plugged into pin 2 on the Arduino
#define ONE_WIRE_BUS 26
#define DST 27
#define PH 25

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);
tdsSensor dstSe(DST);
PHSensor phSe(PH);
HardwareSerial MySerial(1);
SoftwareSerial GpsSerial(12, 14); 

char strs[75];

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

const unsigned int gpsRxBufferLength = 600;
char gpsRxBuffer[gpsRxBufferLength];
unsigned int ii = 0;
int L = 13; //LED指示灯引脚


void setup(void)
{
  GpsSerial.begin(9600);      //定义波特率9600，和我们店铺的GPS模块输出的波特率一致 
  MySerial.begin(9600, SERIAL_8N1, 16, 17);//(16接tx)（17接rx）
  Serial.begin(9600); //Begin serial communication
  sensors.begin();

  Save_Data.isGetData = false;
  Save_Data.isParseData = false;
  Save_Data.isUsefull = false;
}

void loop(void)
{ 
  gpsRead();  //获取GPS数据
  parseGpsBuffer();//解析GPS数据
  printGpsBuffer();
  
  
  
  // Send the command to get temperatures
  sensors.requestTemperatures();  
  float temper = sensors.getTempCByIndex(0); // Why "byIndex"? You can have more than one IC on the same bus. 0 refers to the first IC on the wire//Update value every 1 sec.
  float tds = dstSe.readtds();
  float ph = phSe.getPHvalue(temper);
  
 
  //buildFrame(strs,temper,ph,tds,Save_Data.latitude,Save_Data.longitude);

   
// dtostr2(strs,temper,tds);
 // MySerial.write(strs);

  Serial.print("tds is: ");
  Serial.println(tds);
  Serial.print("Temperature is: ");
  Serial.println(temper);
  Serial.print("PH is: ");
  Serial.println(ph);
  delay(1);
  
}
    
char* dtostr2(char *str, float temper,float tds)
    {
        sprintf(str, "%.2f %.2f",temper,tds);
        return str;
    }

char* buildFrame(char *str, float temper,float ph,float tds,char* latitude,char* longitude)
    {
        int i = 0;
        int sum = 0;
        int j = 0;
        sprintf(str, "%.2f %.2f %.2f ",temper,ph,tds);

        while(sum<3){
          if(str[i]==' ') sum++;
          i++;
        }
        while(latitude[j]!='\0')
          str[i++] = latitude[j++];
       j=0;
       str[i++] = ' '; 
       while(longitude[j]!='\0')
          str[i++] = longitude[j++];
        str[i] = '\0';   
        return str;
    }

void errorLog(int num)
{
  Serial.print("ERROR");
  Serial.println(num);
  while (1)
  {
    digitalWrite(L, HIGH);
    delay(300);
    digitalWrite(L, LOW);
    delay(300);
  }
}

void printGpsBuffer()
{
  if (Save_Data.isParseData)
  {
    Save_Data.isParseData = false;
    
    Serial.print("Save_Data.UTCTime = ");
    Serial.println(Save_Data.UTCTime);

    if(Save_Data.isUsefull)
    {
      Save_Data.isUsefull = false;
      Serial.print("Save_Data.latitude = ");
      Serial.println(Save_Data.latitude);
      Serial.print("Save_Data.N_S = ");
      Serial.println(Save_Data.N_S);
      Serial.print("Save_Data.longitude = ");
      Serial.println(Save_Data.longitude);
      Serial.print("Save_Data.E_W = ");
      Serial.println(Save_Data.E_W);
    }
    else
    {
      Serial.println("GPS DATA is not usefull!");
    }
    
  }
}

void parseGpsBuffer()
{
  char *subString;
  char *subStringNext;
  if (Save_Data.isGetData)
  {
    Save_Data.isGetData = false;
    Serial.println("**************");
    Serial.println(Save_Data.GPS_Buffer);

    
    for (int i = 0 ; i <= 6 ; i++)
    {
      if (i == 0)
      {
        if ((subString = strstr(Save_Data.GPS_Buffer, ",")) == NULL)
          errorLog(1);  //解析错误
      }
      else
      {
        subString++;
        if ((subStringNext = strstr(subString, ",")) != NULL)
        {
          char usefullBuffer[2]; 
          switch(i)
          {
            case 1:memcpy(Save_Data.UTCTime, subString, subStringNext - subString);break; //获取UTC时间
            case 2:memcpy(usefullBuffer, subString, subStringNext - subString);break; //获取UTC时间
            case 3:memcpy(Save_Data.latitude, subString, subStringNext - subString);break;  //获取纬度信息
            case 4:memcpy(Save_Data.N_S, subString, subStringNext - subString);break; //获取N/S
            case 5:memcpy(Save_Data.longitude, subString, subStringNext - subString);break; //获取纬度信息
            case 6:memcpy(Save_Data.E_W, subString, subStringNext - subString);break; //获取E/W

            default:break;
          }

          subString = subStringNext;
          Save_Data.isParseData = true;
          if(usefullBuffer[0] == 'A')
            Save_Data.isUsefull = true;
          else if(usefullBuffer[0] == 'V')
            Save_Data.isUsefull = false;

        }
        else
        {
          errorLog(2);  //解析错误
        }
      }


    }
  }
}


void gpsRead() {
  Serial.println("read ");
  while (GpsSerial.available())
  {
    gpsRxBuffer[ii++] = GpsSerial.read();
    if (ii == gpsRxBufferLength)clrGpsRxBuffer();
  }

  char* GPS_BufferHead;
  char* GPS_BufferTail;
  if ((GPS_BufferHead = strstr(gpsRxBuffer, "$GPRMC,")) != NULL || (GPS_BufferHead = strstr(gpsRxBuffer, "$GNRMC,")) != NULL )
  {
    if (((GPS_BufferTail = strstr(GPS_BufferHead, "\r\n")) != NULL) && (GPS_BufferTail > GPS_BufferHead))
    {
      memcpy(Save_Data.GPS_Buffer, GPS_BufferHead, GPS_BufferTail - GPS_BufferHead);
      Save_Data.isGetData = true;

      clrGpsRxBuffer();
    }
  }
}

void clrGpsRxBuffer(void)
{
  memset(gpsRxBuffer, 0, gpsRxBufferLength);      //清空
  ii = 0;
}
