/*
Desenvolvido por Alexandre Aravecchia
aravecchia@gmail.com
www.aravecchia.weebly.com
*/

#include <Arduino.h>

int x=1;
// Escova um bit de 1 a 10000000 e de novo ate 1 usando bitwise, piscando o LED 13 a cada escovada
// Compile no Arduino normalmente como se fosse um Blink,
// e aperte Ctrl Shift M para ver a saida na serial.
// Observe o bit se deslocando.
// Mude a variavel t para alterar a velocidade.

//tiodocomputador@gmail.com

int led = 13;
int t = 100;

void setup() 
{
  Serial.begin(9600); 
  pinMode(led, OUTPUT);
}

void loop()
{
  digitalWrite(led, LOW);
  delay(t);
  for (int x=1; x<256; x=x<<1)
  {
    Serial.print("x = " );                       
    Serial.println(x, BIN); 
    delay(t);  
  }  
  digitalWrite(led, HIGH);
  delay(t);
    digitalWrite(led, LOW);
  for (int x=256; x>0; x=x>>1)
  {
    Serial.print("x = " );                       
    Serial.println(x, BIN); 
    delay(t);  
  }    
}

