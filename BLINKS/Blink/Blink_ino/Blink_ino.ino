#include <Arduino.h>

/*
  Blink
 Turns on an LED on for one second, then off for one second, repeatedly.
 
 This example code is in the public domain.
 */

// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led;
int sensor=A5;

// the setup routine runs once when you press reset:
void setup()
{      
  Serial.begin(9600);   
  for(led=2; led<10; led++)
  {
    pinMode(led, OUTPUT); 
  }
  pinMode(sensor, INPUT); 
}

// the loop routine runs over and over again forever:
void loop()
{
  int a=2;
  int b=3;
  int c=4;
  int d=5;
  int e=6;
  int f=7;
  int g=8;
  int h=9;
  int matriz[]={
    a,b,c,d,e,f,g,h          };

  for (int x=0; x<8; x++)
  {
    int sensorValue = analogRead(sensor);
    int t = map(sensorValue, 0, 1023, 0, 255);
    digitalWrite(matriz[x], HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(t);
    digitalWrite(matriz[x], LOW);   // turn the LED on (HIGH is the voltage level)
    Serial.println(t);
  }
  for(int x=6; x>0; x--)
  {
    int sensorValue = analogRead(sensor);
    int t = map(sensorValue, 0, 1023, 0, 255);
    digitalWrite(matriz[x], HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(t);
    digitalWrite(matriz[x], LOW);   // turn the LED on (HIGH is the voltage level)
    Serial.println(t);
  }
}



