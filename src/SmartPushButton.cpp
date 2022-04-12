#include "SmartPushButton.h"


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



