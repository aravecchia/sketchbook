#include <Arduino.h>

/*
  CLP para máquina de termoformagem a vácuo.
  Desenvolvido por https://cyberohm.com
  com apoio de www.labdegaragem.com.br
  Agradecimentos a Rui Viana, Wiechert, Celso Ito, Guilherme Razgriz e Rafael Maciel.
  Fique a vontade para baixar, usar, melhorar e compartilhar!
  1 de junho de 2016.
*/
#include <math.h>
#include <Thermistor.h>

Thermistor temp(0);
int sensor = A2;
int opto = 2;    // Pino de leitura do opto
int triac = 5;       // Pino ligado ao circuito do Triac
//este pino tem que disparar em [To+T/16] para que o motor tenha 7T/8 da potencia total
int led = 13;

// Variables will change:
int optoState;       // Estado do opto. Se estiver HIGH, tensao diferente de zero.
//Se estiver em LOW, tensao = zero. Presisamente o que queremos.
int lastOptoState;     // O estado anterior do sensor.
//long lastMillis;     //define a contagem do tempo.

int leitura;
int D;
int visor;
int t=200;

void setup()
{
  pinMode(opto, INPUT);  // inicializa o pino do opto de leitura como inpput
  pinMode(sensor, INPUT); //inicializa o pino do sensor analogico como input
  pinMode(triac, OUTPUT);  // inicializa o pino do MOC-3031 como output
  pinMode(led, OUTPUT);  // inicializa o pino do MOC-3031 como output
  Serial.begin(9600);

 attachInterrupt(0, cut, RISING); // Interrupção no pino 2(0) ou 3(1)
  // RISING FALLING CHANGE
}

void cut()
{
//  temperatura = temp.getTemp();
//  while ((TEMP[selecao]) > temperatura)
  {
      leitura = float(analogRead(sensor));
      D = map(leitura, 0, 1023, 0, 8200); // o delay de controle
    delayMicroseconds(D);
    digitalWrite(triac, HIGH);
    delayMicroseconds(t);
    digitalWrite(triac, LOW);
  }
}



void loop()
{
  {
    
  }
}
