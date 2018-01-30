/********************************************************************/
// First we include the libraries
#include <OneWire.h> 
#include <DallasTemperature.h>
#include <Arduino.h>
#include <Wire.h>
#include <UnoWiFiDevEd.h>

#define CONNECTOR "mqtt"
#define TOPIC "myran/pannrum/temp1"

// Last millis that we sent an update
unsigned long lastupdate = 0;
unsigned int temperature = 0;

/********************************************************************/
// Data wire is plugged into pin 2 on the Arduino 
#define ONE_WIRE_BUS 2 
/********************************************************************/
// Setup a oneWire instance to communicate with any OneWire devices  
// (not just Maxim/Dallas temperature ICs) 
OneWire oneWire(ONE_WIRE_BUS); 
/********************************************************************/
// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);
/********************************************************************/ 
void setup(void) 
{ 
 Serial.begin(115200); 
 Serial.println("Myran vattentemperatur - startar..."); 

 sensors.begin(); 
 Ciao.begin();
} 
void loop(void) 
{ 
  
  // If we updated 5 seconds ago
  if(((unsigned long)(millis() - lastupdate)) >= 5000){
    
    lastupdate = millis();
     // call sensors.requestTemperatures() to issue a global temperature 
     // request to all devices on the bus 
    /********************************************************************/
     Serial.print(" Requesting temperatures..."); 
     sensors.requestTemperatures(); // Send the command to get temperature readings 
     Serial.println("DONE"); 
    /********************************************************************/
     Serial.print("Temperature is: "); 
     temperature = sensors.getTempCByIndex(0);
     Serial.print(temperature); // Why "byIndex"?  
     
     Ciao.write(CONNECTOR, TOPIC, String(temperature));
       // You can have more than one DS18B20 on the same bus.  
       // 0 refers to the first IC on the wire 
       //delay(1000); 
  }
} 
