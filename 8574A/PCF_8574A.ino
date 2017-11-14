#include <Arduino.h>

#include <Wire.h>
#define mux1 0x54

void setup()
{
  Wire.begin();
  Wire.beginTransmission(mux1);
  Wire.send(B00000000);
  Wire.endTransmission;
}

void loop()
{
  for (int b=0; b<256; b++)
  {
  Wire.beginTransmission(mux1);
  Wire.send(b);
  Wire.endTransmission;
  delay(100);
  }
}
