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
const float baudtime = 1/9600;
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
int DynamicNRG;
int index = 0;
int i = 0;
int TotEnergy;



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


//The main loop||
void loop() {
  current_height = bmp.readAltitude(1013.25);
  if(digitalRead(button_pin) == LOW)
   { start_height = bmp.readAltitude(1013.25);
  }


  heightPos = (current_height - start_height) * 100;
  


    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    delay(1000);

    DynamicNRG = dynamicEnergy(filter(a.acceleration.x));
    potentialenergy = potentialEnergy(heightPos);
    TotEnergy = DynamicNRG + potentialEnergy(heightPos);


    Serial.print(DynamicNRG);
    Serial.print(" ");
    Serial.println("F ");
    Serial.print("Total Energy = ");
    Serial.println(TotEnergy);
    Serial.print("|Dynamic Energy: ");
    Serial.print(DynamicNRG);
    Serial.print(" F + ");
    Serial.print("Potential Energy: ");
    Serial.print(potentialenergy);
    Serial.println(" F |");
    Serial.println("_________________________________________________________________________________________");
}



// Filter function ||
// utilizes arrays to give an average value based from the input values ||
// Parameters: Input - a float ||
// Output: Integer - Returns an average value as integer||
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

// Potential energy fuction ||
// Takes the height difference and uses it to give a rough value over the potential energy ||
// Parameters: input - height above zero level as float ||
// Output: potential energy returned as an integer ||
int potentialEnergy(float input) {
   return potentialenergy = weight * input * gravconst;
}

// Dynamic energy function ||
// Uses the formula for dynamic energy and velocity as input to calculate the dynmaic energy of our components ||
// Parameter: Input - The velocity in one axis as a float ||
// Output: Dynamic energy as an integer ||
int dynamicEnergy(float input){
  return (weight * input * input)/2; 
}



