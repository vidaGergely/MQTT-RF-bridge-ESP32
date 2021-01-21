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

void decissionSwitch(int highStateInMilisec, int pinOuts[])
{
  if (Serial.available() > 0)
  {
    int incommingBytes = Serial.read();
    switch (incommingBytes)
    {
      //ON, or OFF led state
    case 49:
      stateChange(highStateInMilisec,pinOuts[0]);
      break;
    case 50:
      stateChange(highStateInMilisec,pinOuts[1]);
      break;

    default:
      break;
    }
  }
}
