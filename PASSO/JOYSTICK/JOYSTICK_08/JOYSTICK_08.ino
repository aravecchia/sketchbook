/*
Desenvolvido por Alexandre Aravecchia
aravecchia@gmail.com
www.aravecchia.weebly.com
*/

#include <Arduino.h>

/*
  Motor de Passo Mitsumi 5 terminais.
 Gira o motor em funcao de um potenciometro acoplado ao joystick.
 */
int vertical = A0;
int var=650;
int matriz[8][4] =
{
  {
    0,0,0,1                                }
  ,
  {
    0,0,1,1                                }
  ,
  {
    0,0,1,0                                }
  ,
  {
    0,1,1,0                                }
  ,
  {
    0,1,0,0                                }
  ,
  {
    1,1,0,0                                }
  ,
  {
    1,0,0,0                                }
  ,
  {
    1,0,0,1                                }  
};

void setup() 
{                
  Serial.begin(9600);
  for (int pino=2; pino<6; pino++)
  {
    pinMode(pino, OUTPUT);  
  }
  pinMode(vertical, INPUT); 
}

void loop()
{
  int t=10;
 for (int x=0; x<7; x++)
  {
    for (int y=0; y<4; y++)
    {
      if (var<analogRead(A0))
      {
        digitalWrite((y+2), matriz[x][y]);
        delay(t);
        var++;
      }
      else if(var==analogRead(A0))
      delay(10*t);
    }
  }

  for (int x=7; x>=0; x--)
  {
    for (int y=0; y<4; y++)
    {
      if (var>analogRead(A0))
      {
        digitalWrite((y+2), matriz[x][y]);
        delay(t);
        var--;
      }
       else if(var==analogRead(A0))
      delay(10*t);
    }
  }

  Serial.print(var);
  Serial.print(" - ");
  Serial.println(analogRead(A0));
}
















