#ifndef _SMARTPUSHBUTTON_h
#define _SMARTPUSHBUTTON_h

#include <Arduino.h>
#include <Signals.h>



#define EVENT_SINGLE_PRESSED      1
#define EVENT_DOUBLE_PRESSED      2
#define EVENT_SINGLE_PRESSED_HOLD 3
#define EVENT_DOUBLE_PRESSED_HOLD 4

#define ACTIVE_LOW	0
#define ACTIVE_HIGH 1

class SmartPushButton {
  
  public:
    void begin(int Pin, int Polarity);
    void process();
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
   
	Signals<> signalSinglePress;
	Signals<> signalSinglePressHold;
	Signals<> signalDoublePress;
	Signals<> signalDoublePressHold;
   
  private:
    void stateMachine();
    unsigned long pMillis; 
	unsigned char PUSHED, NOTPUSHED;
    int tPin;
    int longPressInterval = 200;
    int shortPressInterval = 50;
    int counter = 0;
    int pushCounter = 0;
    int Event = 0;
    int tState = 0;
};

#endif





