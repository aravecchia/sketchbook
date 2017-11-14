#include <Arduino.h>

//Programa : Comunicacao com Modulo RF 433 - Emissor
//Autor : Arduino e Cia
#include <VirtualWire.h>
//Define pinos Led e Botao
int led = 13;
int red = 9;
int sensor = A0;
int valor_sensor;
char *string_sensor;

int t=250;
int bps=5000;

//char *msg;
boolean estado = 0;

void setup()
{
Serial.begin(9600);
pinMode(led,OUTPUT);
pinMode(red,OUTPUT);
pinMode(sensor,INPUT);
//Pino ligado ao pino DATA do transmissor RF
vw_set_tx_pin(4);
//Velocidade de comunicacao (bits por segundo)
vw_setup(bps);
}
void loop()
{
digitalWrite(led, estado);
digitalWrite(red, !estado);
//valor_sensor = map(analogRead(sensor), 0, 1023, 0, 100);
valor_sensor = (analogRead(sensor));
Serial.println(analogRead(sensor), DEC);
itoa(valor_sensor, string_sensor, 10); //int to ascii
//Envio dos dados
Serial.println(valor_sensor);
vw_send(( uint8_t *)string_sensor, strlen(string_sensor));
//Aguarda envio dos dados
vw_wait_tx();
//Desliga o led da porta 13 ao final da transmissao
digitalWrite(led, !estado);
digitalWrite(red, estado);
delay(t);
digitalWrite(led, !estado);
digitalWrite(red, estado);
delay(t);
}

