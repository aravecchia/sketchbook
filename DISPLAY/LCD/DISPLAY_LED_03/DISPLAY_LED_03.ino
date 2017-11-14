#include <Arduino.h>

int LATCH = 2; 
int DATA = 3;
int CLK = 4;
int t=1000;
// define os pinos de latch, data e clock do 74HC595 que controla o display da temperatura do ambiente

byte digito[8]= {B10000000,B01000000,B00100000,B00010000,B00001000,B00000100,B00000010,B00000001};
void setup()
{
  Serial.begin(9600);

  pinMode(LATCH, OUTPUT);
  pinMode(CLK, OUTPUT);
  pinMode(DATA, OUTPUT);


}

void loop()
{
  
    {
      digitalWrite(LATCH, LOW);
      shiftOut(DATA, CLK, LSBFIRST, digito[0]); //primeiro CI recebe 1 Byte
      digitalWrite(LATCH, HIGH); 
      delay(t);
    }
  if 
}







