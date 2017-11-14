#include <Arduino.h>

//**************************************************************//
// Name : shiftOutCode, Dual One By One
// Author : Carlyn Maw, Tom Igoe, CyberOhm.com
//
// Date : 29 Mar, 2015
//
// Version : 2.0
//
// Notes : Code for using a 74HC595 Shift Register with Arduino and Processing
//
// : to follow a potentiometer
//
//**************************************************************//

int LATCH = 2;
int DATA = 3;
int CLOCK = 4;
int t=1000;
//Proxima etapa: transformar essa matrix numa mascara e/ou deslicamento de bits.
int matriz=1;
int i;
int deslocamento=(matriz>>i);

void setup()
{
  Serial.begin(9600);
  pinMode(LATCH, OUTPUT);
  pinMode(DATA, OUTPUT);
  pinMode(CLOCK, OUTPUT);

}
void loop() 
{
    digitalWrite(LATCH, LOW);
    for (i=1; i<8; i++)
    {
      digitalWrite(CLOCK, LOW);
      digitalWrite(DATA, deslocamento);
      digitalWrite(CLOCK, HIGH);
      Serial.println(i);
            delay(t);
    }
    digitalWrite(LATCH, HIGH);
    Serial.println("___________");
  
}













