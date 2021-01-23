#include <Arduino.h>

void stateChange(int highStateInMilisec, int pintOut)
{
  digitalWrite(pintOut, HIGH);
  unsigned long currentTime = millis();
  while ((millis() - currentTime) <= highStateInMilisec)
  {
  }
  digitalWrite(pintOut, LOW);
}

