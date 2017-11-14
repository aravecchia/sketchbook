#include <Arduino.h>

// Programa que conta os "meio­ciclos" da onda senoidal fornecida
//concessionária de energia elétrica.

// Variável que armazena os pulsos. Como será chamada dentro da roti
// ContaPulsos(), que é uma rotina de interrupção,
// tem que ter o comando volatile.

volatile unsigned int pulsos = 0;
const int led = 13;

// Rotina que é chamada a cada meio ciclo, incrementando a variável
void ContaPulso()
{
  pulsos++;
}

void setup()
{
  Serial.begin(9600);
  // Essa instrução faz com que, a cada vez que o pino 2 passa muda de
  // (RISING), a rotina ContaPulso() é chamada. O número 0 define o
  // pino número 1 define o pino 3.
  attachInterrupt(0, ContaPulso, CHANGE);
  pinMode(2, INPUT);
  pinMode(led, OUTPUT);
  
}

void loop()
{
  volatile unsigned long t = millis();
  // Espera um segundo...
  digitalWrite(led, 0);
  while ((millis() - t) <= 1000)
  {
    Serial.println(digitalRead(2));
      }
  // Durante a espera, a interrupção ocorre a cada vez que o pino 2 muda de
  // zero para 5V. Como isso acontece a cada meio ciclo, após um segundo
  // a variável pulsos vai conter o valor 120, que será impresso repetidas
  // vezes.
 // Serial.print(pulsos);
// Serial.println(" Hz");
  pulsos = 0;
  digitalWrite(led, 1);
  // Zera a variável para contar os pulsos do próximo ciclo.
}

