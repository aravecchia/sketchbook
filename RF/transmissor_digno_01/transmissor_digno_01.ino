#include <Arduino.h>

// transmitter.pde
//
// Simple example of how to use VirtualWire to transmit messages
// Implements a simplex (one-way) transmitter with an TX-C1 module
//
// See VirtualWire.h for detailed API docs
// Author: Mike McCauley (mikem@airspayce.com)
// Copyright (C) 2008 Mike McCauley
// $Id: transmitter.pde,v 1.3 2009/03/30 00:07:24 mikem Exp $

#include <VirtualWire.h>

const int led_pin = 10;
const int transmit_pin = 12;
const int receive_pin = 2;
const int transmit_en_pin = 3;
int t=1000;

void setup()
{
  Serial.begin(9600);	// Debugging only
  Serial.println("Iniciando transmissao...");
  // Initialise the IO and ISR
  vw_set_tx_pin(transmit_pin);
  //    vw_set_rx_pin(receive_pin);
  vw_set_ptt_pin(transmit_en_pin);
  vw_set_ptt_inverted(true); // Required for DR3100
  vw_setup(2000);       // Bits per sec
  pinMode(led_pin, OUTPUT);
  pinMode(A0, INPUT);
}



void loop()
{
  char msg[11] = {
    'S', 'e', 'n', 's', 'o', 'r', ' ', '=', ' ', '#', '%'  };

  long temperatura = map(analogRead(A0), 0, 1023, 100, 0);
  Serial.println(temperatura);
  msg[9] = temperatura;
  digitalWrite(led_pin, HIGH); // Flash a light to show transmitting
  vw_send((uint8_t *)msg, 11);
  vw_wait_tx(); // Wait until the whole message is gone
  digitalWrite(led_pin, LOW);
  delay(t);
  // count = count + 1;
}

