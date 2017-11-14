#include <Arduino.h>

// receiver.pde
//
// Simple example of how to use VirtualWire to receive messages
// Implements a simplex (one-way) receiver with an Rx-B1 module
//
// See VirtualWire.h for detailed API docs
// Author: Mike McCauley (mikem@airspayce.com)
// Copyright (C) 2008 Mike McCauley
// $Id: receiver.pde,v 1.3 2009/03/30 00:07:24 mikem Exp $

#include <VirtualWire.h>

const int LedPin = 13;
const int transmit_pin = 12;
const int receive_pin = 11;
const int transmit_en_pin = 3;

int t=1000;
int LATCH = 4; 
int DATA = 5;
int CLK = 6;

byte digito[10]= {
  B11111100,B01100000,B11011010,B11110010,B01100110,B10110110,B10111110,B11100000,B11111110,B11110110};
// matrizes de 10 termos, cada um define um Byte diferente para cada
// digito de 0 a 9 no display, ou seja, liga um conjunto especifico de portas do 74hc595
// que acende um conjunto especifico de LEDs.

double Celsius;

void setup()
{
  delay(1000);
  Serial.begin(9600);	// Debugging only
  Serial.println("Iniciando repepcao...");

  // Initialise the IO and ISR
  vw_set_tx_pin(transmit_pin);
  vw_set_rx_pin(receive_pin);
  vw_set_ptt_pin(transmit_en_pin);
  vw_set_ptt_inverted(true); // Required for DR3100
  vw_setup(2000);	 // Bits per sec

  vw_rx_start();       // Start the receiver PLL running

  pinMode(LedPin, OUTPUT);

  pinMode(LATCH, OUTPUT);
  pinMode(CLK, OUTPUT);
  pinMode(DATA, OUTPUT);
}

void loop()
{
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;

  int z = Celsius/100;
  int y = (Celsius - 100*z)/10;
  int x = Celsius - 100*z - 10*y;

  if (vw_get_message(buf, &buflen)) // Non-blocking
  {
    int i;

    digitalWrite(LedPin, HIGH); // Flash a light to show received good message
    // Message with a good checksum received, dump it.
    //Serial.print("Got: ");

    for (i = 0; i < buflen; i++)
    {
      if (i==2)
      {
        Celsius = double(buf[i]);
        Serial.print(Celsius/10);//, INT);
        
        digitalWrite(LATCH, LOW);
        shiftOut(DATA, CLK, LSBFIRST, digito[x]); //primeiro CI recebe 1 Byte
        shiftOut(DATA, CLK, LSBFIRST, digito[y]+1);  //segundo CI recebe 1 Byte
        if (z==0)
        {
          shiftOut(DATA, CLK, LSBFIRST, 0); //terceiro CI recebe 1 Byte
        }
        else
        {
          shiftOut(DATA, CLK, LSBFIRST, digito[z]); //terceiro CI recebe 1 Byte
        }
        digitalWrite(LATCH, HIGH);
      }
      
      else if (i==9)
      {
        Serial.print(long(buf[i]));//, INT);
      }
      else
      {
        Serial.print(char(buf[i]));//, HEX);
      }
      Serial.print(' ');
    }
    Serial.println();
    digitalWrite(LedPin, LOW);
  }
}






