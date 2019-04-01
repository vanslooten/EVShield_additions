/**
 * Basic class to use the HiTechnic Color sensor with an EvShield.
 * 
 * Technical info use from these sources:
 * https://github.com/botbench/rdpartyrobotcdr/blob/master/drivers/hitechnic-colour-v2.h
 * https://sourceforge.net/p/lejos/ev3/code/ci/master/tree/ev3classes/src/lejos/hardware/sensor/HiTechnicColorSensor.java
 * https://github.com/cmorty/lejos/blob/master/classes/src_shared/lejos/nxt/addon/ColorHTSensor.java
*/

#include "EVs_HTColorSensor.h"

EVs_HTColorSensor::EVs_HTColorSensor(uint8_t i2c_address)
: EVShieldI2C(i2c_address)
{
}
uint8_t EVs_HTColorSensor::issueCommand(char command)
{
  return writeByte(HTColor_Command, (uint8_t)command);
}

/**
 * Puts the sensor into white balance calibration mode. For best results
 * the sensor should be pointed at a diffuse white surface at a distance
 * of approximately 15mm before calling this method. After a fraction of
 * a second the sensor lights will flash and the calibration is done. When
 * calibrated, the sensor keeps this information in non-volatile memory.
 *
 * @return 0 if it went well and -1 otherwise
 */
int EVs_HTColorSensor::initWhiteBalance() {
  return issueCommand(0x43);
}

/**
 * Puts the sensor into black/ambient level calibration mode. For best
 * results the sensor should be pointed in a direction with no obstacles
 * for 50cm or so. This reading the sensor will use as a base level for
 * other readings. After a fraction of a second the sensor lights will
 * flash and the calibration is done. When calibrated, the sensor keeps
 * this information in non-volatile memory.
 *
 * @return 0 if it went well and -1 otherwise.
 */
int EVs_HTColorSensor::initBlackLevel() {
  return issueCommand(0x42);
}

/**
 * Read the color index number from the sensor.
 */
int EVs_HTColorSensor::getColorId()
{
  return readByte(HTColor_Color); // 0xFF 0x3F
}


