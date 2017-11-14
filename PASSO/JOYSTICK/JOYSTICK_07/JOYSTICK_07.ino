#include <Arduino.h>

/*
  Motor de Passo Mitsumi de 4 terminais + GND.
 Gira o motor em funcao da leitura de um potenciometro, sem usar biblioteca Stepper.
 Autor: http://cyberohm.com
 Apoio: http://www.labdegaragem.com
 */
//Define a matriz
int matriz[8][4] =
{
  {
    0,0,0,1                                                                }
  ,
  {
    0,0,1,1                                                                }
  ,
  {
    0,0,1,0                                                                }
  ,
  {
    0,1,1,0                                                                }
  ,
  {
    0,1,0,0                                                                }
  ,
  {
    1,1,0,0                                                                }
  ,
  {
    1,0,0,0                                                                }
  ,
  {
    1,0,0,1                                                                }

};

int joystick = A0;  // Analog input pin that the potentiometer is attached to

int t=1/100;
int x;
int y;
int count;

void setup() 
{                
  Serial.begin(9600);
  for (int pino=2; pino<6; pino++)
  {
    pinMode(pino, OUTPUT);
  }
}

void loop()
{
  int sensor = map(analogRead(joystick), 0, 1023, 0, 100);
  if ((count<=sensor)&&(sensor-count>2))
  {
    x++;
    if (x>7)
    {
      x=0;
    }
    count++;
    for (y=0; y<4; y++)
    {
      digitalWrite((y+2), matriz[x][y]);
      Serial.print(count);
      Serial.print(" -> ");
      Serial.println(sensor);
    }
    delay(t);
  }

  else if ((count>sensor)&&(count-sensor>2))
  {
    x--;
    if (x<0)
    {
      x=7;
    }
    count--;
    for (y=0; y<4; y++)
    {
      digitalWrite((y+2), matriz[x][y]);
      Serial.print(count);
      Serial.print(" -> ");
      Serial.println(sensor);
    }
    delay(t);
  }
}

























