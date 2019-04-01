/*
 * EVShield interface library
 * Copyright (C) 2015 mindsensors.com
 *
 * This file is part of EVShield interface library.
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

#ifndef EVs_HTColorSensor_H
#define EVs_HTColorSensor_H

#define HTColor_Command     0x41
#define HTColor_Color       0x42

#include "EVShieldI2C.h"

/**
  @brief This class interfaces with HiTechnic ColorSensor attached to EVShield 
  */
class EVs_HTColorSensor : public EVShieldI2C
{
public:
  /** device constructor; custom i2c address is an optional parameter */
  EVs_HTColorSensor(uint8_t i2c_address = 0x02);

  /** issue a byte command to the command register of the device */
  uint8_t issueCommand(char command);

  int initWhiteBalance();
  int initBlackLevel();
  
  /** get the color id from the sensor */
  int getColorId();
};
#endif

