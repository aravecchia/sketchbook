#include <Arduino.h>

lint t;
int led;
int L1sensor = 6;
int L2sensor = 7;
int L3sensor = 8;
int AGUAsensor = 9;
int ledL1 = 10;
int ledL2 = 11;
int ledL3 = 13;
int ledAGUA = A0;
boolean L1state;
boolean L2state;
boolean L3state;
boolean AGUAstate;

void setup()
{
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  pinMode(L1sensor, INPUT);
  pinMode(L2sensor, INPUT);
  pinMode(L3sensor, INPUT);
  pinMode(AGUAsensor, INPUT);
  pinMode(ledL1, OUTPUT);
  pinMode(ledL2, OUTPUT);
  pinMode(ledL3, OUTPUT);
  pinMode(ledAGUA, OUTPUT);
  t = 10;
}

void loop()
{
  int L1state = digitalRead(L1sensor);
  int L2state = digitalRead(L2sensor);
  int L3state = digitalRead(L3sensor);
  int AGUAstate = digitalRead(AGUAsensor);
  int State[4] = {L1state, L2state, L3state, AGUAstate};
  int SENSOR[4] = {L1sensor, L2sensor, L3sensor, AGUAsensor};
  int LED[4] = {ledL1, ledL2, ledL3, ledAGUA};
  for (int x = 0; x < 4; x++)
  {

    Serial.print(LED[x]);
    Serial.print(" - ");
    Serial.print(SENSOR[x]);
    Serial.print(" - ");
    Serial.println(State[x]);
    digitalWrite(LED[x], State[x]);   // turn the LED on (HIGH is the voltage level)
    delay(t);              // wait for a second
  }
  t = 2000;
}
