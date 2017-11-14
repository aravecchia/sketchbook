#include <Arduino.h>

const int entrada = A0;
  long Tzero = 0; // will store last time LED was updated
//const int timeout = 2000000;   // um segundo

void setup()
{  
  Serial.begin(9600);

}

void loop()
{

int T = millis();

long  frequencia = (1000000/T);
int onda = analogRead(entrada);
  if(onda = 0)
  {
    T = T - Tzero;
// save the last time you blinked the LED 
    Serial.print("T: ");
    Serial.print(T);
    Serial.print(" us - ");

    Serial.print("Freq: ");
    Serial.print(frequencia);
    Serial.println(" Hz");
  }
}
