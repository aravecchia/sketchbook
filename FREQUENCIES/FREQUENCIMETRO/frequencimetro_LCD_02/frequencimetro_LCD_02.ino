
// Desenvolvido por Alexandre Aravecchia
// a.k.a. O Tio do Computador
//http://tiodocomputador.tumblr.com/
// Com o apoio de http://labdegaragem.com/
//Publicado no Labdegaragem em 10/outubro/2016.


#include <LiquidCrystal.h> //Inclui a biblioteca do LCD
#include <math.h>
#include <Arduino.h>
//LiquidCrystal lcd(12,11,5,4,3,2);
//LiquidCrystal lcd(7, 9, 10, 11, 12, 13);
//LiquidCrystal lcd(RS E D4 D5 D6 D7);
//Estes valores quando trabalhar na protoboard
//LiquidCrystal lcd(13, 12, 11, 10, 9, 8);
//Estes valores quando trabalhar no proteus
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
//Estes valores quando trabalhar no LCD Keypad

const int entrada = 2; // PulseIn ligado ao pino 2
//const int timeout = 2000000;   // um segundo
const int t=500; // tempo de delay
const float BETA =  4000; //Calibrar este valor utilizando um termometro externo como comparacao
const float Ro = 100000; //Resistencia tpica de um termistor de 100k
const float To = 25+273;

void setup()
{
  Serial.begin(9600);
  pinMode(entrada, INPUT_PULLUP);
  // pinMode(entrada, INPUT_PULLUP);
  // Use INPUT_PULLUP para utilizar o Arduino diretamente no NE-555
  //Se o circuito estiver instavel, 
  // tente usar Pull Up com pinMode(entrada, INPUT); normalmente.

  lcd.begin(16, 2); //Inicia o LCD com dimensões 16x2(Colunas x Linhas)
  lcd.setCursor(0, 0); //Posiciona o cursor na primeira coluna(0) e na primeira linha(0) do LCD
  lcd.print("Protocolo NE-555"); //Escreve no LCD "Olá Garagista!"
  lcd.setCursor(0, 1); //Posiciona o cursor na primeira coluna(0) e na segunda linha(1) do LCD
  lcd.print(" Lab de Garagem "); //Escreve no LCD "LabdeGaragem"
  delay(t);
}

void loop()
{
  unsigned long pico;
  unsigned long vale;
  float periodo;
  float periodoS;
  float R;
  float Kelvin;
  float Celsius = Kelvin-273;

  pico    = (pulseIn(entrada, HIGH));
  vale   = (pulseIn(entrada, LOW));
  periodo = (pico + vale);
  periodoS = 1000000*periodo;
  
  R = (((1.44*periodoS) - 20000000000)/1000000);
  
Kelvin =  1 / ( (1/To)+((log(R/Ro))/BETA) );


  Celsius = Kelvin-273; // Convert Kelvin to Celsius

  if (periodo)
  {
    lcd.begin(16, 2); 
    lcd.setCursor(0, 0); 
    lcd.print("R ="); 
    lcd.setCursor(4, 0);
    lcd.print(R, 0); 
    lcd.print(" Ohm"); 

    lcd.setCursor(0, 1); 
    lcd.print("T ="); 
    lcd.setCursor(4, 1);
    lcd.print(Celsius, 2); 
    //  lcd.setCursor(8, 1); 
    lcd.print(" Celsius");
  }
  // lcd.clear();
  delay(t);
}













