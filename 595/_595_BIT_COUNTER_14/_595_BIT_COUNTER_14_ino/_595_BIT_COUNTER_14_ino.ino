#include <Arduino.h>

//**************************************************************//
// Name : shiftOutCode, Dual One By One
// Author : Carlyn Maw, Tom Igoe
//
// Date : 25 Oct, 2006
//
// Version : 1.0
//
// Notes : Code for using a 74HC595 Shift Register
//
// : to count from 0 to 255
//
//**************************************************************//
//Pin connected to ST_CP of 74HC595
int LATCH = 2;
//Pin connected to DS of 74HC595
int DATA = 3;
////Pin connected to SH_CP of 74HC595
int CLOCK = 4;
//holder for information you're going to pass to shifting function
//byte data = 0;
//
void setup()
{
  //set pins to output because they are addressed in the main loop
  pinMode(LATCH, OUTPUT);
}
void loop() {
  //function that blinks all the LEDs
  //gets passed the number of blinks and the pause time
//  blinkAll_2Bytes(1,500);
  // light each pin one by one using a function A
  for (int j = 0; j < 8; j++) 
  {
    //ground latchPin and hold low for as long as you are transmitting
    digitalWrite(LATCH, 0);
    //green LEDs
    lightShiftPinA(j);
    //return the latch pin high to signal chip that it
    //no longer needs to listen for information
    digitalWrite(LATCH, 1);
    delay(500);
  }
}
//This function uses bitwise math to move the pins up
void lightShiftPinA(int p) 
{
  //defines a local variable
  int pin;
  //this is line uses a bitwise operator
  //shifting a bit left using << is the same
  //as multiplying the decimal number by two.
  pin = 1<< p;
  //move 'em out
  shiftOut(DATA, CLOCK, pin);
}
// the heart of the program
void shiftOut(int myDATA, int myCLOCK, byte myDATAOut)
{
  {
    // This shifts 8 bits out MSB first,
    //on the rising edge of the clock,
    //clock idles low
    //internal function setup
    int i=0;
    int pinState;
    pinMode(myCLOCK, OUTPUT);
    pinMode(myDATA, OUTPUT);
    //clear everything out just in case to
    //prepare shift register for bit shifting
    digitalWrite(myDATA, 0);
    digitalWrite(myCLOCK, 0);
    //for each bit in the byte myDataOut�
    //NOTICE THAT WE ARE COUNTING DOWN in our for loop
    //This means that %00000001 or "1" will go through such
    //that it will be pin Q0 that lights.
    for (i=7; i>=0; i--) {
      digitalWrite(myCLOCK, 0);
      //if the value passed to myDataOut and a bitmask result
      // true then... so if we are at i=6 and our value is
      // %11010100 it would the code compares it to %01000000
      // and proceeds to set pinState to 1.
      if ( myDATAOut & (1<<i) ) {
        pinState= 1;
      }
      else {
        pinState= 0;
      }
      //Sets the pin to HIGH or LOW depending on pinState
      digitalWrite(myDATA, pinState);
      //register shifts bits on upstroke of clock pin
      digitalWrite(myCLOCK, 1);
      //zero the data pin after shift to prevent bleed through
      digitalWrite(myDATA, 0);
    }
  }
  //stop shifting
  digitalWrite(myCLOCK,0);
  //blinks both registers based on the number of times you want to
  //blink "n" and the pause between them "d"
  //starts with a moment of darkness to make sure the first blink
  //has its full visual effect.
}


