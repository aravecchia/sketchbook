#include <Arduino.h>

//Programa : Comunicacao com Modulo RF 433 - Emissor
//Autor : Arduino e Cia
#include <VirtualWire.h>
//Define pinos Led e Botao
int led = 13;
int red = 9;
int sensor = A0;

int t = 100;
int bps = 5000;

char  *msg;
boolean estado = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  pinMode(red, OUTPUT);
  //Pino ligado ao pino DATA do transmissor RF
  vw_set_tx_pin(4);
  //Velocidade de comunicacao (bits por segundo)
  vw_setup(bps);
}
void loop()
{
  digitalWrite(led, estado);
  digitalWrite(red, !estado);
  msg = "DOMINAR O MUNDO!!!";
  //Envio dos dados
  vw_send(( uint8_t *)msg, strlen(msg));
  //Aguarda envio dos dados
  vw_wait_tx();
  //Desliga o led da porta 13 ao final da transmissao
  digitalWrite(led, !estado);
  digitalWrite(red, estado);
  delay(t);
}

