#include <SmartPushButton.h>
SmartPushButton spb;
void setup()
{
  Serial.begin (57600); 
  spb.begin(0, ACTIVE_LOW);
}

void loop()
{
  spb.process();
  spb.signalSinglePress.connect(singlePressCallback);
}

void singlePressCallback(){
  Serial.println("SINGLE PRESS");
}
