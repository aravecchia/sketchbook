#include <Arduino.h>

int entrada = A0;
int delta1;
int delta2;
int periodo;
long frequencia;
 
void setup()
{  
  Serial.begin(9600);
  pinMode(entrada, INPUT);
}
 
int TA_LENDO_O_SINAL = 0;
 
void loop()
{
 
  int tensao = analogRead(entrada);
 
  if ( !TA_LENDO_O_SINAL && !tensao )
  {
    /// Inicia leitura - primeira passagem em 0
    TA_LENDO_O_SINAL = 1;
    delta1 = millis();
  }
  else if ( !tensao )
  {
    /// Finaliza leitura - segunda passagem em 0
    delta2 = millis();
    periodo=(delta2-delta1);
    frequencia=2/periodo;
    Serial.println(frequencia);
    TA_LENDO_O_SINAL = 0;
  }
 
}
