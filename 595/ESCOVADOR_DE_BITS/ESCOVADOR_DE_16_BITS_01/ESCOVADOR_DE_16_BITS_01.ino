/*
Desenvolvido por Alexandre Aravecchia
aravecchia@gmail.com
www.aravecchia.weebly.com
*/

#include <Arduino.h>


int LATCH = 2; 
int DATA = 3;
int CLOCK = 4;

void setup()
{
  Serial.begin(9600);
  pinMode(LATCH, OUTPUT);
  pinMode(CLOCK, OUTPUT);
  pinMode(DATA, OUTPUT);
}

void loop()
{
  int t=100;
  // Tempo de delay.

  for (int x=1; x<256; x=x<<1)
  {
    digitalWrite(LATCH, LOW);
    // inicia a transmissao de DATA.
    shiftOut(DATA, CLOCK, MSBFIRST, x);
    shiftOut(DATA, CLOCK, MSBFIRST, x);
    digitalWrite(LATCH, HIGH);
    Serial.print("x = ");
    Serial.print(x);
    Serial.print(" - "); 
    Serial.println(x, BIN);

    if (x==1||x==128)
    {
      delay(10*t);
    }
    else
    {
      delay(t);
    }
  }
  for (int x=128; x>0; x=x>>1)
  {
    digitalWrite(LATCH, LOW);
    // inicia a transmissao de DATA.
    shiftOut(DATA, CLOCK, MSBFIRST, x);
    digitalWrite(LATCH, HIGH);
    Serial.print("x = ");
    Serial.print(x);
    Serial.print(" - "); 
    Serial.println(x, BIN);

    delay(t);
  }
}





