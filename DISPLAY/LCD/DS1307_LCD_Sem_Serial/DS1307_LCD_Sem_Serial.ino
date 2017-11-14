#include <Arduino.h>

#include <LiquidCrystal.h>
#include <DS1307.h>
#include <Wire.h>
LiquidCrystal lcd(13, 12, 5, 4, 3, 2);
//LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
//Estes valores quando trabalhar na protoboard
//LiquidCrystal lcd(13, 12, 11, 10, 9, 8);
//Estes valores quando trabalhar no proteus

int clock[7];

void setup() {
  for (int i = 3; i < 8; i++) {
    pinMode(i, INPUT);
  }
Serial.begin(9600);//Inicializacao da serial
  lcd.begin(20, 2);
  DS1307.begin();
  //DS1307.setDate(ano, mes, dia, semana, horas, minutos, segundos); // <= Após carregar data e hora podera desativar esta linha
}

void loop() {
  DS1307.getDate(clock);

  lcd.setCursor(0, 2);
  lcd.print("Hora: ");
  Print(clock[4]);
  lcd.print(":");
  Print(clock[5]);
  lcd.print(":");
  Print(clock[6]);
  lcd.setCursor(0, 0);
  lcd.print("Data: ");
  Print(clock[2]);
  lcd.print("/");
  Print(clock[1]);
  lcd.print("/");
  lcd.print("20");
  Print(clock[0]);

  if (digitalRead(7)) { //horas
    clock[4]++;
    if (clock[4] > 23) clock[4] = 0;
    DS1307.setDate(clock[0], clock[1], clock[2], 0, clock[4], clock[5], clock[6]);
  }
  
    if (digitalRead(6)) { //minutos
    clock[5]++;
    if (clock[5] > 59) clock[5] = 0;
    DS1307.setDate(clock[0], clock[1], clock[2], 0, clock[4], clock[5], clock[6]);
  }

  if (digitalRead(5)) { //dia
    clock[2]++;
    if (clock[2] > 31) clock[2] = 1;
    DS1307.setDate(clock[0], clock[1], clock[2], 0, clock[4], clock[5], clock[6]);
  }

  if (digitalRead(4)) { //mes
    clock[1]++;
    if (clock[1] > 12) clock[1] = 1;
    DS1307.setDate(clock[0], clock[1], clock[2], 0, clock[4], clock[5], clock[6]);
  }

  if (digitalRead(3)) { //ano
    clock[0]++;
    if (clock[0] > 99) clock[0] = 0;
    DS1307.setDate(clock[0], clock[1], clock[2], 0, clock[4], clock[5], clock[6]);
  }
  delay(100);
}

//Funcao para ajustar os digitos para 00,01,02,...
void Print(int number) {
  lcd.print(number / 10); //imprime o digito mais significativo
  lcd.print(number % 10); //imprime o digito menos significativo
}
