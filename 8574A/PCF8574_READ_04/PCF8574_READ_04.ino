#include <Wire.h>
int t = 100;
int x=1;
int bus = 56;
//---------------------------
void setup()
{
  Wire.begin();
  Serial.begin(9600);
}
//---------------------------
void loop()
{
    for (x = 1; x < 129; x=x<<1)
    {
      // Se PCF8574A mude 38 para 56
      Wire.beginTransmission(bus);                   // Begin the transmission to PCF8574
      Wire.write(0);                                  // Zera as portas
      Wire.endTransmission();                         // End the Transmission
      Wire.beginTransmission(bus);                   // Begin the transmission to PCF8574
      Wire.write(x);                               // Liga todas portas
      Wire.endTransmission();                         // End the Transmission
      Serial.println(x);
      delay(t);                                    // Delay 1 seg
    }
     for (x = 64; x > 1; x=x>>1)
    {
      // Se PCF8574A mude 38 para 20
      Wire.beginTransmission(bus);                   // Begin the transmission to PCF8574
      Wire.write(0);                                  // Zera as portas
      Wire.endTransmission();                         // End the Transmission
      Wire.beginTransmission(bus);                   // Begin the transmission to PCF8574
      Wire.write(x);                               // Liga todas portas
      Wire.endTransmission();                         // End the Transmission
      Serial.println(x);
      delay(t);                                    // Delay 1 seg
    }

}
