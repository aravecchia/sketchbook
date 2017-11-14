#include <Arduino.h>

/*
  Este codigo faz a leitura de um sensor de corrente (optoacoplador)
  no pino 2, e por meio de um potenciometro em A0
  controla um Dimmer no pino 13.
/*
Desenvolvido por Alexandre Aravecchia
aravecchia@gmail.com
www.aravecchia.weebly.com
*/
  com apoio de www.labdegaragem.com.br
  Fique a vontade para baixar, usar e melhorar, mas nao esqueca de
  compartilhar!
  22 de junho de 2015.
*/
int sensor = A0;

int opto = 2;    // Pino de leitura do opto
int controle = 3;       // Pino ligado ao circuito do Triac
//este pino tem que disparar em [To+T/16] para que o motor tenha 7T/8 da potencia total

// Variables will change:
int optoState;       // Estado do opto. Se estiver HIGH, tensao diferente de zero.
//Se estiver em LOW, tensao = zero. Presisamente o que queremos.
int lastOptoState;     // O estado anterior do sensor.
long lastMillis;     //define a contagem do tempo.

int period;
int D;
int visor;

void setup()
{
  pinMode(opto, INPUT);  // inicializa o pino do opto de leitura como inpput
  pinMode(sensor, INPUT); //inicializa o pino do sensor analogico como input
  pinMode(controle, OUTPUT);  // inicializa o pino do MOC-3031 como output
  Serial.begin(9600);
}

void loop()
{
  digitalWrite(controle, LOW);
  optoState = digitalRead(opto);
  // compare the buttonState to its previous state
  if ((optoState != lastOptoState) && (optoState == 0))
  {
    D = map(analogRead(sensor), 0, 1023, 0, 8000); // o delay de controle
    float visor = float(map(analogRead(sensor), 0, 1023, 0, 100000)) / 1000;
    if (visor <= 5)
    {
      digitalWrite(controle, HIGH);
      Serial.print(5.00);
    }
    else if (visor > 90)
    {
      digitalWrite(controle, LOW);
      Serial.print(visor);
    }
    else
    {
      digitalWrite(controle, LOW);
      delayMicroseconds(D);
          digitalWrite(controle, HIGH);
      Serial.print(visor);
    }
    Serial.println(" %");

    lastOptoState = optoState;
    lastMillis = millis();
  }

  lastOptoState = optoState;
}
