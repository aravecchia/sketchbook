#include <Arduino.h>

/*
  Este codigo faz a leitura de um sensor de corrente (optoacoplador)
  no pino 2, e por meio de um potenciometro em A0
  controla um Dimmer no pino 13.
  Desenvolvido por https://cyberohm.com
  com apoio de www.labdegaragem.com.br

  Fique a vontade para baixar, usar e melhorar, mas nao esqueca de
  compartilhar!
  21 de maio de 2016.
*/

//Constantes
const int sensor = A0;        //Potenciometro ou sensor analógico
const int opto = 2;           // Pino de leitura do opto
const int controle = 3;       // Pino ligado ao circuito do Triac
const int led = 13;

// Variaveis:
int optoState;        //define o estado do opto
boolean semiciclo;

long lastMillis;     //define a contagem do tempo.
float period;
float frequency;

void setup()
{
  pinMode(opto, INPUT);  // inicializa o pino do opto de leitura como inpput
  pinMode(sensor, INPUT); //inicializa o pino do sensor analogico como input
  pinMode(controle, OUTPUT);  // inicializa o pino do MOC-3031 como output
  pinMode(led, OUTPUT);  // inicializa o pino do MOC-3031 como output
  Serial.begin(9600);
}

void loop()
{

  digitalWrite(controle, HIGH);
  optoState = digitalRead(opto);
  if (optoState == 0)
  {
    period = millis() - lastMillis;
    semiciclo = 0;
  }
  else
  {
    semiciclo = 1;
    Serial.print(optoState);
    Serial.print(" - ");
    Serial.println(period);
    lastMillis = millis();
  }
}
/*
  digitalWrite(controle, HIGH);
  optoState = digitalRead(opto);
  if (optoState == !semiciclo)
  {
  period = millis() - lastMillis;
  int D = map(analogRead(sensor), 0, 1023, 0, period); // o delay de controle
  digitalWrite(controle, LOW);
  delay(D / 2);
  digitalWrite(controle, HIGH);
  Serial.println(semiciclo);
  lastMillis = millis();
  }
  semiciclo = !semiciclo;
  }
*/
