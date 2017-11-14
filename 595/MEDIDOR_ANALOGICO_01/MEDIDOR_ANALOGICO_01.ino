/*
/*Desenvolvido por Alexandre Aravecchia
  Projetista, desenvolvedor, programador
 aravecchia@gmail.com
 www.aravecchia.weebly.com
 */
Alexandre Aravecchia
Ana Clara Aravecchia
Rui Viana
Almir Bispo Filho
Laboratorio de Garagem
Labirito - Celso Eiji Ito
Blog do Embarcado
*/
#include <Arduino.h>

int sensor=A0;
int LATCH = 2; 
int DATA = 3;
int CLOCK = 4;
int t=250;

void setup()
{
  Serial.begin(9600);
  pinMode(LATCH, OUTPUT);
  pinMode(CLOCK, OUTPUT);
  pinMode(DATA, OUTPUT);
}

void loop()
{
  int matriz[10] = {
    0B11111100,  // 0
    0B01100000,  // 1
    0B11011010,  // 2
    0B11110010,  // 3
    0B01100110,  // 4
    0B10110110,  // 5
    0B10111110,  // 6
    0B11100000,  // 7
    0B11111110,  // 8
    0B11110110,  // 9     
  };

  int valor = map(analogRead(sensor), 0, 1023, 0, 999);
  Serial.print(valor);
  
  int z = valor/100;
  Serial.print(" - ");
    Serial.print(z);
    
  int y = (valor-(100*z))/10;
    Serial.print(" - ");
    Serial.print(y);
  
  int x = valor-(100*z)-(10*y);
    Serial.print(" - ");
    Serial.println(x);
  
  digitalWrite(LATCH, LOW);
  if (z==0)
  {
    shiftOut(DATA, CLOCK, LSBFIRST, 0B0);
  }
  else
  {
    shiftOut(DATA, CLOCK, LSBFIRST, matriz[z]);
  }
  if ((y==0)&&(z==0))
  {
    shiftOut(DATA, CLOCK, LSBFIRST, 0B0);
  }
  else
  {
    shiftOut(DATA, CLOCK, LSBFIRST, matriz[y]);
  }
  shiftOut(DATA, CLOCK, LSBFIRST, matriz[x]);
  digitalWrite(LATCH, HIGH); 
  delay(t);  
}














