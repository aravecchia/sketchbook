#include <Arduino.h>
/*Desenvolvido por Alexandre Aravecchia
  Projetista, desenvolvedor, programador
 aravecchia@gmail.com
 www.aravecchia.weebly.com
 */

int LATCH = 2; 
int DATA = 3;
int CLOCK = 4;
int sensorPin = A0;

void setup()
{
  Serial.begin(9600);
  pinMode(LATCH, OUTPUT);
  pinMode(CLOCK, OUTPUT);
  pinMode(DATA, OUTPUT);
  pinMode(sensorPin, INPUT);
}

void loop()
{
  int t=1000;
  // Tempo de delay.

  int sensorValue = map(analogRead(sensorPin), 0, 1023, 0, 16);
  long int relay[]={
    0,1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768  };

  int a = relay(sensorValue)>>8;
  int B = sensorValue<<8;
  int b = B>>8;

  digitalWrite(LATCH, LOW);
  // inicia a transmissao de DATA.
  shiftOut(DATA, CLOCK, MSBFIRST, a);
  shiftOut(DATA, CLOCK, MSBFIRST, b);
  digitalWrite(LATCH, HIGH);
  Serial.print("Sensor = ");
  Serial.print(sensorValue);
  Serial.print(" - "); 
  Serial.print(sensorValue, BIN);
  Serial.print(" <-> ");
  Serial.print(a);
  Serial.print(",");
  Serial.print(b);
  Serial.print(" - ");
  Serial.print(a, BIN);
  Serial.print(" ");
  Serial.println(b, BIN);

  delay(t);

}



















