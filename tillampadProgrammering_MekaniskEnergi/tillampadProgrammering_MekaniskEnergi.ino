/*
* Name: TillampadProgrammering_MekaniskEnergi
* Author: Alexander Stupak
* Date: 2025-11-24
* Description: T

  This example shows how to connect two sensors on the same I2C bus.

  The BME280 has two I2C addresses: 0x77 (jumper open) or 0x76 (jumper closed)

  Hardware connections:
  BME280 -> Arduino
  GND -> GND
  3.3 -> 3.3
  SDA -> A4
  SCL -> A5
*/
//Libraries:
#include <Wire.h>

#include "SparkFunBME280.h"
//Objects:

BME280 mySensorA; //Uses default I2C address 0x77
BME280 mySensorB; //Uses I2C address 0x76 (jumper closed)

//Public constants:
int MpPa=12;
float StartPressure = mySensorA.readFloatPressure();
float Height;
void setup()
{
  Serial.begin(115200);
  Serial.println("Example showing alternate I2C addresses");

  Wire.begin();

  mySensorA.setI2CAddress(0x77); //The default for the SparkFun Environmental Combo board is 0x77 (jumper open).
  //If you close the jumper it is 0x76
  //The I2C address must be set before .begin() otherwise the cal values will fail to load.

  if(mySensorA.beginI2C() == false) Serial.println("Sensor A connect failed");

  mySensorB.setI2CAddress(0x76); //Connect to a second sensor
  if(mySensorB.beginI2C() == false) Serial.println("Sensor B connect failed");
}

void loop()
{
  Height = mySensorA.readFloatPressure() - StartPressure;
  Serial.println(Height/MpPa);

  Serial.print(" PressureA: ");
  Serial.print(mySensorA.readFloatPressure(), 0);

  Serial.print(" TempA: ");
  Serial.print(mySensorA.readTempC(), 2);
 /*
  Serial.print(" HumidityB: ");
  Serial.print(mySensorB.readFloatHumidity(), 0);
  
  Serial.print(" PressureB: ");
  Serial.print(mySensorB.readFloatPressure(), 0);
  
  Serial.print(" TempB: ");
  Serial.print(mySensorB.readTempC(), 2);

  Serial.println();
*/
  delay(50);
}

