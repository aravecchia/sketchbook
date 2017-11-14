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

const int entrada = 2;
const int LED = 13;
unsigned long valor = 0;
const int t=10;
const unsigned long BETA =  4000; //Calibrar este valor utilizando um termometro externo como comparacao
const unsigned long Ro = 100000; //Resistencia tpica de um termistor de 100k
const unsigned long To = 25+273; //Transforma temperatura de referencia do Termistor de Celsius para Kelvin


unsigned long pico; //Tempo 
unsigned long vale;
unsigned long periodo;
unsigned long periodoS;
unsigned long frequencia;

unsigned long Kelvin;
unsigned long Celsius = Kelvin-273;
unsigned long R; // Resistencia do Termistor
unsigned long R2 = 33000; //Segundo resistor do NE-222
unsigned long C1 = 10000000; // Capacitor principal em picoFaraday;

void setup()
{
  Serial.begin(9600);
  pinMode(entrada, INPUT_PULLUP);
  // pinMode(entrada, INPUT_PULLUP);
  // Use INPUT_PULLUP para utilizar o Arduino diretamente no NE-555
  //Se o circuito estiver instavel, 
  // tente usar Pull Up com pinMode(entrada, INPUT); normalmente.
  pinMode(LED, OUTPUT);

}
void loop()
{
  digitalWrite(LED, LOW);

  pico    = (pulseIn(entrada, HIGH));
  vale   = (pulseIn(entrada, LOW));
  periodo = (pico + vale); // periodo em microsegundos
  periodoS = periodo / 1000000; // periodo em segundos
  frequencia = (1 / periodo);

  R = (1.44*periodoS/C1) - (2*R2);

  Kelvin =  1 / ( (1/To)+((log(R/Ro))/BETA) ); // Calcula a temperatura por: Steinhart-Hart


  Celsius = Kelvin-273; // Convert Kelvin to Celsius

  if (periodo)
  {
    Serial.print("t1 = ");
    Serial.print(pico/1000);
    Serial.print(" ms - t2 =  ");
    Serial.print(vale/1000);
    Serial.print(" ms - Periodo = ");
    Serial.print(periodo);
    Serial.print(" ms - ");

    Serial.print("Freq = ");
    Serial.print(frequencia, 0);
    Serial.print(" Hz - ");
    digitalWrite(LED, HIGH);

    Serial.print("R = ");
    Serial.print(R);
    Serial.print(" Ohm - ");

    Serial.print("Temp = ");
    Serial.print(Celsius);
    Serial.println(" *C.");
    delay(t);
  }
}












