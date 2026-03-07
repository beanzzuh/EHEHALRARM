#include "SevSeg.h"
#include <IRremote.h>
#define IRS A1
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


IRrecv irrecv(IRS);
decode_results results;

int currentTime = 1234;
void setup() {
  Serial.begin(115200);
  byte numDigits = 4;
  byte digitPin[] = {7,8,9,10};
  byte segmentPins[] = {2,3,4,5,11,12,13,6};
  bool ROS = 0; //reisitor onsegnemet
  sevseg.begin(COMMON_CATHODE,numDigits,digitPin,segmentPins,ROS);
  sevseg.setBrightness(90);

  pinMode(buzzerPin, OUTPUT);
  noTone(buzzerPin);

  IrReceiver.begin(IRS, ENABLE_LED_FEEDBACK);
}

void loop() {
  sevseg.setNumber(currentTime, 2);
  sevseg.refreshDisplay();

  if (IrReceiver.decode()){
     Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX); // Print "old" raw data
      // IrReceiver.printIRResultShort(&Serial); // Print complete received data in one line
      // IrReceiver.printIRSendUsage(&Serial);   // Print the statement required to send this data
 
      IrReceiver.resume();
  }
}
