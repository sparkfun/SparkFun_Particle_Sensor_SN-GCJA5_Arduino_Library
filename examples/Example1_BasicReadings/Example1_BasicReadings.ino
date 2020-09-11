/*
  Reading 1.0 to 10um sized particulate matter from the Panasonic SN-GCJA5
  By: Nathan Seidle
  SparkFun Electronics
  Date: September 8th, 2020
  License: This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).

  What is PM and why does it matter?
  https://www.epa.gov/pm-pollution/particulate-matter-pm-basics

  Feel like supporting our work? Buy a board from SparkFun!
  https://www.sparkfun.com/products/17123

  Hardware Connections:
  Attach a Qwiic Cable to your SparkFun RedBoard/BlackBoard/ESP32 Thing Plus or other
  Plug the sensor onto the shield
  Serial.print it out at 115200 baud to serial monitor.
*/

#include <Wire.h>

#include "SparkFun_Particle.h" //Click here to get the library: http://librarymanager/All#SparkFun_Particle_SN-GCJA5
SFE_PARTICLE_SENSOR myAirSensor;

void setup()
{
  Serial.begin(115200);
  Serial.println(F("Panasonic SN-GCJA5 Example"));

  pinMode(A4, INPUT_PULLUP);
  pinMode(A5, INPUT_PULLUP);

  Wire.begin();
  
  //Wire.setClock(400000);

//  if(myAirSensor.begin(Wire1) == false)
  if(myAirSensor.begin() == false)
  {
    Serial.println(F("The particle sensor did not respond. Please check wiring. Freezing..."));
    while(1);    
  }

//  while(1)
//  {
//    readSensor(0);
//    delay(1000);
//  }

  Serial.println(F("Sensor started"));
}

void loop()
{
  float pm1_0 = myAirSensor.getPM1_0();
  Serial.print(F("Particulate Matter 1.0 microns in size: "));
  Serial.print(pm1_0, 2); //Print float with 2 decimals

  float pm2_5 = myAirSensor.getPM2_5();
  Serial.print(F(" PM2.5: "));
  Serial.print(pm2_5, 2);

  float pm10 = myAirSensor.getPM10();
  Serial.print(F(" PM10: "));
  Serial.print(pm10, 2);

  unsigned int pc0_5 = myAirSensor.getPC0_5();
  Serial.print(F(" Particle count 0.3 to 0.5um in size: "));
  Serial.print(pc0_5);

  unsigned int pc1_0 = myAirSensor.getPC1_0();
  Serial.print(F(" 0.5-1.0um: "));
  Serial.print(pc1_0);

  unsigned int pc2_5 = myAirSensor.getPC2_5();
  Serial.print(F(" 1.0-2.5um: "));
  Serial.print(pc2_5);

  unsigned int pc5_0 = myAirSensor.getPC5_0();
  Serial.print(F(" 2.5-5.0um: "));
  Serial.print(pc5_0);

  unsigned int pc7_5 = myAirSensor.getPC7_5();
  Serial.print(F(" 5.0-7.5um: "));
  Serial.print(pc7_5);

  unsigned int pc10 = myAirSensor.getPC10();
  Serial.print(F(" 7.5-10um: "));
  Serial.print(pc10);

  Serial.print(F(" Status: "));

  byte sensorStatus = myAirSensor.getStatusSensors();
  Serial.print(F(" Sensor: "));
  Serial.print(sensorStatus);

  byte statusPD = myAirSensor.getStatusPD();
  Serial.print(F(" Photo diode: "));
  Serial.print(statusPD);

  byte statusLD = myAirSensor.getStatusLD();
  Serial.print(F(" Laser diode: "));
  Serial.print(statusLD);

  byte statusFan = myAirSensor.getStatusFan();
  Serial.print(F(" Fan: "));
  Serial.print(statusFan);

  Serial.println();

  delay(1000); //The sensor has new data every second
}

byte sensorData[50];

uint32_t readSensor(uint8_t addr)
{
  Wire.beginTransmission(0x33);
  Wire.write(addr);
  if (Wire.endTransmission(false) != 0)
    return (0); //Sensor did not ACK

  Wire.requestFrom((uint8_t)0x33, (uint8_t)20);
  if (Wire.available())
  {
    for(int x = 0 ; x < 20 ; x++)
    {
      sensorData[x] = Wire.read();
    }
  }

  Serial.println("Sensor data: ");
  for(int x = 0 ; x < 20 ; x++)
  {
    if(x % 8 == 0) Serial.println();
    Serial.print(" 0x");
    if(sensorData[x] < 0x10) Serial.print("0");
    Serial.print(sensorData[x], HEX);
  }
  
  return (0);
}
