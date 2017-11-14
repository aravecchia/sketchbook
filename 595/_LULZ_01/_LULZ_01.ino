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
int s1;
int s2;
int s3;
int s4;
int s5;
int s6;
int s7;
int s8;

int matriz[] = {
  s1, s2, s3, s4, s5, s6, s7, s8};

int led;
int x;
int y;

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
  int t=100;
  for (led=1; led<256; led=led<<1)
  {
    for (x=0; x<8; x++)
    {    
      digitalWrite(LATCH, LOW);
      for (y=0; y<8; y++)
      {
        if(x==y)
        {
          matriz[y]=led;
        }
        else
        {
          matriz[y]=0;
        }
        shiftOut(DATA, CLOCK, MSBFIRST, matriz[y]);
      }
      digitalWrite(LATCH, HIGH);
      delay(t);
    }
  }
}
