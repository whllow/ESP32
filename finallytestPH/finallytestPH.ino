/* Arduino DS18B20温度传感器教程
 */
//Include libraries
#include <OneWire.h> 
#include <DallasTemperature.h>
#include <HardwareSerial.h>
#include "tdsSensor.h"
#include "PHSensor.h"
//#include "GPS.h"


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
//GPS gps(0);
HardwareSerial MySerial(1);
char strs[75];

void setup(void)
{
   
  MySerial.begin(9600, SERIAL_8N1, 16, 17);//(16接tx)（17接rx）
  Serial.begin(9600); //Begin serial communication
  sensors.begin();
}

void loop(void)
{ 
  // Send the command to get temperatures
  sensors.requestTemperatures();  
  float temper = sensors.getTempCByIndex(0); // Why "byIndex"? You can have more than one IC on the same bus. 0 refers to the first IC on the wire//Update value every 1 sec.
  float tds = dstSe.readtds();
  float ph = phSe.getPHvalue(temper);
 /*
  gps.gpsRead();  //获取GPS数据
  gps.parseGpsBuffer();//解析GPS数据
 
   buildFrame(strs,temper,ph,tds,Save_Data.latitude,Save_Data.longitude);
*/
   
  dtostr2(strs,temper,tds);
  MySerial.write(strs);
  
  Serial.print("Frame is: ");
  Serial.println(strs);

  
  Serial.print("Temperature is: ");
  Serial.println(temper);
  Serial.print("PH is: ");
  Serial.println(ph);
  
  delay(2000);
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
