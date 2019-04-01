
// EVs_Display.cpp
//
// This is a class for reading from DIST-Nx, made by Mindsensors.
// See http://www.mindsensors.com/index.php?module=pagemaster&PAGE_user_op=view_page&PAGE_id=73
// See http://www.mindsensors.com/index.php?module=pagemaster&PAGE_user_op=view_page&PAGE_id=72
// See http://www.mindsensors.com/index.php?module=pagemaster&PAGE_user_op=view_page&PAGE_id=69

// Initial version: 2010-06-10 by Andrew Sylvester
// Modified for EVShield: 2015-2-16 by Michael Giles
// Large parts of the code is ported from the NXC library for the device,
// written by Deepak Patil.

/*
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "EVs_Display.h"
#include <Wire.h>

EVs_Display::EVs_Display(uint8_t i2c_address)
: EVShieldI2C(i2c_address)
{
	//byte buf[] = { 0x34, 0x0c, 0x06, 0x35, 0x04, 0x10, 0x42, 0xA8, 0x34, 0x80, 0x02 };
	//writeRegisters(0x00, 11, buf );
}

bool EVs_Display::init(void * shield, SH_BankPort bp) {
	delayMicroseconds(50000);
	EVShieldI2C::init(shield, bp);
	byte buf[] = { 0x34, 0x0c, 0x06, 0x35, 0x04, 0x10, 0x42, 0xA8, 0x34, 0x80, 0x02 };
	bool result = writeRegisters(0x00, 11, buf );
	delayMicroseconds(4500); // wait min 4.1ms
	clear();
	delayMicroseconds(4500); // wait min 4.1ms
	return result;
}

uint8_t EVs_Display::issueCommand(char command) {
	return writeByte(Display_Command, (uint8_t)command);
}

unsigned char EVs_Display::ASCIItoLCD(unsigned char ch){
  unsigned char c;
  if ( ((ch >= 0x20) && (ch <= 0x3F)) || ((ch >= 0x41) && (ch <= 0x5A)) || ((ch >= 0x61) && (ch <= 0x7A)) )
     c = 0x80 + ch;
  else
     c = 0x40; //;
  //Serial.print(" "); Serial.print(c,HEX);
  return c;
}

void EVs_Display::setCursor(int line_num, int x){
  if (line_num==0)
     issueCommand(0x80+x);
  else
     issueCommand(0xC0+x);
}

void EVs_Display::setLine(int line_num) {
	setCursor(line_num,0);
}


void EVs_Display::clear() { // send the clear screen command to the LCD
  setCursor(0,0);
  print("                ");
  setCursor(1,0);
  print("                ");
  setCursor(0,0);
}

bool EVs_Display::print(const char c) {
	bool result = writeByte(Display_Output, ASCIItoLCD(c) );
	delayMicroseconds(4500); // wait min 4.1ms
	return result;
}

void EVs_Display::print(const char c[]) {
	byte len;
  while (*c)
  {
     len = min(strlen(c), LCDI2C_MAX_STRLEN);
     Wire.beginTransmission(_device_address);
     Wire.write(Display_Output);
     while (len--)
        Wire.write(ASCIItoLCD(*c++));
		 // fill remaining space with spaces:
		 for (len=strlen(c); len<LCDI2C_MAX_STRLEN; len++) Wire.write(ASCIItoLCD(' '));
     Wire.endTransmission();
		 //if (error != 0) { Serial.print("Transmission error "); Serial.print(error,HEX); Serial.println(" in EVs_Display::print()"); }
     if (*c)
        delay(LCDI2C_PRINT_STR_DELAY);      // More to send.  Wait a bit
  }
}

void EVs_Display::scan() {
  byte error, address;
  int nDevices;

  Serial.println("Scanning...");

  nDevices = 0;
  for(address = 1; address < 127; address++ )
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address<16)
        Serial.print("0");
      Serial.print(address,HEX);
      Serial.println("  !");

      nDevices++;
    }
    else if (error==4)
    {
      Serial.print("Unknown error at address 0x");
      if (address<16)
        Serial.print("0");
      Serial.println(address,HEX);
    }
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("done\n");

}
