#include <Arduino.h>

const int entrada = 2;
//const int timeout = 2000000;   // um segundo
const int LED = 13;
const int t=500;

void setup()
{
  Serial.begin(9600);
    pinMode(entrada, INPUT);
 // pinMode(entrada, INPUT_PULLUP);
  // Use INPUT_PULLUP para utilizar o Arduino diretamente no NE-555
  //Se o circuito estiver instavel, 
  // tente usar Pull Up com pinMode(entrada, INPUT); normalmente.
  pinMode(LED, OUTPUT);
}

void loop()
{
  digitalWrite(LED, LOW);

  unsigned long pico  = 0;
  unsigned long vale = 0;
  float periodo = 0;
  float frequencia = 0;

  pico    = (pulseIn(entrada, HIGH));
  vale   = (pulseIn(entrada, LOW));
  periodo = (pico + vale);
  frequencia = (1000000 / periodo);

  if (periodo)
  {
    Serial.print("T: ");
    Serial.print(periodo);
    Serial.print(" us - ");

    Serial.print("Freq: ");
    Serial.print(frequencia, 0);
    Serial.println(" Hz");
      digitalWrite(LED, HIGH);
    delay(t);
  }
}
