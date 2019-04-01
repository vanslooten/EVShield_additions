
// EVs_Display.h
//
// This is a class interface for an i2c LCD display, made by Fjodor van Slooten.

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


#ifndef EVs_Display_H
#define EVs_Display_H

#define Display_Command      0x00
#define Display_Output       0x40
#define LCDI2C_MAX_STRLEN       16
#define LCDI2C_PRINT_STR_DELAY  20

#include "EVShieldI2C.h"

/**
  @brief This class interfaces with i2c display attached to EVShield
	*/
class EVs_Display : public EVShieldI2C
{
public:
	/** device constructor for Display; custom i2c address is an optional parameter */
  EVs_Display(uint8_t i2c_address = 0x76);

  bool init(void * shield, SH_BankPort bp);

  /** issue a byte command to the command register of the device */
  uint8_t issueCommand(char command);

  unsigned char ASCIItoLCD(unsigned char ch);

  void setLine(int line_num);
  void setCursor(int line_num, int x);
  void clear();

  bool print(const char c);
  void print(const char c[]);

  void scan();
};

#endif
