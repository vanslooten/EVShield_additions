#include <Wire.h>
#include <EVShield.h>
#include "EVs_Display.h"

/* Setup for this example:
  - connect LEGO display to port BAS1

  This sketch requires added class EVs_Display, in version as distributed in zip-file AppDev.
  (if you get errors, check if files "EVs_Display.cpp" and "EVs_Display.h" exist in Documents\Arduino\libraries\EVShield)
*/

EVShield evshield(0x34,0x36);

EVs_Display lcd;

void setup() {
    Serial.begin(115200);       // start serial port output, check for same speed at Serial Monitor!
    delay(2000);                // wait two seconds, allowing time to activate the serial monitor

    evshield.init( SH_HardwareI2C );

    lcd.init( &evshield, SH_BAS1 );

    Serial.println("Starting...");

    evshield.ledSetRGB( 0, 255, 0); // led green

    lcd.setLine(0);
    lcd.print("Cola");
    lcd.setCursor(0,11);
    lcd.print(" 0.99");
    lcd.setLine(1);
    lcd.print("Press Go");
    evshield.waitForButtonPress(BTN_GO);
    lcd.setLine(1);
    lcd.print("Cola bought!");
}

void loop() {
}

