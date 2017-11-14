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
  // Tempo de delay.
  //AQUI O PULO DO GATO: 
  // Ligar o Arduino ao primeiro HC595 (j) e este nas linhas de leds (cada porta a uma linha de 8 leds ligados em paralelo)
  //Ligar o segundo HC595 nas colunas dos negativos dos leds. Cada porta aciona a base de um transistor, que aciona o negativo
  //  de um conjunto de 8 leds. Cada conjunto de 8 leds esta ligado a 1 das 8 portas do primeiro HC595. CUIDADO!!! Veja meus esquemas feitos em Proteus.
  // Voce esta fazendo N portas AND, sendo q A aciona o positivo e B aciona o negativo (base do transistor aciona a ligacao do led ao seu negativo) de cada led.

  //  (i) controla o negativo de cada conjunto de 8 leds
  //  (j) controla os leds de todos os conjuntos.
  // Assim, para mandar o Byte 01010101 para 5o. conjunto, mandamos 0001000 para o primeiro HC595 (i)
  // e 01010101 para o segundo (j).
  // Assim todos os conjuntos de leds recebem o byte 01010101, mas como apenas o 5o. recebe um bit positivo (acionando o negativo dos leds),
  // apenas o 5o. vai ligar os leds.
  //  (i) AND (j) = controle de cada led

  for (int a=1; a<256; a=(a<<1))
    // inicia a contagem dos conjuntos.
    // Todos os leds podem estar acesos, mas apenas acenderao os leds do conjunto que estiver ativado.
    // Ativa o primeiro conjunto, depois o segundo e assim por diante.

  {
    for (int b=1; b<256; b=(b<<1)) // inicia a contagem dos leds. 
      for (int c=1; c<256; c=(c<<1)) // inicia a contagem dos leds. 
      {
        for (int d=1; d<256; d=(d<<1)) // inicia a contagem dos leds. 
        {
          for (int e=1; e<256; e=(e<<1)) // inicia a contagem dos leds. 
          {
            for (int f=1; f<256; f=(f<<1)) // inicia a contagem dos leds. 
            {
              for (int g=1; g<256; g=(g<<1)) // inicia a contagem dos leds. 
              {
                for (int h=1; h<256; h=(h<<1)) // inicia a contagem dos leds. 
                {
                  {
                    digitalWrite(LATCH, LOW);
                    shiftOut(DATA, CLOCK, MSBFIRST, a);
                    shiftOut(DATA, CLOCK, MSBFIRST, b);
                    shiftOut(DATA, CLOCK, MSBFIRST, c);
                    shiftOut(DATA, CLOCK, MSBFIRST, d);
                    shiftOut(DATA, CLOCK, MSBFIRST, e);
                    shiftOut(DATA, CLOCK, MSBFIRST, f);
                    shiftOut(DATA, CLOCK, MSBFIRST, g);
                    shiftOut(DATA, CLOCK, MSBFIRST, h);
                    digitalWrite(LATCH, HIGH);
                   // Serial.print("i= ");
                   // Serial.print(i, BIN);
                   // Serial.print(" - j= ");
                    //Serial.println(j, BIN);
                    delay(t);
                  }
                }
              }
            }
          }
        }
      }
  }
}







