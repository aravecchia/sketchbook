#include <Arduino.h>

#include <VirtualWire.h>

void setup()
{
  Serial.begin(9600); // Debugging only
  Serial.println("setup");
  pinMode(8, OUTPUT);
pinMode(9, OUTPUT);
pinMode(13, OUTPUT);
  vw_set_ptt_inverted(true); // Required for DR3100
  vw_setup(2000);
  // Bits per sec
  vw_rx_start();
  // Start the receiver PLL running
}

void loop ()
{
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;
  if (vw_get_message(buf, & buflen)) // Non-blocking
  {
    int i;
    digitalWrite(13, LOW); // Flash a light to show received good message
        digitalWrite(8, HIGH); // Flash a light to show received good message
    // Message with a good checksum received, dump it.
    Serial.print("Got: ");
    for (i = 0; i < buflen; i ++ )
    {
      Serial.print(char(buf[i]));
      Serial.print(" - ");
    Serial.println(buf[i]);
    digitalWrite(8, LOW);
   digitalWrite(13, HIGH);
    }
  }
  else
  {
    digitalWrite(13, HIGH); // Flash a light to show received good message
        digitalWrite(9, LOW); // Flash a light to show received good message
        Serial.println("Nada!!!");
}
}


