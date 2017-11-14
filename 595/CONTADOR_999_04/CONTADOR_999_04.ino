#include <Arduino.h>

/*Desenvolvido por Alexandre Aravecchia
  Projetista, desenvolvedor, programador
 aravecchia@gmail.com
 www.aravecchia.weebly.com
 */
int LATCH = 2; 
int DATA = 3;
int CLOCK = 4;
int t=1000;

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

  for (int x=0; x<10; x++)
  {
    digitalWrite(LATCH, LOW);
    for (int z=0; z<3; z++)
    {
      shiftOut(DATA, CLOCK, LSBFIRST, matriz[x]);
    }   
    delay(t); 
    digitalWrite(LATCH, HIGH);      


  }

}











