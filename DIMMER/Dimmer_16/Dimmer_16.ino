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
int sensor = A0;
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

void setup()
{
  pinMode(opto, INPUT);  // inicializa o pino do opto de leitura como inpput
  pinMode(sensor, INPUT); //inicializa o pino do sensor analogico como input
  pinMode(triac, OUTPUT);  // inicializa o pino do MOC-3031 como output
  pinMode(led, OUTPUT);  // inicializa o pino do MOC-3031 como output
  Serial.begin(9600);

}

void loop()
{
  {
    digitalWrite(triac, LOW);
    optoState = digitalRead(opto);
    // compare the buttonState to its previous state
    if ((optoState != lastOptoState) && (optoState == HIGH))
    {
      leitura = float(analogRead(sensor));
      D = map(leitura, 0, 1023, 0, 8200); // o delay de controle
      float T = float (map(leitura, 0, 1023, 0, 100000)) / 1000;

      //    Rt = R0.[1 + At + Bt2]
      //  97000 = 100 * ((3.90802/1000)*273 + 40000*(273^2))
      //    R2 = (-1000 + sqrt(-100000100000) + (4*5/float(map(analogRead(sensor)), 0, 1023, 0, 5))))/2
      //    Tk = Tc + 273
      //    Tc = Tk - 273
      //    25C = 298K (97 KOhm)
      delayMicroseconds(D);
      digitalWrite(triac, HIGH);
      delayMicroseconds(200);
      digitalWrite(triac, LOW);
      Serial.print(T);
      Serial.print(" % - ");
      Serial.print(D);
      Serial.println(" ms - ");
      Serial.print(optoState);
    }
    lastOptoState = optoState;
  }
}
