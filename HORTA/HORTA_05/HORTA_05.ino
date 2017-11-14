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

const int t = 100;

int BETA =  4500; //Calibrar este valor utilizando um termometro externo como comparacao
float Ro = 100000; //Resistencia tipica de um termistor de 100k
float To = 25 + 273; //Transforma temperatura de referencia do Termistor de Celsius para Kelvin

float pico; //Tempo
float picoanterior;
float vale;
float valeanterior;
float Periodo;
float Frequencia;

float Kelvin;
float Celsius = Kelvin - 273;
float media;

float R; // Resistencia do Termistor
float R2 = 10000; //Segundo resistor do NE-222
int C1 = 1; // Capacitor principal em MICROFARADAY;


void setup()
{
  Serial.begin(9600);
  pinMode(entrada, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
}

void loop()
{
  digitalWrite(LED, LOW);
  delay(t);
  {
    pico = pulseIn(entrada, HIGH);
    vale = pulseIn(entrada, LOW);
    Periodo = (pico + vale);
    Frequencia = 1000000 / Periodo;

    R = 220+((1.44 * Periodo) / C1) - (2 * R2);

    // Kelvin =  1 / ( (1/To) + ((log(R/Ro)/ BETA)) ); // Calcula a temperatura por Steinhart-Hart
    Kelvin = 1 / ( (1 / To) + ((log(R / Ro) / BETA)));
    //Kelvin = 1/To;

    Celsius = Kelvin - 273.15; // Convert Kelvin to Celsius
    //if ((R >= 0) && (vale > 0.9 * valeanterior) && (vale < 1.1 * valeanterior) && (pico > 0.9 * picoanterior) && (pico < 1.1 * picoanterior))
    {
      {
        Serial.print(vale / 1000, 3);
        Serial.print(" ms - ");
        Serial.print(pico / 1000, 3);
        Serial.print(" ms - Periodo = ");
        Serial.print(Periodo / 1000, 3);
        Serial.print(" ms - ");

        Serial.print(" Freq = ");
        Serial.print(Frequencia, 3);
        Serial.print(" Hz - ");

        Serial.print("R = ");
        Serial.print(R / 1000);
        Serial.print(" K Ohm - ");

        Serial.print("Temp = ");
        Serial.print(Celsius, 2);
        Serial.println(" *C.");
      }
    }
    picoanterior = pico;
    valeanterior = vale;
    delay(t);
  }
}
