#include <Arduino.h>

//**************************************************************//
// Name : shiftOutCode, Dual One By One
// Author : Carlyn Maw, Tom Igoe, CyberOhm.com
//
// Date : 29 Mar, 2015
//
// Version : 2.0
//
// Notes : Code for using a 74HC595 Shift Register with Arduino and Processing
//
// : to follow a potentiometer
//
//**************************************************************//

int LATCH = 2;
int DATA = 3;
int CLOCK = 4;
int t=100;

int matriz[8][8] = {
  {
    0,0,0,0,0,0,0,1              }
  ,
  {
    0,0,0,0,0,0,1,0              }
  ,
  {
    0,0,0,0,0,1,0,0              }
  ,
  {
    0,0,0,0,1,0,0,0              }
  ,
  {
    0,0,0,1,0,0,0,0              }
  ,
  {
    0,0,1,0,0,0,0,0              }
  ,
  {
    0,1,0,0,0,0,0,0              }
  ,
  {
    1,0,0,0,0,0,0,0              }
};

void setup()
{
  Serial.begin(9600);
  pinMode(LATCH, OUTPUT);
  pinMode(DATA, OUTPUT);
  pinMode(CLOCK, OUTPUT);

}
void loop() 
{
  for (int i=0; i<8; i++)
  {
    digitalWrite(LATCH, LOW);
    for (int j=0; j<8; j++)
    {
      digitalWrite(CLOCK, LOW);
      digitalWrite(DATA, matriz[i][j]);
      digitalWrite(CLOCK, HIGH);
      Serial.print("Led ");
      Serial.print(j);
      Serial.print(" = ");
      Serial.println(matriz[i][j]);
    }
    digitalWrite(LATCH, HIGH);
    Serial.println("___________");
    delay(t);
  }
}












