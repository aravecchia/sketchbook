#include <Arduino.h>

// CyberOhm Robotics
// https://cyberohm.com
// Apoio: Laboratorio de Garagem - https://www.labdegaragem.com
// Agradecimentos a valiosa ajuda dos amigos:
// Almir, Jonatas, Jucelei, Rogerio, Marcelo, Renyer, fredsant, Daniel (Oraculo X), Daniel (Pinguim Jedi), Pedro e Wiechert (O Destruidor).
// alem da tremenda paciencia da minha esposa pra me aguentar falando nisso dia e noite :D

int LATCH = 2; 
int DATA = 3;
int CLOCK = 4;
// define os pinos de latch, data e clock do 74HC595 que controlam o display da temperatura do ambiente
int a = 0;
int b = 0;
int c = 0;
int d = 0;
int e = 0;
int f = 0;
int g = 0;
int h = 0;
int matriz[] = {
  a, b, c, d, e, f, g, h};
int x;
int y;
int z;
int t=500;

void setup()
{
  Serial.begin(9600);
  pinMode(LATCH, OUTPUT);
  pinMode(CLOCK, OUTPUT);
  pinMode(DATA, OUTPUT);
  // Define LATCH, DATA e CLOCK como pinos de saida
}

void loop()
{
  matriz[0]=1;
  for (x=0; x<8; x++)
  {
    matriz[x]=1<<x;
      digitalWrite(LATCH, LOW);
    for (y=0; y<8; y++)
    {
      shiftOut(DATA, CLOCK, MSBFIRST, matriz[y]);
    }
    digitalWrite(LATCH, HIGH);
    delay(t);
  }
}


