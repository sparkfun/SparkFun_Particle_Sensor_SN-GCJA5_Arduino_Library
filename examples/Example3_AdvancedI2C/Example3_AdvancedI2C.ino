/*
  Reading 1.0 to 10um sized particulate matter from the Panasonic SN-GCJA5
  By: Nathan Seidle
  SparkFun Electronics
  Date: September 8th, 2020
  License: This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).

  This example shows how to use a different Wire port and faster I2C clock.

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

  Wire1.begin();          //This line will fail on an Uno. Use a platform that has multiple Wire ports.
  Wire1.setClock(400000); //The SN-GCJA5 support 400kHz I2C

  if (myAirSensor.begin(Wire1) == false) //Pass the Wire1 port into the library
  {
    Serial.println("The particle sensor did not respond. Please check wiring. Freezing...");
    while (1)
      ;
  }

  Serial.println("Sensor started");
  Serial.println("PM:1.0, 2.5, 10, Counts: 0.5, 1, 2.5, 5, 7.5, 10,");
}

void loop()
{
  float pm1_0 = myAirSensor.getPM1_0();
  Serial.print(pm1_0, 2); //Print float with 2 decimals
  Serial.print(",");

  float pm2_5 = myAirSensor.getPM2_5();
  Serial.print(pm2_5, 2);
  Serial.print(",");

  float pm10 = myAirSensor.getPM10();
  Serial.print(pm10, 2);
  Serial.print(",");

  unsigned int pc0_5 = myAirSensor.getPC0_5();
  Serial.print(pc0_5);
  Serial.print(",");

  unsigned int pc1_0 = myAirSensor.getPC1_0();
  Serial.print(pc1_0);
  Serial.print(",");

  unsigned int pc2_5 = myAirSensor.getPC2_5();
  Serial.print(pc2_5);
  Serial.print(",");

  unsigned int pc5_0 = myAirSensor.getPC5_0();
  Serial.print(pc5_0);
  Serial.print(",");

  unsigned int pc7_5 = myAirSensor.getPC7_5();
  Serial.print(pc7_5);
  Serial.print(",");

  unsigned int pc10 = myAirSensor.getPC10();
  Serial.print(pc10);
  Serial.print(",");

  Serial.println();

  delay(1000); //The sensor has new data every second
}