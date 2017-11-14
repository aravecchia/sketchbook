#include <Arduino.h>
/*Desenvolvido por Alexandre Aravecchia
  Projetista, desenvolvedor, programador
 aravecchia@gmail.com
 www.aravecchia.weebly.com
 */
int t=250;

int LATCH = 2; 
int DATA = 3;
int CLOCK = 4;

long maximo = 512;
long maxim = (maximo>>1);
void setup()
{
  Serial.begin(9600);
  pinMode(LATCH, OUTPUT);
  pinMode(CLOCK, OUTPUT);
  pinMode(DATA, OUTPUT);
}

void loop()
{


  for (long x=1; x<maxim; x=x<<1)
  {
  digitalWrite(LATCH, LOW);
    // inicia a transmissao de DATA.
    for (int y=0;y<3;y++)
    {
    shiftOut(DATA, CLOCK, MSBFIRST, x);
    }
    Serial.print("x = ");
    Serial.print(x);
    Serial.print(" - "); 
    Serial.println(x, BIN);
    delay(t);
  digitalWrite(LATCH, HIGH);
  }

}







