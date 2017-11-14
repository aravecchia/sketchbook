#include <Arduino.h>
/*Desenvolvido por Alexandre Aravecchia
  Projetista, desenvolvedor, programador
 aravecchia@gmail.com
 www.aravecchia.weebly.com
 */

int LATCH = 2; 
int DATA = 3;
int CLOCK = 4;
long maximo = 65536;
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
  long t=100;
  // Tempo de delay.
  for (long x=1; x<maximo; x=x<<1)
  {
    digitalWrite(LATCH, LOW);
    // inicia a transmissao de DATA.
    shiftOut(DATA, CLOCK, MSBFIRST, x);
    digitalWrite(LATCH, HIGH);
    Serial.print("x = ");
    Serial.print(x);
    Serial.print(" - "); 
    Serial.println(x, BIN);
    if ((x==0)||(x==maximo))
    {
      delay(2*t);
    }
    else
    {
      delay(t);
    }
  }
  for (long x=maxim; x>1; x=x>>1)
  {
    digitalWrite(LATCH, LOW);
    // inicia a transmissao de DATA.
    shiftOut(DATA, CLOCK, MSBFIRST, x);
    digitalWrite(LATCH, HIGH);
    Serial.print("x = ");
    Serial.print(x);
    Serial.print(" - "); 
    Serial.println(x, BIN);
    delay(t);
  }
}






