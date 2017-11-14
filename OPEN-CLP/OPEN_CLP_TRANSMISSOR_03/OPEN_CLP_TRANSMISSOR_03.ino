#include <Arduino.h>

//Programa : Comunicacao com Modulo RF 433 - Emissor
//Autor : Arduino e Cia
#include <VirtualWire.h>
//Define pinos Led e Botao
const int led = 13;
int red = 9;
int t=1000;
int valor_botao;
char Valor_CharMsg[4];
//Armazena estado led = ligar/desligar
int estado = 0;

void setup()
{
Serial.begin(9600);
pinMode(led,OUTPUT);
pinMode(red,OUTPUT);
//Pino ligado ao pino DATA do transmissor RF
vw_set_tx_pin(4);
//Velocidade de comunicacao (bits por segundo)
vw_setup(1000);
Serial.println("Trasmissao modulo RF - Acione o botao...");
}
void loop()
{
//Altera o estado do led
estado = !estado;
//Converte valor para envio
itoa(estado,Valor_CharMsg,10);
//Liga o led da porta 13 para indicar envio dos dados
digitalWrite(led, estado);
digitalWrite(red, !estado);
//Envio dos dados
vw_send(( uint8_t *)Valor_CharMsg, strlen(Valor_CharMsg));
//Aguarda envio dos dados
vw_wait_tx();
//Desliga o led da porta 13 ao final da transmissao
digitalWrite(led, !estado);
digitalWrite(red, estado);
Serial.print("Valor enviado: ");
Serial.println(Valor_CharMsg);
delay(t);
}

