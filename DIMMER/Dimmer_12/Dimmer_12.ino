#include <Arduino.h>

/*
  Este codigo faz a leitura de um sensor de corrente (optoacoplador)
  no pino 2, e por meio de um potenciometro em A0
  controla um Dimmer no pino 13.
/*Desenvolvido por Alexandre Aravecchia
  Projetista, desenvolvedor, programador
 aravecchia@gmail.com
 www.aravecchia.weebly.com
 */
  com apoio de www.labdegaragem.com.br
  Fique a vontade para baixar, usar e melhorar, mas nao esqueca de
  compartilhar!
  22 de junho de 2015.
*/
#define mudaopto1 ((optoState1 != lastoptoState1) && (optoState1 == HIGH))
#define mudaopto2 ((optoState2 != lastoptoState2) && (optoState2 == HIGH))
int sensor = A5;        //Potenciometro ou sensor analógico
int opto1 = 2;           // Pino de leitura do opto
int opto2 = 3;           // Pino de leitura do opto
int controle = 4;       // Pino ligado ao circuito do Triac


// Variables will change:
int optoState1;
int optoState2;
// Estado dos optos.
int lastoptoState1;     // O estado anterior do sensor.
int lastoptoState2;     // O estado anterior do sensor.
long lastMillis;     //define a contagem do tempo.
float period;
float frequency;

void setup()
{
  pinMode(opto1, INPUT);  // inicializa o pino do opto de leitura como inpput
  pinMode(opto2, INPUT);  // inicializa o pino do opto de leitura como inpput
  pinMode(sensor, INPUT); //inicializa o pino do sensor analogico como input
  pinMode(controle, OUTPUT);  // inicializa o pino do MOC-3031 como output
  Serial.begin(9600);
}

void loop()
{
  digitalWrite(controle, HIGH);
  optoState1 = digitalRead(opto1);
  optoState2 = digitalRead(opto2);

  // compare the buttonState to its previous state
  if ((mudaopto1 == 1) || (mudaopto2 == 1))
{
  int D = map(analogRead(sensor), 0, 1023, 0, 8); // o delay de controle

    period = millis() - lastMillis;
    digitalWrite(controle, LOW);

    delay(D);
    digitalWrite(controle, HIGH);

    lastMillis = millis();
    if (mudaopto1 == 1)
    {
      lastoptoState1 = optoState1;
    }
    if (mudaopto2 == 1)
    {
      lastoptoState2 = optoState2;
    }
  }
}
