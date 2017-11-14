#include <Arduino.h>

/*
* EZ1Rangefinder Distance Sensor
 * prints distance and changes LED flash rate
 * depending on distance from the Ping))) sensor
 */
const int sensorPin = 2;
long value = 0;

void setup()
{
  Serial.begin(9600);
}
void loop()
{
  value = pulseIn(sensorPin, HIGH)/1000 ;
  Serial.print(value);
    Serial.println(" ms");
  delay(10);
}


