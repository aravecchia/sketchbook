#include <Arduino.h>

int t=100;

void setup()
{
  for (int pin=22; pin<26; pin++)
  {
    pinMode(pin, INPUT);
  }
  for (int led=26; led<47; led++)
  {
    pinMode(led, OUTPUT);
  }
  Serial.begin(9600);
}

void loop()
{
  for (int linha=0; linha<4; linha++)
  {
    digitalWrite((linha+26), HIGH);
    for (int coluna=0; coluna<4; coluna++)
    {
      if(digitalRead(coluna+22)==1)
      {
        Serial.print(" - Linha: ");
        Serial.print(linha+1);
        Serial.print("Coluna: ");
        Serial.println(coluna+1);
        digitalWrite(((4*linha)+30+coluna), HIGH);
        delay(t);
        digitalWrite(((4*linha)+30+coluna), LOW);
      }
    }
    digitalWrite(linha+26, LOW);
  }
}










