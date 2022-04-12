#include <SmartPushButton.h>

SmartPushButton spb;

void setup()
{
  Serial.begin (57600); 
  spb.begin(0);         //Set the input pin
}

void loop()
{
  spb.process();
  
  if (spb.event() == EVENT_SINGLE_PRESSED){
    Serial.println("SINGLE PRESS");
    spb.clearEvent();
  } 
  else if (spb.event() == EVENT_SINGLE_PRESSED_HOLD){
    Serial.println("SINGLE PRESS & HOLD");
    spb.clearEvent();
  }
  else if (spb.event() == EVENT_DOUBLE_PRESSED){
    Serial.println("DOUBLE PRESS");
    spb.clearEvent();
  }
  else if (spb.event() == EVENT_DOUBLE_PRESSED_HOLD){
    Serial.println("DOUBLE PRESS & HOLD");
    spb.clearEvent();
  }
  
}
