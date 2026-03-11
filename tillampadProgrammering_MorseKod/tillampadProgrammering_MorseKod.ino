/*
* Name: TillampadProgrammering_MorseKod
* Author: Alexander Stupak
* Date: 2026-02-23
* Description: Software for an arduino that converts input of morse code into actual text.
*/


// Constant Variables
const int buttonPin = 2;
const int piezoPin = 3;

//Dynamic Variables
int myTime;
int prevTime;
int nowTime;
int i;
void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT);
  pinMode(piezoPin, OUTPUT);
  prevTime = millis()/1000;
}

void loop() {
  //Serial.println(digitalRead(Buttonpin)); 
  while(digitalRead(buttonPin) == 1){
    tone(piezoPin, 3000, 1);
    if(prevTime + 1 <= millis()/1000) { 
      Serial.println(i);
      prevTime = millis()/1000;
      i += 5;
    }
  }

  


}

