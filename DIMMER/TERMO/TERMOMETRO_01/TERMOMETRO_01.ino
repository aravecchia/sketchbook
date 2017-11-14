#include <Arduino.h>

float leitura;


float Vcc = 4.83; // Para Garagino ligado à USB
float R1 = 99500; // Para 3 resistores 33.2K + resistencia do fio
float R2 = 100000; // Para resistor Sethi3D a zero graus
float zero = (R2*Vcc) / ( R1+R2);

float temperatura;
int t = 100;

 int sensor = A0;
 int pwmled = 9;
 int brilho;

 
void setup() 
{
 pinMode(sensor, INPUT);
 Serial.begin(9600);
}

void loop()
{
leitura = float(analogRead(sensor));
temperatura = (5*leitura/1023);
analogWrite(pwmled, brilho);
Serial.print("Tensao = ");
Serial.print(temperatura);
Serial.println(" Volts - ");
delay(t);
}
