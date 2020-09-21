/*
  This is a library written for the Panasonic SN-GCJA5 particle sensor
  SparkFun sells these at its website: www.sparkfun.com
  Do you like this library? Help support open source hardware. Buy a board!
  https://www.sparkfun.com/products/17123

  Written by Nathan Seidle @ SparkFun Electronics, September 8th, 2020
  This library handles reads the Particle Matter and Particle Count.
  https://github.com/sparkfun/SparkFun_Particle_Sensor_SN-GCJA5

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include "SparkFun_Particle_Sensor_SN-GCJA5_Arduino_Library.h"

//Test to see if the device is connected
bool SFE_PARTICLE_SENSOR::begin(TwoWire &wirePort)
{
  _i2cPort = &wirePort; //Grab which port the user wants us to use

  return (isConnected()); //Check to see if device acks to its address.
}

//Given a mass density PM register, do conversion and return mass density
float SFE_PARTICLE_SENSOR::getPM(uint8_t pmRegister)
{
  uint32_t count = readRegister32(pmRegister);
  return (count / 1000.0);
}
float SFE_PARTICLE_SENSOR::getPM1_0()
{
  return (getPM(SNGCJA5_PM1_0));
}
float SFE_PARTICLE_SENSOR::getPM2_5()
{
  return (getPM(SNGCJA5_PM2_5));
}
float SFE_PARTICLE_SENSOR::getPM10()
{
  return (getPM(SNGCJA5_PM10));
}

//Particle count functions
uint16_t SFE_PARTICLE_SENSOR::getPC0_5()
{
  return (readRegister16(SNGCJA5_PCOUNT_0_5));
}
uint16_t SFE_PARTICLE_SENSOR::getPC1_0()
{
  return (readRegister16(SNGCJA5_PCOUNT_1_0));
}
uint16_t SFE_PARTICLE_SENSOR::getPC2_5()
{
  return (readRegister16(SNGCJA5_PCOUNT_2_5));
}
uint16_t SFE_PARTICLE_SENSOR::getPC5_0()
{
  return (readRegister16(SNGCJA5_PCOUNT_5_0));
}
uint16_t SFE_PARTICLE_SENSOR::getPC7_5()
{
  return (readRegister16(SNGCJA5_PCOUNT_7_5));
}
uint16_t SFE_PARTICLE_SENSOR::getPC10()
{
  return (readRegister16(SNGCJA5_PCOUNT_10));
}

//State functions
uint8_t SFE_PARTICLE_SENSOR::getState()
{
  return (readRegister8(SNGCJA5_STATE));
}
uint8_t SFE_PARTICLE_SENSOR::getStatusSensors()
{
  return ((getState() >> 6) & 0b11);
}
uint8_t SFE_PARTICLE_SENSOR::getStatusPD()
{
  return ((getState() >> 4) & 0b11);
}
uint8_t SFE_PARTICLE_SENSOR::getStatusLD()
{
  return ((getState() >> 2) & 0b11);
}
uint8_t SFE_PARTICLE_SENSOR::getStatusFan()
{
  return ((getState() >> 0) & 0b11);
}

//Low level I2C functions
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

//Returns true if device acknowledges its address
bool SFE_PARTICLE_SENSOR::isConnected()
{
  _i2cPort->beginTransmission(_deviceAddress);
  if (_i2cPort->endTransmission() != 0)
    return (false); //Sensor did not ACK
  return (true);    //All good
}

//Reads from a given location
//Stores the result at the provided outputPointer
uint8_t SFE_PARTICLE_SENSOR::readRegister8(uint8_t addr)
{
  _i2cPort->beginTransmission(_deviceAddress);
  _i2cPort->write(addr);
  if (_i2cPort->endTransmission(false) != 0)
    return (0); //Sensor did not ACK

  _i2cPort->requestFrom((uint8_t)_deviceAddress, (uint8_t)1);
  if (_i2cPort->available())
    return (_i2cPort->read());

  return (0); //Sensor did not respond
}

//Reads two consecutive bytes from a given location
uint16_t SFE_PARTICLE_SENSOR::readRegister16(uint8_t addr)
{
  _i2cPort->beginTransmission(_deviceAddress);
  _i2cPort->write(addr);
  if (_i2cPort->endTransmission(false) != 0)
    return (0); //Sensor did not ACK

  _i2cPort->requestFrom((uint8_t)_deviceAddress, (uint8_t)2);
  if (_i2cPort->available())
  {
    uint8_t lsb = _i2cPort->read();
    uint8_t msb = _i2cPort->read();
    return ((uint16_t)msb << 8 | lsb);
  }
  return (0); //Sensor did not respond
}

//Reads four consecutive bytes from a given location
uint32_t SFE_PARTICLE_SENSOR::readRegister32(uint8_t addr)
{
  _i2cPort->beginTransmission(_deviceAddress);
  _i2cPort->write(addr);
  if (_i2cPort->endTransmission(false) != 0)
    return (0); //Sensor did not ACK

  _i2cPort->requestFrom((uint8_t)_deviceAddress, (uint8_t)4);
  if (_i2cPort->available())
  {
    uint8_t ll = _i2cPort->read();
    uint8_t lh = _i2cPort->read();
    uint8_t hl = _i2cPort->read();
    uint8_t hh = _i2cPort->read();
    return (((uint32_t)hh << 24) | ((uint32_t)hl << 16) | ((uint32_t)lh << 8) | ((uint32_t)ll << 0));
  }
  return (0); //Sensor did not respond
}
