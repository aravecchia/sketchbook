#include <Arduino.h>

/*Desenvolvido por Alexandre Aravecchia
  Projetista, desenvolvedor, programador
 aravecchia@gmail.com
 www.aravecchia.weebly.com
 */
// Apoio: Laboratorio de Garagem - labdegaragem.com
// Agradecimentos a valiosa ajuda dos amigos:
// Almir, Jonatas, Jucelei, Rogerio, Marcelo, Renyer, fredsant, (o cara daquele site de mecatronica, esqueci os dois nomes) (esqueci alguem???)
// alem da tremenda paciencia da minha esposa pra me aguentar falando nisso dia e noite :D

int LATCH = 2; 
int DATA = 3;
int CLOCK = 4;
int t=50;
// define os pinos de latch, data e clock do 74HC595 que controla o display da temperatura do ambiente
int a = 0;
int b = 0;
int c = 0;
int d = 0;
int e = 0;
int f = 0;
int g = 0;
int h = 0;

int matriz[]={
  a, b, c, d, e, f, g, h};
int x;

void setup()
{
  Serial.begin(9600);
  pinMode(LATCH, OUTPUT);
  pinMode(CLOCK, OUTPUT);
  pinMode(DATA, OUTPUT);
}

void loop()
{
  for (int x=0; x<8; x++)
  {
    for (matriz[x]=1; matriz[x]<256; matriz[x]=(matriz[x])<<1)
       {
      digitalWrite(LATCH, LOW);
      for (int y=0; y<8; y++)
      {
        shiftOut(DATA, CLOCK, MSBFIRST, matriz[y]);
      }
      digitalWrite(LATCH, HIGH);
      delay(t);
    }
  }
}















