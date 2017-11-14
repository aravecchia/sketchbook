#include <Arduino.h>

//Programa : Comunicacao com Modulo RF 433 - Emissor
//Autor : CyberOhm Robotics
// tiodocomputador@gmail.com

#include <VirtualWire.h>

int green = 13;
int red = 9;
int sensor = A0;
int leitura;
int valor;
int texto;
int comprimento;

int rf = 4;
char *msg;

int t = 250;
int bps = 5000;

boolean estado = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(green, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(sensor, INPUT);

  //Pino ligado ao pino DATA do transmissor RF
  vw_set_tx_pin(rf);
  //Velocidade de comunicacao (bits por segundo)
  vw_setup(bps);
}

void loop()
{
  leitura = analogRead(sensor);
  digitalWrite(green, estado);
  digitalWrite(red, !estado);
  delay(t);

  //msg = "DOMINAR O MUNDO";
  valor = map(leitura, 0, 1023, 0, 127);

  Serial.print(leitura);
  Serial.print(" - ");
  texto = char(valor);
   Serial.println(texto);

  msg = "DOMINAR O MUNDO";
  //Envio dos dados
  vw_send(( uint8_t *)&texto, 10);
  //Aguarda envio dos dados
  vw_wait_tx();

  //Desliga o led da porta 13 ao final da transmissao
  digitalWrite(green, !estado);
  digitalWrite(red, estado);
  delay(t);
}
