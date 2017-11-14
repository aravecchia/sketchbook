#include <Arduino.h>
/*
Desenvolvido por Alexandre Aravecchia
aravecchia@gmail.com
www.aravecchia.weebly.com
*/

int t=250;
int y=255;
void setup()
{
  Serial.begin(9600);

}

void loop()
{
  for(int x=1; x<256; x=x<<1)
  {
    Serial.println(x, BIN);
    Serial.println((y), BIN);
    Serial.println("__________&");
    Serial.println((x & y), BIN);
        Serial.println("**********");
    delay(5*t);
    }
    delay(50*t);
}

