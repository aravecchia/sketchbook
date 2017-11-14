#include <Arduino.h>

/*
Este codigo recebe a iluminacao de um LDR e escreve um valor proporcional num display de 8 segmentos.
 */

// Pin connected to SRCLK of 74HC595:
int CLOCK = 7;
// Pin connected to RCLK of 74HC595:
int LATCH = 5;
// Pin connected to SER of 74HC595:
int DATA = 6;

void setup()
{ 
  pinMode(LATCH, OUTPUT);
  pinMode(CLOCK, OUTPUT);
  pinMode(DATA, INPUT);
  //set pins to output so you can control the shift register
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

void loop()
{
  int t=100;  // so um delay
  //declara a matriz para um display de 8 segmentos
  //  {
  //    0bHGFEDCBA,
  //  };
  byte unidade[]=
  {
    0b00111111,  // caractere 0
    0b00000110,  // caractere 1
    0b01011011,  // caractere 2
    0b01001111,  // caractere 3
    0b01100110,  // caractere 4
    0b01101101,  // caractere 5
    0b01111101,  // caractere 6
    0b00000111,  // caractere 7
    0b01111111,  // caractere 8
    0b01101111,   // caractere 9
  };

  for (int i = 0; i < 10 ; i++)
  {
    // take the latchPin low
    digitalWrite(LATCH, LOW);
    // shift out the bits:
    delay(t);
    shiftIn(DATA, CLOCK, MSBFIRST, unidade[i]);
    //take the latch pin high so the LEDs update:
    digitalWrite(LATCH, HIGH);
    // pause before next value:
    Serial.print(i);
    delay(t);
    digitalWrite(LATCH, HIGH);
  }
}
