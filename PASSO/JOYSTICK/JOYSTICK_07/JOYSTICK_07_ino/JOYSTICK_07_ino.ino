#include <Arduino.h>

/*
  Motor de Passo Mitsumi 5 terminais.
 Gira o motor em funcao da leitura de um potenciometro.
 Autor: http://cyberohm.com
 Apoio: http://www.labdegaragem.com
 */

int matriz[8][4] =
{
  {
    0,0,0,1                                                }
  ,
  {
    0,0,1,1                                                }
  ,
  {
    0,0,1,0                                                }
  ,
  {
    0,1,1,0                                                }
  ,
  {
    0,1,0,0                                                }
  ,
  {
    1,1,0,0                                                }
  ,
  {
    1,0,0,0                                                }
  ,
  {
    1,0,0,1                                                }

};

int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
int analogTimerPin = A1;
int t=50;
int x=0;
int y=0;
int count=0;

void setup() 
{                
  Serial.begin(9600);
  pinMode(2, OUTPUT);   
  pinMode(3, OUTPUT); 
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT); 
}

void loop()
{
  // read the analog in value:
  int  sensorValue = analogRead(analogInPin);            
  // map it to the range of the analog out:
  int  outputValue = map(sensorValue, 0, 1023, 0, 96);  
  // change the analog out value:
  int T = analogRead(analogTimerPin);
  int t = map(T, 0, 1023, 5, 50);

  digitalWrite((y+2), matriz[x][y]);
  if(count>outputValue)
  {
    digitalWrite((y+2), matriz[x][y]);
    Serial.print(sensorValue);
    Serial.print(" - ");
    Serial.print(outputValue);
    Serial.print(" - ");
    Serial.println(count);
    count++;
    delay(t);
  }
    else if(count<outputValue)
  {
    digitalWrite((y+2), matriz[x][y]);
    Serial.print(sensorValue);
    Serial.print(" - ");
    Serial.print(outputValue);
    Serial.print(" - ");
    Serial.println(count);
    count--;
  }
  if(count>96)
  {
    count=0;
  }
  y++;
  if (y==4)
  {
    x++;
    y=0;
  }
  if (x==8)
  {
    x=0;
  }
  if(count<0)
  {
    count=96;
  }
  y--;
  if (y<0)
  {
    x--;
    y=3;
  }
  if (x==0)
  {
    x=7;
  }
  delay(t);
}



