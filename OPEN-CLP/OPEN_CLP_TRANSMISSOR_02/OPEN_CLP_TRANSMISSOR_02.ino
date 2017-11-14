#include <Arduino.h>

//simple Tx on pin D12
//Written By : Mohannad Rawashdeh
// 3:00pm , 13/6/2013
//http://www.genotronex.com/
//..................................
#include <VirtualWire.h>

int led = 13;
int red = 9;
int t = 1000;

void setup() {
  pinMode(led, OUTPUT);
  pinMode(red, OUTPUT);

  vw_set_ptt_inverted(true);
  vw_set_tx_pin(11);
  vw_setup(2000);// speed of data transfer Kbps
}
void loop()
{
 char * msg = "1" ;
  vw_send((uint8_t *)msg, strlen(msg));
  vw_wait_tx(); // Wait until the whole message is gone
  digitalWrite(led, 1);
  digitalWrite(red, 0);
  delay(2 * t);
  msg = "0" ;
  vw_send((uint8_t *)msg, strlen(msg));
  vw_wait_tx(); // Wait until the whole message is gone
  digitalWrite(13, 0);
  digitalWrite(red, 1);
  delay(2 * t);
}

