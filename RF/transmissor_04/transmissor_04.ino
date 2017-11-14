#include <Arduino.h>

#include <VirtualWire.h>
void setup()
{
  Serial.begin(9600); // Debugging only
  Serial.println("setup");
  // Initialise the IO and ISR
  vw_set_ptt_inverted(true); // Required for DR3100
  vw_setup(2000);
  // Bits per sec
  for (int pino=22; pino<38; pino++)
  {
    pinMode(pino, OUTPUT);
  }
}

void loop()
{
  int x;
  const char * matriz[] = {
    "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "*", "#",  };
  for (x=0; x<16; x++)
  {
    const char * msg = matriz[x];
    digitalWrite(13, true); // Flash a light to show transmitting
    vw_send(( uint8_t * )msg, strlen(msg));
    vw_wait_tx(); // Wait until the whole message is gone
    digitalWrite(13, false);
    Serial.print("Mandei a string: ");
    Serial.print(x);
    Serial.print(": ");
    Serial.println(matriz[x]);
    delay(200);
  }
}
/*

 
 
 //Programa : Módulo RF Transmissor com Arduino Uno
 //Autor : FILIPEFLOP - Arduino e Cia
 #include <VirtualWire.h>
 #define Led 13
 String mensagem;
 void setup()
 {
 Serial.begin(9600);
 vw_set_tx_pin(4); //Define o pino 8 do Arduino como
 //o pino de dados do transmissor
 vw_setup(2000); // Bits per sec
 pinMode(Led, OUTPUT);
 }
 void loop()
 {
 digitalWrite(Led, LOW);
 char data[30];
 int numero;
 if (Serial.available() > 0)
 {
 numero = Serial.readBytesUntil (13,data,20);
 data[numero] = 0;
 Serial.print("Enviado : ");
 Serial.print(data);
 Serial.print(" - Caracteres : ");
 Serial.println(strlen(data));
 send(data); //Envia a mensagem para a rotina que
 //envia os dados via RF
 digitalWrite(Led, HIGH);
 delay(10);
 } 
 }
 void send (char *message)
 {
 vw_send((uint8_t *)message, strlen(message));
 vw_wait_tx(); // Aguarda o envio de dados
 }
 
 */

