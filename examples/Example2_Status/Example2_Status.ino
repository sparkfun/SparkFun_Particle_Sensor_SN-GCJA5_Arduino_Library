/*
  Reading 1.0 to 10um sized particulate matter from the Panasonic SN-GCJA5
  By: Nathan Seidle
  SparkFun Electronics
  Date: September 8th, 2020
  License: This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).

  This example shows how to read the status of the sensor.

  What is PM and why does it matter?
  https://www.epa.gov/pm-pollution/particulate-matter-pm-basics

  Feel like supporting our work? Buy a board from SparkFun!
  https://www.sparkfun.com/products/17123

  Hardware Connections:
  The SN-GCJA5 requires 5V for power and 3.3V I2C lines. We recommend using a BlackBoard 
  running at 3.3V: https://www.sparkfun.com/products/16282 or a level converter: https://www.sparkfun.com/products/12009
  Connect the red/black wires of the SN-GCJA5 to 5V/GND
  Connect the Yellow wire to SCL (board must be set to 3.3V to avoid damage to sensor)
  Connect the Blue wire to SDA (board must be set to 3.3V to avoid damage to sensor)
  Open the serial monitor at 115200 baud
*/

#include <Wire.h>

#include "SparkFun_Particle_Sensor_SN-GCJA5_Arduino_Library.h" //Click here to get the library: http://librarymanager/All#SparkFun_Particle_SN-GCJA5
SFE_PARTICLE_SENSOR myAirSensor;

void setup()
{
  Serial.begin(115200);
  Serial.println(F("Panasonic SN-GCJA5 Example"));

  Wire.begin();

  if (myAirSensor.begin() == false)
  {
    Serial.println(F("The particle sensor did not respond. Please check wiring. Freezing..."));
    while (1)
      ;
  }

  Serial.println(F("Sensor started"));
}

void loop()
{
  Serial.print(F(" Status: "));

  byte sensorStatus = myAirSensor.getStatusSensors();
  Serial.print(F(" Sensors: "));
  if (sensorStatus == 0)
    Serial.print(F("All sensors good"));
  else if (sensorStatus == 1)
    Serial.print(F("One sensor or fan abnormal"));
  else if (sensorStatus == 2)
    Serial.print(F("Two sensors or fan abnormal"));
  else if (sensorStatus == 3)
    Serial.print(F("Both sensors and fan abnormal"));

  byte statusPD = myAirSensor.getStatusPD();
  Serial.print(F(" Photo diode: "));
  if (statusPD == 0)
    Serial.print(F("Normal"));
  else if (statusPD == 1)
    Serial.print(F("Normal w/ software correction"));
  else if (statusPD == 2)
    Serial.print(F("Abnormal, loss of function"));
  else if (statusPD == 3)
    Serial.print(F("Abnormal, with software correction"));

  byte statusLD = myAirSensor.getStatusLD();
  Serial.print(F(" Laser diode: "));
  if (statusLD == 0)
    Serial.print(F("Normal"));
  else if (statusLD == 1)
    Serial.print(F("Normal w/ software correction"));
  else if (statusLD == 2)
    Serial.print(F("Abnormal, loss of function"));
  else if (statusLD == 3)
    Serial.print(F("Abnormal, with software correction"));

  byte statusFan = myAirSensor.getStatusFan();
  Serial.print(F(" Fan: "));
  if (statusFan == 0)
    Serial.print(F("Normal"));
  else if (statusFan == 1)
    Serial.print(F("Normal w/ software correction"));
  else if (statusFan == 2)
    Serial.print(F("In calibration"));
  else if (statusFan == 3)
    Serial.print(F("Abnormal, out of control"));

  Serial.println();

  delay(1000); //The sensor has new data every second
}