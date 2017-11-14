#include <Arduino.h>

/*
  Blink
 Turns on an LED on for one second, then off for one second, repeatedly.
 
 This example code is in the public domain.
 */

// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int a=2;
int b=3;
int c=4;
int d=5;

int t=100;

int matriz[16][4] = {
  {
    0,0,0,0                                }
  ,
  {
    0,0,0,1                                }
  ,
  {
    0,0,1,0                                }
  ,
  {
    0,0,1,1                                }
  ,
  {
    0,1,0,0                                }
  ,
  {
    0,1,0,1                                }
  ,
  {
    0,1,1,0                                }
  ,
  {
    0,1,1,1                                }
  ,
  {
    1,0,0,0                                }
  ,
  {
    1,0,0,1                                }
  ,
  {
    1,0,1,0                                }
  ,
  {
    1,0,1,1                                }
  ,
  {
    1,1,0,0                                }
  ,
  {
    1,1,0,1                                }
  ,
  {
    1,1,1,0                                }
  ,
  {
    1,1,1,1                                }
  ,
};

// the setup routine runs once when you press reset:
void setup() 
{                
  // initialize the digital pin as an output.
  for (int pin=2; pin<6; pin++)
  {
    pinMode(pin, OUTPUT);
  }
}

// the loop routine runs over and over again forever:
void loop() {
  for(int i = 0; i<16; i++)
  {
    escreve(matriz[i]);       // wait for a second
    delay(t);
  }
}

void escreve( int m[] )
{
  digitalWrite(a, m[0]);
  digitalWrite(b, m[1]);
  digitalWrite(c, m[2]);
  digitalWrite(d, m[3]);   
}

