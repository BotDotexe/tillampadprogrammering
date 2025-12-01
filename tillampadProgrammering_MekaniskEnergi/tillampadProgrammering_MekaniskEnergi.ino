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



Adafruit_BMP280 bmp; // I2C

//constant variables:
const int button_pin= 8;
const int ArraySize = 10;
int filterArray[ArraySize];

//temp variables/dynamic variables:
float start_height;
float current_height;
float heightPos;
int index = 0;
int i = 0;


//setup
void setup() {
  Serial.begin(9600);
  pinMode(OUTPUT, button_pin);
  while ( !Serial ) delay(100);   // wait for native usb
  Serial.println(F("BMP280 test"));
  unsigned status;
  status = bmp.begin(BMP280_ADDRESS_ALT, BMP280_CHIPID);
  }


 
void loop() {
  current_height = bmp.readAltitude(1013.25);
  if(digitalRead(button_pin) == LOW)
   { start_height = bmp.readAltitude(1013.25);
  }
  heightPos = (current_height - start_height)* 100;
  
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
    Serial.print(heightPos);
    Serial.println(" cm");
    filter(heightPos);
    delay(1000);
}



// filter function
// utilizes arrays to give a rounded value that has been read. ||
// Parameters: nothing ||
// Output: float ||
void filter(float input) {
  for(int i = 0; i < ArraySize; i++){
  filterArray[index] = input;
  index = (index + 1) % 10;
  }
  float sum = 0.0;
  float avg = 0.0;

  for (int i = 0; i < 10; i++) {
    sum += filterArray[i];
  }
  avg = sum / 10.0;
  avg = avg + 0;
  Serial.println(avg);
  delay(50);


}





