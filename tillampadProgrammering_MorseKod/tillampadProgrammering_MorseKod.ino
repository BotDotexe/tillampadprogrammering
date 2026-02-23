/*
* Name: TillampadProgrammering_MorseKod
* Author: Alexander Stupak
* Date: 2026-02-23
* Description: Software for an arduino that converts input of morse code into actual text.
*/


// Constant Variables
const int Buttonpin = 2;


//Dynamic Variables
int myTime;
int prevTime;
int nowTime;
void setup() {
  Serial.begin(9600);
  pinMode(OUTPUT,Buttonpin);
  prevTime = millis()/1000;
}

void loop() {
  //Serial.println(digitalRead(Buttonpin)); 
  while(digitalRead(Buttonpin) == 1){
    if(prevTime + 1 <= millis()/1000) { 
      Serial.println(millis()/1000);
      prevTime = millis()/1000;
    }
  }
  


}

