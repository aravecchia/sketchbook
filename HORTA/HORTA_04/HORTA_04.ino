/*
PROTOCOLO NE-555
 Leitura de sensores a distancia do Arduino
 com ligacao por meio de fios
 _____________________________
 Desenvolvido por Alexandre Aravecchia
 a.k.a. O Tio do Computador
 Projetista, desenvolvedor, programador
 http://tiodocomputador.tumblr.com/
 Com o apoio de http://labdegaragem.com.br/
 Publicado no Labdegaragem em 10/outubro/2016.
 */

#include <math.h>
#include <Arduino.h>

int entrada = 2;
int LED = 13;

const int t=10;

unsigned long BETA =  4000; //Calibrar este valor utilizando um termometro externo como comparacao
unsigned long Ro = 100000; //Resistencia tpica de um termistor de 100k
unsigned long To = 25+273; //Transforma temperatura de referencia do Termistor de Celsius para Kelvin

unsigned long pico; //Tempo 
unsigned long vale;
unsigned long Periodo;
unsigned long Frequencia;

unsigned long Kelvin;
unsigned long Celsius = Kelvin-273;
unsigned long R; // Resistencia do Termistor
unsigned long R2 = 10000; //Segundo resistor do NE-222
unsigned long C1 = 10000000; // Capacitor principal em microFaraday;


void setup()
{
  Serial.begin(9600);
  pinMode(entrada, INPUT);
  pinMode(LED, OUTPUT);
}
void loop()
{
  digitalWrite(LED, LOW);
  delay(t);
  
  pico = pulseIn(entrada, HIGH);
  vale = pulseIn(entrada, LOW);
  Periodo = pico + vale;
  Frequencia = 1000000/Periodo;

  R = ((1.44*Periodo)/C1)-(2*R2);

  Kelvin =  1 / ( (1/To)+((log(R/Ro))/BETA) ); // Calcula a temperatura por: Steinhart-Hart

  Celsius = Kelvin-273; // Convert Kelvin to Celsius

  if (Periodo)
  {
    Serial.print(vale);
    Serial.print("us - ");
    Serial.print(pico);
    Serial.print("us - Periodo = ");
    Serial.print(Periodo/1000);
    Serial.print(" ms - ");

    Serial.print("Freq=");
    Serial.print(Frequencia);
    Serial.print(" Hz - ");

    Serial.print("R=");
    Serial.print(R/1000);
    Serial.print(" K Ohm - ");

    Serial.print("Temp = ");
    Serial.print(Celsius);
    Serial.println(" *C.");
  }
  else
  {
  Serial.println("Aguardando sinal...");
  delay(t);
  }
  digitalWrite(LED, HIGH);
  delay(t);
}




