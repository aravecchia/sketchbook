#include <Wire.h>
int t = 100;
byte data;
int bus = 56;
//---------------------------
void setup()
{
  Wire.begin();
  Serial.begin(9600);
}
//---------------------------
void loop()
{

 Wire.requestFrom(bus, 1);
if(Wire.available())
{
data = Wire.read();
Serial.println(data,BIN);
}
    delay(t);                                    // Delay 1 seg
}
