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

const int LedPin = 13;
const int transmit_pin = 12;
const int receive_pin = 2;
const int transmit_en_pin = 3;
const int button = 8;
int buttonState = 0;         // variable for reading the pushbutton status
int t = 100;

void setup()
{
  // Initialise the IO and ISR
  vw_set_tx_pin(transmit_pin);
  vw_set_rx_pin(receive_pin);
  vw_set_ptt_pin(transmit_en_pin);
  vw_set_ptt_inverted(true); // Required for DR3100
  vw_setup(2000);       // Bits per sec
  pinMode(LedPin, OUTPUT);
  pinMode(button, INPUT);
}

void loop()
{
  buttonState = digitalRead(button);
  if (buttonState == 1)
  {
    digitalWrite(LedPin, HIGH); // Flash a light to show transmitting
    vw_send((uint8_t *) & buttonState, 1);
    vw_wait_tx(); // Wait until the whole message is gone
    delay(t);
  }
  else {
    // turn LED off:
    digitalWrite(LedPin, LOW);
  }
}
