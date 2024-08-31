/**
 * TCA9548 I2CScanner.ino -- I2C bus scanner for Arduino
 *
 * Based on https://playground.arduino.cc/Main/I2cScanner/
 *
 */

#include "Wire.h"

#include "Adafruit_SGP40.h"
#include "Adafruit_SHT31.h"

Adafruit_SGP40 sgpInternal;
Adafruit_SHT31 sht31Internal;

Adafruit_SGP40 sgpExternal;
Adafruit_SHT31 sht31External;

#define TCAADDR 0x70

void tcaselect(uint8_t i) {
  if (i > 7) return;
 
  Wire.beginTransmission(TCAADDR);
  Wire.write(1 << i);
  Wire.endTransmission();  
}


// standard Arduino setup()
void setup()
{
    while (!Serial);
    delay(1000);

    Wire.begin();
    
    Serial.begin(9600);
    Serial.println("\nTCAScanner ready!");
    
    for (uint8_t t=0; t<=2; t++) {
      tcaselect(t);

      if(t == 0){
        
      }else if(t == 1){
        if (! sgpInternal.begin()){
          Serial.println("Internal SGP40 sensor not found :(");
          while (1);
        }

        if (! sht31Internal.begin(0x44)) {   // Set to 0x45 for alternate i2c addr
          Serial.println("Couldn't find Internal SHT31");
        }
      }else if(t == 2){
        if (! sgpExternal.begin()){
          Serial.println("External SGP40 sensor not found :(");
        }

        if (! sht31External.begin(0x44)) {   // Set to 0x45 for alternate i2c addr
          Serial.println("Couldn't find External SHT31");
          while (1);
        }
      }
    }

    Serial.print("Found SHT3x + SGP40 serial #");
    Serial.print(sgpInternal.serialnumber[0], HEX);
    Serial.print(sgpInternal.serialnumber[1], HEX);
    Serial.println(sgpInternal.serialnumber[2], HEX);

    Serial.print("Found SHT3x + SGP40 serial #");
    Serial.print(sgpExternal.serialnumber[0], HEX);
    Serial.print(sgpExternal.serialnumber[1], HEX);
    Serial.println(sgpExternal.serialnumber[2], HEX);

    Serial.println("\ndone");
}
void loop() 
{
}
