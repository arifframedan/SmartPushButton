#ifndef _SMARTPUSHBUTTON_h
#define _SMARTPUSHBUTTON_h

#include <Arduino.h>

#define EVENT_SINGLE_PRESSED      1
#define EVENT_DOUBLE_PRESSED      2
#define EVENT_SINGLE_PRESSED_HOLD 3
#define EVENT_DOUBLE_PRESSED_HOLD 4

class SmartPushButton {
  #define PUSHED    0
  #define NOTPUSHED 1
  
  public:
    void begin(int Pin){
      tPin = Pin;
      pinMode(tPin, INPUT_PULLUP);
      pMillis = millis();
    }
    void process(){
      unsigned long cMillis = millis();
      if (cMillis - pMillis >= 10){
        pMillis = cMillis;
        stateMachine();
      }
    }
    int event(){
      return Event;
    }
    void clearEvent(){
      Event  = 0;
    }
    void setShortPressInterval(int mSec){
      shortPressInterval = mSec/10;
    }
    void setLongPressInterval(int mSec){
      longPressInterval = mSec/10;
    }
   
  private:
    void stateMachine();
    unsigned long pMillis; 
    int tPin;
    int longPressInterval = 200;
    int shortPressInterval = 50;
    int counter = 0;
    int pushCounter = 0;
    int Event = 0;
    int tState = 0;
};

#endif





