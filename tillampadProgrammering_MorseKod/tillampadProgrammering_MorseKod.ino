/*
* Name: TillampadProgrammering_MorseKod
* Author: Alexander Stupak
* Date: 2026-04-20
* Description: Software for an arduino that converts input of morse code into actual text.
*/
// Constant Variables
const int buttonPin = 2;
const int piezoPin = 3;
const int maxLength = 4;
const int morseLength = 26;

const String morseTable[morseLength][maxLength] = {
  {".", "-", "x", "x"},   // A
  {"-", ".", ".", "."},   // B
  {"-", ".", "-", "."},   // C
  {"-", ".", ".", "x"},   // D
  {".", "x", "x", "x"},   // E
  {".", ".", "-", "."},   // F
  {"-", "-", ".", "x"},   // G
  {".", ".", ".", "."},   // H
  {".", ".", "x", "x"},   // I
  {".", "-", "-", "-"},   // J
  {"-", ".", "-", "x"},   // K
  {".", "-", ".", "."},   // L
  {"-", "-", "x", "x"},   // M
  {"-", ".", "x", "x"},   // N
  {"-", "-", "-", "x"},   // O
  {".", "-", "-", "."},   // P
  {"-", "-", ".", "-"},   // Q
  {".", "-", ".", "x"},   // R
  {".", ".", ".", "x"},   // S
  {"-", "x", "x", "x"},   // T
  {".", ".", "-", "x"},   // U
  {".", ".", ".", "-"},   // V
  {".", "-", "-", "x"},   // W
  {"-", ".", ".", "-"},   // X
  {"-", ".", "-", "-"},   // Y
  {"-", "-", ".", "."}    // Z
};
const char alphabet[morseLength] = {
  'A','B','C','D','E','F','G','H','I','J','K','L','M',
  'N','O','P','Q','R','S','T','U','V','W','X','Y','Z'
};
//Dynamic Variables
int myTime;
int prevTime;
int nowTime;
int i;
int morse_count = 0;
int tempTime;
String letters;
String morse_array[maxLength];



void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT);
  pinMode(piezoPin, OUTPUT);
  prevTime = millis() / 1000;
}

void loop() {
  

  //Serial.println(digitalRead(buttonPin));
  while (digitalRead(buttonPin) == 1) {
    //tone(piezoPin, 3000, 1);
    if (prevTime + 1 <= millis() / 1000) {
      //Serial.println(i);
      prevTime = millis() / 1000;
      i += 5;
      tempTime += 1;
    }
    //Serial.println(prevTime);
    //Serial.println(tempTime);
  }
  if(tempTime > 0){

    if (3 <= tempTime  && tempTime < 5) {
      morse_array[morse_count] = "-";
      morse_count += 1;
    }
    if (tempTime < 3) {
      morse_array[morse_count] = ".";
      morse_count += 1;
    }
  }
  if(tempTime = 0){
    morse_array[morse_count] = "x";
      morse_count += 1;
  }
  tempTime = 0;
  for(int i = 0; i < morse_count; i++){
  Serial.print(morse_array[i]);
  }
  Serial.println(" ");
  
   if (morse_count == maxLength){
    i = 0;
    bool found = false;
    //Serial.println(morse_array);
    while(!found){
      if(i+1 >= morseLength){
        break;
      }
      bool same = true;
      for(int j = 0; j < maxLength; j++){
        if(morse_array[j] != morseTable[i][j]){
          same = false;
          break;
        }
      }
      if(same){
       letters = letters + alphabet[i];
       found = true;
       break;
      }
      i++;
    }
    Serial.print(letters);
    delay(3000);
    Serial.println(" ");
    morse_count = 0;
  }
  



}