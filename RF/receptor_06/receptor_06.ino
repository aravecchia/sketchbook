#include <Arduino.h>

//simple Tx on pin D12
//Written By : Mohannad Rawashdeh
// 3:00pm , 13/6/2013
//http://www.genotronex.com/
//..................................
#include <VirtualWire.h>

int led=13;
//int red=9;
int t=100;

void setup()
{
  vw_set_ptt_inverted(true); // Required for DR3100
  vw_set_rx_pin(12);
  vw_setup(4000); // Bits per sec
  pinMode(led, OUTPUT);
//  pinMode(red, OUTPUT);
  vw_rx_start(); // Start the receiver PLL running
}
void loop()
{
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;
  if (vw_get_message(buf, &buflen)) // Non­blocking
  {
    if ((buf[0] == 'B') && (buf[1] == '1')) {
      digitalWrite(led, 1);
    }
  }
  else {
    digitalWrite(led, 0);
//    digitalWrite(red, 1);
    delay(t);
 //   digitalWrite(red, 0);
 //   delay(t);
  }
}

