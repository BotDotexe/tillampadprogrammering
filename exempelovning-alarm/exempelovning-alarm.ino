
/*
* Name: övningsprojekt
* Author: Alexander Stupak
* Date: 2025-11-10
* Description: This project uses a ds3231 to measure time and displays the time to an 1306 oled display, 
* Further, a potentiometer is utilized to get a countdown time, similar to a kitchen-alarmclock
* aswell as displaying the time left until the alarm goes of.
*/

// Include Libraries
#include <RTClib.h>
#include <Wire.h>
#include <U8glib.h>
#include <Servo.h>
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NO_ACK);

// constant digital pins
const int pot_pin = A0;
const int servo_pin = 11;
// Init global variables

// Construct objects

RTC_DS3231 rtc;
Servo servo;



void setup() {
  pinMode(pot_pin, OUTPUT);
  servo.attach(servo_pin);
  // init communication

  Serial.begin(9600);
  Wire.begin();

  // Init Hardware
  rtc.begin();

  // Settings
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}
int timeLeft = 0;
void loop() {
  if (timeLeft == 0){
    timeLeft = potVal(analogRead(pot_pin));
    
    for(int i = 0; 0 < timeLeft; timeLeft--){
       oledWrite(String(timeLeft));
       i--;
       delay(1000);
      
    }
  }
  oledWrite(getTime());   //remove comment when the function is written
  servoWrite(getTemp());  //remove comment when the function is written
  getTime();
  Serial.println(potVal(analogRead(pot_pin)));
  delay(200);
  
}


/*
*This function reads time from an ds3231 module and package the time as a String
*Parameters: Void
*Returns: time in hh:mm:ss as String
*/
String getTime() {
  DateTime now = rtc.now();
  return String(now.hour()) + ":" + String(now.minute()) + ":" + String(now.second());
}

/*
* This function takes temprature from ds3231 and returns as a float
*Parameters: Void
*Returns: temprature as float
*/
float getTemp() {
  return rtc.getTemperature();
}

/*
* This function takes a string and draws it to an oled display
*Parameters: - text: String to write to display
*Returns: void
*/
void oledWrite(String text) {
  u8g.setFont(u8g_font_helvB10);
  u8g.firstPage();
  do {
    u8g.drawStr(0, 20, (text).c_str());
  } while (u8g.nextPage());
}


/*
* takes a temprature value and maps it to corresppnding degree on a servo
*Parameters: - value: temprature
*Returns: void
*/
void servoWrite(float value) {
  
  servo.write(map(value, 20, 30, 0, 180));
}
/*
* takes a value from a potentiometer and maps it to a corresponding number of minutes
* Parameter: - value: analogRead(pin)
* Returns: integer
*/
int potVal(int value) {
  return map(value, 0, 1023, 1, 60);
}

