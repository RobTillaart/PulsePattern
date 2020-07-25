//
//    FILE: pattern_recorder.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: records and writes a pattern to serial
//    DATE: 2020-07-25

//    (c) : MIT
//

#include "Arduino.h"

uint8_t valueCount = 0;

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
}

void loop()
{
  uint8_t  pin = 4;
  uint16_t minDuration = 50;
  uint16_t units = 10;
  uint32_t duration = recordPulse(pin, units, minDuration);

  Serial.print(duration);
  Serial.print(", ");
  valueCount++;
  if ( valueCount == 15)
  {
    Serial.println();
    valueCount = 0;
  }
}

uint32_t recordPulse(uint8_t pin, uint16_t unit, uint16_t minperiod)
{
  static uint8_t state;
  static uint32_t start;
  static bool first = true;
  if (first)
  {
    first = false;
    pinMode(pin, INPUT_PULLUP);
    state = digitalRead(pin);
    start = millis();
  }
  uint8_t newState = state;
  while ((millis() - start) < minperiod - unit);

  uint32_t now = millis();
  while (newState == state)
  {
    while (millis() - now < unit);
    now = millis();
    newState = digitalRead(pin);
  }
  state = newState;
  uint32_t duration = (now - start + unit - 1) / unit * unit;
  start = now;
  return duration;
}

// -- END OF FILE --
