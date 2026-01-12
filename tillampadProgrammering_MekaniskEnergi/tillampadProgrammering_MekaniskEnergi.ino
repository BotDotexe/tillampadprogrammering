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
#include <SPI.h>
#include <Adafruit_BMP280.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

//Class objects:
Adafruit_BMP280 bmp; 
Adafruit_MPU6050 mpu;

//constant variables:
const int button_pin= 8;
const int ArrayLength = 10;
int filterArray[ArrayLength] = { 0 };
int currentIndex = 0;
const float weight = 0.1; //Weight in kg
const float gravconst = 9.82; //the gravitational constant approx. 9.82 
//temp variables/dynamic variables:
float start_height;
float current_height;
int potentialenergy;
float heightPos;
int index = 0;
int i = 0;


//setup
void setup() {
  mpu.begin();
  Serial.begin(9600);
  pinMode(OUTPUT, button_pin);
  while ( !Serial ) delay(100);   // wait for native usb
  Serial.println(F("BMP280 test"));
  unsigned status;
  status = bmp.begin(BMP280_ADDRESS_ALT, BMP280_CHIPID);
  mpu.setAccelerometerRange(MPU6050_RANGE_16_G);
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  }


 
void loop() {
  current_height = bmp.readAltitude(1013.25);
  if(digitalRead(button_pin) == LOW)
   { start_height = bmp.readAltitude(1013.25);
  }


  heightPos = (current_height - start_height) * 100;
  

    /*
    Serial.print(F("Temperature = "));
    Serial.print(bmp.readTemperature());
    Serial.println(" *C");

    Serial.print(F("Pressure = "));
    Serial.print(bmp.readPressure());
    Serial.println(" Pa");

    Serial.print(F("Approx altitude = "));
    Serial.print(bmp.readAltitude(1013.25)); 
    Serial.println(" m");

    Serial.println();
    delay(2000);
    
    */
    
    Serial.print("Height:");
    Serial.print(filter(heightPos));
    Serial.print("cm");
    filter(heightPos);

    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    delay(1000);
    Serial.print(" AccelX:");
    Serial.print(a.acceleration.x);
    Serial.print(",");
    Serial.print("AccelY:");
    Serial.print(a.acceleration.y);
    Serial.print(",");
    Serial.print("AccelZ:");
    Serial.print(a.acceleration.z);
    Serial.println(" ");
}



// filter function
// utilizes arrays to give a rounded value that has been read. ||
// Parameters: nothing ||
// Output: float ||
float filter(float input) {
  filterArray[currentIndex] = input;
  
   // Move to the next index in a circular manner
  currentIndex = (currentIndex + 1) % ArrayLength;
  
  int sum = 0;
  
  for (int i = 0; i < ArrayLength; i++) {
    sum = sum + filterArray[i];
  }
  return sum / ArrayLength;
}
// Potential energy fuction
// Takes the height difference and uses it to give a rough value over the potential energy ||
// Parameters: float || 
// Output: integer ||
int potentialEnergy(float input) {
   return potentialenergy = weight * input * gravconst;
}




