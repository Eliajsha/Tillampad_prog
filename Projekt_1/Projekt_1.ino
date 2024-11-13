/*
* Name: clock and temp project
* Author: Elias Svensson
* Date: 2024-11-12
* Description: This project uses a ds3231 to measure time and displays the time to an 1306 oled display,
* Further, it measures temprature with a analog temprature module and displays a mapped value to a 9g-servo-motor
*/

// Include Libraries
#include <RTClib.h>
#include <Wire.h>
#include "U8glib.h"
#include <Servo.h>

// Init constants
int cord1 = 5;
int cord2 = 33;
int cord3 = 45;
const int deg = 100;
const int ledpin1 = 9;
const int ledpin2 = 10;
const int ledpin3 = 11;
const int ledpin4 = 12;

// Init global variables

// construct objects
RTC_DS3231 rtc;
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NO_ACK);	
Servo myservo;


void setup() {
  // init communication
  Serial.begin(9600);
  
  // Init Hardware
  Wire.begin();
  rtc.begin();
  rtc.adjust(DateTime(F(__DATE__),F(__TIME__)));

  u8g.setFont(u8g_font_unifont);

  pinMode(A1, INPUT);
  pinMode(ledpin1, OUTPUT);
  pinMode(ledpin2, OUTPUT);
  pinMode(ledpin3, OUTPUT);
  pinMode(ledpin4, OUTPUT);
  myservo.attach(7);

}

void loop() {
  oledWrite(getTime(), getTemp());
  Serial.println(getTemp());
  servoWrite(getTemp());
  blinkblonk();
}


/*
*This function reads time from an ds3231 module and package the time as a String
*Paramteters: Void
*Returns: time in hh:mm:ss as String
*/
String getTime(){
  DateTime now = rtc.now();
  return "Time: " + String(now.hour()) + ":" + String(now.minute()) + ":" + String(now.second());
}

/*
* This function reads an analog pin connected to an analog temprature sensor and calculates the corresponding temp
*Parameters: Void
*Returns: temprature as float
*/
float getTemp() {
  int Vo;
  float R1 = 10000;
  float logR2;
  float R2;
  float T;
  float c1 = 0.001129148, c2 = 0.000234125, c3 = 0.0000000876741;
  
  Vo = analogRead(A1);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2 * logR2 + c3 * logR2 * logR2 * logR2)); // temperature in Kelvin
  T = T - 273.15;

  return T;
}

/*
* This function takes a string and draws it to an oled display
*Parameters: - text: String to write to display
*Returns: void
*/
void oledWrite(String text, int temp){
 String temp_str = String(temp);
 String final_temp= "Temp: " + temp_str;
 u8g.firstPage();  
  do {
   u8g.drawStr(cord1, cord2, text.c_str());
   u8g.drawStr(cord1, cord3,  final_temp.c_str()); 
   } while( u8g.nextPage() );
}

/*
* takes a temprature value and maps it to corresppnding degree on a servo
*Parameters: - value: temprature
*Returns: void
*/
void servoWrite(float value){
  myservo.write(map(getTemp(), 20, 30, 0, 180));
}

/*
* This function flashes lights when the temperature is too high
*Parameters: void
*Returns: void
*/
void blinkblonk() {
  if (getTemp() > 27) {
    digitalWrite(ledpin1, HIGH);
    digitalWrite(ledpin3, HIGH);
      delay(deg);
    digitalWrite(ledpin1, LOW);
    digitalWrite(ledpin3, LOW); 
    digitalWrite(ledpin2, HIGH);
    digitalWrite(ledpin4, HIGH);
      delay(deg);
    digitalWrite(ledpin2, LOW);
    digitalWrite(ledpin4, LOW);
  }
}
