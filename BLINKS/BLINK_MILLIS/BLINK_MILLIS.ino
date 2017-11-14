#include <Arduino.h>

/*
  Blink
 Turns on an LED on for one second, then off for one second, repeatedly.
 
 This example code is in the public domain.
 */

// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led = 13;
int ledState = LOW;
long t0=0;
long t1=0;
int dt = 1000;
// the setup routine runs once when you press reset:
void setup() 
{                
  pinMode(led, OUTPUT);  
  Serial.begin(9600);  
}

// the loop routine runs over and over again forever:
void loop() 
{
  t1 = millis();
  if (t1-t0 >= dt)
  {
    t0=t1;
    ledState = !ledState;
    digitalWrite(led, ledState);
    Serial.print(t0);
    Serial.print(" - ");
    Serial.print(t1);
    Serial.print(" - ");
    Serial.println(millis());
  }
}





