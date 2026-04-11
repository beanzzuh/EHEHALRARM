#include "SevSeg.h"
#define IRSbPin A1 //is time
#define setEHEH A2 //set alrarm
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
unsigned long currentTime = 0;
unsigned long alarmTime = -1;

int clockMode = 0; // 0 = normal clock 1 = setting clock


int alarmEH = 432;
 
int buttonState = 0;


/*remote stuff
power = BA45FF00 (vol up)
VOL+ = B946FF00 (vol down)
FUNC/STOP = B847FF00 (dont stop add more time)
ARROWSL = BB44FF00 (increse pitch)
PLAYPUASE = BF40FF00 (no)
ARROWSR = BC43FF00 (incres potch)
ARROWD = F807FF00 (incres po\itch)
VOL- = EA15FF00 (vol up)
ARROWU = F609FF00(lowerpitch)
0 = E916FF00
eq = E619FF00 (test alarm )
T/REPT = F20DFF00
1= F30CFF00
2= E718FF00
3=A15EFF00
4=F708FF00
5=E31CFF00
6=A55AFF00
7=BD42FF00
8=AD52FF00
9 = B54AFF00
*/

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
  sevseg.begin(COMMON_CATHODE,numDigits,digitPin,segmentPins,ROS);
  sevseg.setBrightness(90);

  pinMode(buzzerPin, OUTPUT);
  

 
}

void loop() {
  sevseg.setNumber(currentTime, 2);
  sevseg.refreshDisplay();
  buttonState = digitalRead(IRSbPin);
    if (buttonState == HIGH){
    highC++;
     
    lowC = 0;
  }
  else{
    
    lowC++;
    
     if( highC >0){
     }
    highC = 0;
  }
  currentTime += millis() - currentTime;
  Serial.println(currentTime);

    // delay(1000);
}
