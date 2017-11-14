#include <Arduino.h>

// Programa que conta os "meio­ciclos" da onda senoidal fornecida
//concessionária de energia elétrica.

// Variável que armazena os pulsos. Como será chamada dentro da roti
// ContaPulsos(), que é uma rotina de interrupção,
// tem que ter o comando volatile.

volatile unsigned int pulsos = 0;
const int opto = 2;
const int controle = 3;
const int sensor = A0;
int optoState;       // Estado do opto. Se estiver HIGH, tensao diferente de zero.
//Se estiver em LOW, tensao = zero. Presisamente o que queremos.
int lastOptoState;     // O estado anterior do sensor.

// Rotina que é chamada a cada meio ciclo
void Pulso()
{
  int T = (map(analogRead(sensor), 0, 1023, 0, 8));
  int visor = (map(analogRead(sensor), 0, 1023, 0, 100));
  optoState = digitalRead(opto);
  if ((optoState != lastOptoState))
  {
    T = map(analogRead(sensor), 0, 1023, 0, 16); // o delay de controle
    visor = map(analogRead(sensor), 0, 1023, 0, 100);
    if (visor != 0)
    {
      digitalWrite(controle, LOW);
      delay(T);
      digitalWrite(controle, HIGH);
    }
    else
    {
      digitalWrite(controle, HIGH);
    }
    Serial.print(visor);
    Serial.println(" %");

  }
  lastOptoState = optoState;
}

void setup()
{
  Serial.begin(9600);

  attachInterrupt(0, Pulso, CHANGE);
  pinMode(opto, INPUT);
  pinMode(controle, OUTPUT);

}

void loop()
{
  digitalWrite(controle, 1);


}

