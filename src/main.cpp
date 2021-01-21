#include <Arduino.h>
#include <stdio.h>
#include "./utilities.h"

#define PINOUT_1 2
#define PINOUT_2 3

#define HIGH_STATE_IN_MILISEC 1500
int pinOuts[] = {PINOUT_1,PINOUT_2};

void setup()
{
  Serial.begin(115200);
  pinMode(PINOUT_1, OUTPUT);
}

void loop()
{
  decissionSwitch(HIGH_STATE_IN_MILISEC,pinOuts);
}
