#ifndef _SMARTPUSHBUTTON_h
#define _SMARTPUSHBUTTON_h

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

void SmartPushButton::stateMachine(){
  int pb = digitalRead(tPin);
  switch(tState){
    case 0:
      if (pb == PUSHED){
        tState = 1;
      }
      break;
      
    case 1:
      if (pb == PUSHED){
        counter++;
        if (counter > longPressInterval){
          if (pushCounter == 0)
            Event = EVENT_SINGLE_PRESSED_HOLD;
          else if (pushCounter == 1)
            Event = EVENT_DOUBLE_PRESSED_HOLD;
          tState = 2;
        }
      }
      else{
        tState = 4;
      }
      break;
      
    case 2:
      if (pb == NOTPUSHED){
        tState = 3;
      }
      break; 
       
    case 3:
      counter = 0;
      pushCounter = 0;
      Event = 0;
      tState = 0;
      break; 
      
    case 4:
      counter++;
      if ((pb == NOTPUSHED) && (counter > shortPressInterval)){
        if (pushCounter == 0)
            Event = EVENT_SINGLE_PRESSED;
        else if (pushCounter == 1)
            Event = EVENT_DOUBLE_PRESSED; 
        tState = 3;
      }
      else if ((pb == PUSHED) && (counter <= shortPressInterval)){
        counter = 0;
        pushCounter++;
        tState = 1;
      }
      break;      
  }
}



