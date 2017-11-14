#include <Arduino.h>


int led;
int t;
int sensor = A0;

//________________________________________________________________________________
void setup() 
{    
  for(led=5; led<9; led++)
  {
    pinMode(led, OUTPUT);  
  } 
      pinMode(sensor, INPUT); 
}
//________________________________________________________________________________

void loop() 
{
  t = analogRead(sensor);
  for (led=5; led<9; led++)
  {
    digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(t);               // wait for a second
    digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  }
  for (led=7; led>5; led--)
  {
    digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(t);               // wait for a second
    digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  }
}



