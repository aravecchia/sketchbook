#include <Wire.h>

void setup()
{
  Wire.begin();
  Serial.begin(9600);
}
void loop()
{
  for (int y = 30; y < 64; y++)
  {
    Wire.requestFrom(y, 1);
    //Se PCF8574A - mude de 33 para 57
    if (Wire.available())
      //If the request is available
    {
      int x = Wire.read();
      //Receive the data
      Serial.print(y);
      Serial.print(" - ");
      Serial.println(x);
    }
    else
    {
      Serial.print(y);
      Serial.print(" Falhou ");
    }
  }
}

