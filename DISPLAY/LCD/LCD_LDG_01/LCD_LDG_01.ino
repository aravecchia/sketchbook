/*
Desenvolvido por Alexandre Aravecchia
aravecchia@gmail.com
www.aravecchia.weebly.com
*/

#include <Arduino.h>

#include <LiquidCrystal.h> //Inclui a biblioteca do LCD

LiquidCrystal lcd(12, 11, 5, 4, 3, 2); //Configura os pinos do Arduino para se comunicar com o LCD
//LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
//Estes valores quando trabalhar na protoboard
//LiquidCrystal lcd(13, 12, 11, 10, 9, 8);
//Estes valores quando trabalhar no proteus

int led1 = 10;
int led2 = 13;
int temp; //Inicia uma variável inteira(temp), para escrever no LCD a contagem do tempo

void setup()
{
  lcd.begin(16, 2); //Inicia o LCD com dimensões 16x2(Colunas x Linhas)
  lcd.setCursor(0, 0); //Posiciona o cursor na primeira coluna(0) e na primeira linha(0) do LCD
  lcd.print("Ola Garagista!"); //Escreve no LCD "Olá Garagista!"
  lcd.setCursor(0, 1); //Posiciona o cursor na primeira coluna(0) e na segunda linha(1) do LCD
  lcd.print("LabdeGaragem"); //Escreve no LCD "LabdeGaragem"
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
}

void loop()
{
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);

  lcd.setCursor(13, 1); //Posiciona o cursor na décima quarta coluna(13) e na segunda linha(1) do LCD
  lcd.print(temp); //Escreve o valor atual da variável de contagem no LCD
  delay(1000); //Aguarda 1 segundo
  temp++; //Incrementa variável de contagem

  while (temp % 10 == 0)
  {
    digitalWrite(led1, HIGH);
    delay(1000); //Aguarda 1 segundo
  temp++; //Incrementa variável de contagem
  }
while (temp % 3 == 0)
  {
    digitalWrite(led2, HIGH);
    delay(1000); //Aguarda 1 segundo
  temp++; //Incrementa variável de contagem
  }
  
  if (temp == 999) //Se a variável temp chegar em 600(10 Minutos),...
  {
    temp = 0; //...zera a variável de contagem
  }
}

