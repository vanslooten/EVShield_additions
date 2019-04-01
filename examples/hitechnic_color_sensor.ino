/*
 Test sketch for the HiTechnic Colorsensor.
 http://www.hitechnic.com/cgi-bin/commerce.cgi?preadd=action&key=nco1038
 
 Setup for this example:
  - connect HiTechnic Colorsensor to port BAS1

  This sketch requires added class EVs_HTColorSensor, in version as distributed in zip-file AppDev, or from here:
  http://home.et.utwente.nl/slootenvanf/div/arduino/EVs_HTColorSensor.zip
  (extract the two files into the EVShield library folder, eg. Documents\Arduino\libraries\EVShield)
  
  (if you get errors, check if files "EVs_HTColorSensor.cpp" and "EVs_HTColorSensor.h" exist in
  Documents\Arduino\libraries\EVShield or in the sketch folder)
*/

#include <Wire.h>
#include <EVShield.h>
#include "EVs_HTColorSensor.h"

EVShield evshield(0x34,0x36);

EVs_HTColorSensor colorSensor(0x02);

void setup() {
    Serial.begin(115200);       // start serial port output, check for same speed at Serial Monitor!
    delay(2000);                // wait two seconds, allowing time to activate the serial monitor

    evshield.init( SH_HardwareI2C );

    colorSensor.init( &evshield, SH_BAS1 );

    Serial.println("Starting...");
    // to calibrate the WhiteBalance of the sensor, uncomment the next line (read the comments of this method in EVs_HTColorSensor.cpp!):
    //Serial.print("init="); Serial.println(colorSensor.initWhiteBalance());
    // to calibrate the BlackLevel of the sensor, uncomment the next line (read the comments of this method in EVs_HTColorSensor.cpp!):
    //Serial.print("init="); Serial.println(colorSensor.initBlackLevel());
}

void loop() {
  Serial.println(colorSensor.getColorId());
  delay(1000);
}

