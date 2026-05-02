#include "SevSeg.h"
#define IRSbPin A1 //is time
#define setEHEH A2 //set alrarm
#include <CronAlarms.h>
#include <TimeLib.h>

SevSeg sevseg; 
//Segment Pins below
int aPin = 2;
int bPin = 3;
int cPin = 4;
int dPin = 5;
int dpPin = 6;
int ePin = 11;
int fPin = 12;
int gPin = 13;
//digit pins below
int d1Pin = 7;
int d2Pin = 8;
int d3Pin = 9;
int d4Pin = 10;

int buzzerPin = A0;
int highC = 0;
int lowC = 0;

bool settingAlarm = false;
bool alarmArmed = false;
unsigned long currentTime = 360000; //og 360000
unsigned long alarmTime = -1;


int clockMode = 0; // 0 = normal clock 1 = setting clock


int alarmEH = 432;
 
int buttonState = 0;

int hours;
int minutes;



time_t t = now();
setTime(t);



void blare(unsigned EHEH = 432, unsigned stopEHEH = 1000){
  //the alarm eh part use EQ
  tone(buzzerPin, EHEH);
  delay(stopEHEH);
  noTone(buzzerPin);
  delay(stopEHEH);
}


void setup() {
  Serial.begin(57600);
  byte numDigits = 4;
  byte digitPin[] = {7,8,9,10};
  byte segmentPins[] = {2,3,4,5,11,12,13,6};
  bool ROS = 0; //reisitor onsegnemet
  bool LZ = true; //LEading zero
  bool disableDecimalPoint = true;
  bool updateWitDelays = false;
  sevseg.begin(COMMON_CATHODE,numDigits,digitPin,segmentPins,ROS,updateWitDelays,
  LZ, disableDecimalPoint);
  sevseg.setBrightness(90);

  pinMode(buzzerPin, OUTPUT);
  

 
}



void loop() {
  
  //int time = makeTime(currentTime);
  if(time<9){
    sevseg.setSegmentsDigit(2, 0x63);
  }
  sevseg.setNumber(minute(t));
  sevseg.refreshDisplay();
  buttonState = digitalRead(IRSbPin);
    if (buttonState == HIGH){
    highC++;
    //makeTime(currentTime);
    lowC = 0;
  }
  else{
    
    lowC++;
    
     if( highC >0){
     }
    highC = 0;
  }
  currentTime += millis() - currentTime;
  //Serial.println(currentTime);

    // delay(1000);
}



// int makeTime(long lilSecs){
//   int hours;
//   int minutes;
//   hours = lilSecs/36000000; //og 36000000
//   lilSecs -= hours*36000000; //og 36000000
//   minutes = lilSecs/60000; //og 60000
//   int finalDisplay = hours*100+minutes;
//   Serial.println(finalDisplay);
//   Serial.println("hours" + hours);
//   Serial.println("minutes" + minutes);
//   //Serial.println(minutes);
//   return finalDisplay;
// }
