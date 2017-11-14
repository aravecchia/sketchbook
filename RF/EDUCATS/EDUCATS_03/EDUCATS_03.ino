/*
Desenvolvido por Alexandre Aravecchia
aravecchia@gmail.com
www.aravecchia.weebly.com
*/

#include <Arduino.h>

int LDR=A1;
int Button1=2;
int Button2=3;
int AGUA=10;
int L1=11;
int L2=13;
int L3=A0;

void setup()
{
  pinMode(LDR, INPUT);
  pinMode(Button1, INPUT);
  pinMode(Button2, INPUT);
  pinMode(AGUA, OUTPUT);
  pinMode(L1, OUTPUT);
  pinMode(L2, OUTPUT);
  pinMode(L3, OUTPUT);

}

void loop()
{
  if (analogRead(LDR) >= 512)
  {
    if ((digitalRead(Button1) == HIGH) && (digitalRead(Button2) == LOW))
    {
      digitalWrite(L1, HIGH);
      digitalWrite(L2, LOW);
    }
    else if ((digitalRead(Button1) == LOW) && (digitalRead(Button2) == HIGH))
    {
      digitalWrite(L1, LOW);
      digitalWrite(L2, HIGH);
    }
    else if ((digitalRead(Button1) == HIGH) && (digitalRead(Button2) == HIGH))
    {
      digitalWrite(L1, HIGH);
      digitalWrite(L2, HIGH);
    }
    else
    {
      digitalWrite(L1, LOW);
      digitalWrite(L2, LOW);
    }
  }
  else
  {
    digitalWrite(L1, HIGH);
    digitalWrite(L2, HIGH);
  }
}
