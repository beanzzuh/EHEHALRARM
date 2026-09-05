#include "SevSeg.h"
#define IRSbPin A1 //is time
#define setEHEH A2 //set alrarm
#include <CronAlarms.h>
#include <TimeLib.h>
#include <ezButton.h>


//SO YOU DONT HAVE TO SEARCH UP https://github.com/PaulStoffregen/Time/tree/master]

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

// bool settingAlarm = false;
// bool alarmArmed = false;
unsigned long currentTime = 360000; //og 360000
// unsigned long alarmTime = -1;


int clockMode = 0; // 0 = normal clock 1 = setting clock


int alarmEH = 432;
 
int buttonState = 0;
int buttonState2 = 0;
int buttonState3 = 0;
const int redChange = A1;
const int blueSet = A2;
const int orangeAlarm = A3;

ezButton buttChange(A1);
ezButton buttSet(A2);
ezButton buttAlarm(A3);


int hours;
int minutes;

unsigned long previousMillis = 0;
const long onEH = 1000;
const long offEH = 1000;

bool alarmIsRinging = false;
bool alarmCanRing = false;
bool alarmIsSet = false;

double cIndex = 0;



void changeT(){
  if(cIndex >= 3){
    cIndex = 0;
  }
  else {
    cIndex += 0.5;
    // delay(1000);
    
  }
}



void blare(unsigned EHEH = 432, unsigned stopEHEH = 1000){
  static unsigned timer = 0, elapsed = 0;
  int delay = 500;

  elapsed = millis() - timer;
  if(elapsed >= delay){
    timer += delay;
  }
  if(alarmIsRinging && alarmCanRing){
    digitalWrite(buzzerPin,elapsed < 250 && elapsed < 1000);
  }
  
  //the alarm eh part use EQ
  //tone(buzzerPin, EHEH);
  //delay(stopEHEH);
  //noTone(buzzerPin);
  //delay(stopEHEH);
}
enum Position{
  HOURS,
  MINUTES
};

struct AlarmTime {
  int mm;
  int hh;
};

AlarmTime alarmTime = {};

Position pos = MINUTES;

void setup() {
  buttChange.setDebounceTime(10);
  buttSet.setDebounceTime(10);
  setTime(10,59,0,9,5,26);
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

  pinMode(redChange, INPUT);
  pinMode(blueSet, INPUT);
  pinMode(orangeAlarm, INPUT);
}

unsigned timeDelay = 500;
unsigned currentTimedelay = timeDelay;

void buttonControls(){
  if(buttonState == HIGH){
    changeT();
  }
  if(buttonState2 == HIGH && currentTimedelay >= 500){
    currentTimedelay = 0;
  }
}

int position = 0;

void changeDigitpos(int &position){
  if(position == 3){
    position = 0;
  }
  else{
    position++;
  }
}

void setNumber(char &digit){
  if(digit == 57){
    digit = 48;
  }
  else{
    digit++;
  }
}

void adjustHours(){
  adjustTime(3600);
}
void adjustMinutes(){
  adjustTime(60);
}

int start = -1;

void loop() {
  buttChange.loop();
  buttSet.loop();
  buttAlarm.loop();
  buttonState = digitalRead(redChange);
  buttonState2 = digitalRead(blueSet);
  buttonState3 = digitalRead(orangeAlarm);
  buttonControls();
  blare();

  if(buttChange.isPressed()){
   //changeDigitpos(position);
   //alarmIsRinging = false;
   if(pos == HOURS){
    pos = MINUTES;
   } else{
    pos = HOURS;
   }
   //Serial.println(position);
  }

  time_t t = now();

  if(buttSet.isPressed()){
    
    if(pos == HOURS){
      adjustHours();
    } else {
      adjustMinutes();
    }
    if(alarmIsSet){
      int belay = 500;
      if(start == -1){
        start = millis();
      }
      else if(millis()-start > belay && !alarmCanRing){
        alarmCanRing = true;
        Serial.println("AlarmCanrnig");
      }
     
    }
  }

  int mm = minute(t);
  int hh = hour(t);
  int ASCII0 = 48;
  

  if(buttAlarm.isPressed()){
    alarmTime.mm = mm;
    alarmTime.hh = hh;
    alarmIsSet = true;
    Serial.println("alarm is set");
    
    //Serial.println("ur pressing my buttons");
    
  }

  if(alarmTime.mm == mm && alarmTime.hh == hh && alarmCanRing){
    //Serial.println("YAy");
    alarmIsRinging = true;
    Serial.println("ALaramisRing");

  }

  char h1 = hh % 10 + ASCII0;
  char h2 = hh/10 + ASCII0;
  char m1 = mm % 10 + ASCII0;
  char m2 = mm/10 + ASCII0;
  
  char timeStr[4] = {h2,h1,m2,m1};
  //int time = makeTime(currentTime);
  sevseg.setChars(timeStr);

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

