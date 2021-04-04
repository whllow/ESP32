/* Arduino DS18B20温度传感器教程
 */
//Include libraries
#include <OneWire.h> 
#include <DallasTemperature.h>
#include <HardwareSerial.h>
// Data wire is plugged into pin 2 on the Arduino
#define ONE_WIRE_BUS 26
// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);
HardwareSerial MySerial(1);
char test2[25] ;
void setup(void)
{
   
  MySerial.begin(9600, SERIAL_8N1, 16, 17);
  Serial.begin(9600); //Begin serial communication
  Serial.println("Arduino Digital Temperature // Serial Monitor Version"); //Print a message
  sensors.begin();
}

void loop(void)
{ 
  // Send the command to get temperatures
  sensors.requestTemperatures();  
  Serial.print("Temperature is: ");
  float val = sensors.getTempCByIndex(0); // Why "byIndex"? You can have more than one IC on the same bus. 0 refers to the first IC on the wire//Update value every 1 sec.
  dtostr(test2,val);
  MySerial.write(test2);
  Serial.println(val);
  delay(2000);
}

char* dtostr(char *str, float d)
    {
        sprintf(str, "%.2f", d);
        return str;
    }

char* buildFrame(char *str, float temper,float ph,float com)
    {
        sprintf(str, "%.2f %.2f %.2f",temper,ph,com);
        return str;
    }
