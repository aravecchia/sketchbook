#include <Arduino.h>

/*
  Motor de Passo Mitsumi 5 terminais.
 Acelera o motor progressivamente, desacelera ate parar,
 inverte a rotaco, acelera novamente, e assim vai.
 */

void setup() {                
  // initialize the digital pin as an output.
  // Pin 13 has an LED connected on most Arduino boards:
  Serial.begin(9600);
  pinMode(3, OUTPUT);   
  pinMode(4, OUTPUT); 
  pinMode(5, OUTPUT); 
  pinMode(6, OUTPUT);
  pinMode(13, OUTPUT);


}

void loop()
{
  int tempo=320;
  int t=tempo;
  while (t>=1)
  {
    {
      digitalWrite(3, 1);
      digitalWrite(4, 0);
      digitalWrite(5, 0);
      digitalWrite(6, 0);
      digitalWrite(13, 1);
      delay(t); 
    }
    {
      digitalWrite(3, 1);
      digitalWrite(4, 1);
      digitalWrite(5, 0);
      digitalWrite(6, 0);
      digitalWrite(13, 0);
      delay(t); 
    }
    {
      digitalWrite(3, 0);
      digitalWrite(4, 1);
      digitalWrite(5, 0);
      digitalWrite(6, 0);
      digitalWrite(13, 1);
      delay(t); 
    }
    {
      digitalWrite(3, 0);
      digitalWrite(4, 1);
      digitalWrite(5, 1);
      digitalWrite(6, 0);
      digitalWrite(13, 0);
      delay(t); 
    }
    {
      digitalWrite(3, 0);
      digitalWrite(4, 0);
      digitalWrite(5, 1);
      digitalWrite(6, 0);
      digitalWrite(13, 1);
      delay(t); 
    }
    {
      digitalWrite(3, 0);
      digitalWrite(4, 0);
      digitalWrite(5, 1);
      digitalWrite(6, 1);
      digitalWrite(13, 0);
      delay(t); 
    }
    {
      digitalWrite(3, 0);
      digitalWrite(4, 0);
      digitalWrite(5, 0);
      digitalWrite(6, 1);
      digitalWrite(13, 1);
      delay(t); 
    }
    {
      digitalWrite(3, 1);
      digitalWrite(4, 0);
      digitalWrite(5, 0);
      digitalWrite(6, 1);
      digitalWrite(13, 0);
      delay(t);
    }
    t=t--;
  }
  while (t<=tempo)
  {
    {
      digitalWrite(3, 0);
      digitalWrite(4, 0);
      digitalWrite(5, 0);
      digitalWrite(6, 1);
      digitalWrite(13, 1);
      delay(t); 
    }
    {
      digitalWrite(3, 0);
      digitalWrite(4, 0);
      digitalWrite(5, 1);
      digitalWrite(6, 1);
      digitalWrite(13, 0);
      delay(t); 
    }
    {
      digitalWrite(3, 0);
      digitalWrite(4, 0);
      digitalWrite(5, 1);
      digitalWrite(6, 0);
      digitalWrite(13, 1);
      delay(t); 
    }
    {
      digitalWrite(3, 0);
      digitalWrite(4, 1);
      digitalWrite(5, 1);
      digitalWrite(6, 0);
      digitalWrite(13, 0);
      delay(t); 
    }
    {
      digitalWrite(3, 0);
      digitalWrite(4, 1);
      digitalWrite(5, 0);
      digitalWrite(6, 0);
      digitalWrite(13, 1);
      delay(t); 
    }
    {
      digitalWrite(3, 1);
      digitalWrite(4, 1);
      digitalWrite(5, 0);
      digitalWrite(6, 0);
      digitalWrite(13, 0);
      delay(t); 
    }
    {
      digitalWrite(3, 1);
      digitalWrite(4, 0);
      digitalWrite(5, 0);
      digitalWrite(6, 0);
      digitalWrite(13, 1);
      delay(t); 
    }
    {
      digitalWrite(3, 1);
      digitalWrite(4, 0);
      digitalWrite(5, 0);
      digitalWrite(6, 1);
      digitalWrite(13, 0);
      delay(t);
    } 
    t=t++;
  }
}


