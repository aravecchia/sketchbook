/*
Desenvolvido por Alexandre Aravecchia
aravecchia@gmail.com
www.aravecchia.weebly.com
*/

#include <Arduino.h>

#include <LiquidCrystal.h> //Inclui a biblioteca do LCD

//LiquidCrystal lcd(RS, EN, DB, DB5, DB6, DB7);
LiquidCrystal lcd(13, 12, 11, 5, 4, 3, 2); //Configura os pinos do Arduino para se comunicar com o LCD
//LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
//Estes valores quando trabalhar na protoboard
//LiquidCrystal lcd(13, 12, 11, 10, 9, 8);
//Estes valores quando trabalhar no proteus

// Declara os pinos analogicos que controlam o tempo de acionamento
int sensor1 = A1;
int sensor2 = A0;

// Declara os pinos digitais que controlam quais relays serao ligados
int button1 = 6;
int button2 = 7;
int button3 = 8;

// Declara os pinos digitais onde serao ligados os relays. Vou chamar de LED porque usei leds sinalizadores
int led1 = 9;
int led2 = 10;
int led3 = 13;

// Declara a variavel tempo
int timmer;

// Declara a variavel que controla o estado
int State;

void setup()
{
  pinMode(sensor1, INPUT);
  pinMode(sensor2, INPUT);

  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(button3, INPUT_PULLUP);

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);

  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  
  State = 1; // Coloca estado=ligado, para inicializar sempre com os relays acionados e o usuario saber que esta funcionando

  lcd.begin(16, 2); //Inicia o LCD com dimensões 16x2(Colunas x Linhas)

  lcd.setCursor(0, 0); // Posiciona o cursor na primeira coluna(0) e na primeira linha(0) do LCD
  lcd.print("C Y B E R  O H M"); // Escreve o nome da empresa no LCD
  lcd.setCursor(4, 1); // Posiciona o cursor na quinta coluna(4) e na segunda linha(1) do LCD
  lcd.print("Robotics"); // Escreve o segundo nome da empresa no LCD
  delay(5000); // Deixe o usuario memorizar o nome da empresa, mas não passe de 5 segundos ou ele vai achar que teu circuito eh lento.
}

void loop()
{
  int timmerON = map(analogRead(sensor1), 0, 1024, 5, 121); // Variável que controla o tempo que os relays ficam ligados (maximo de 2 minutos).
  int timmerOFF = map(analogRead(sensor2), 0, 1024, 5, 601); // Variável que controla o tempo que os relays ficam ligados (maximo de 10 minutos).
  
  int Buttons[3] = {button1, button2, button3}; // Matriz para armazenar o estado dos botoes
  int LED[3] = {led1, led2, led3}; // Matriz para armazenar o estado dos relays

  lcd.begin(16, 2); //Reinicia o LCD com dimensões 16x2(Colunas x Linhas). Seria necessario, se ja iniciou no void setup()?

  lcd.setCursor(2, 0); //Posiciona o cursor na terceira coluna(2) e na primeira linha(0) do LCD

  lcd.print((timmerON) / 60); // Converte para minutos inteiros e escreve no LCD
  lcd.print(":");
  if (((timmerON) % 60) < 10) // Se o resto da divisao por 60 for menor que 10...
  {
    lcd.print("0"); // Escreve um zero
  }
  lcd.print((timmerON) % 60); // Escreve o resto da divisao por 60 no LCD (segundos)
  lcd.print(" -"); // Separador

  lcd.setCursor(9, 0); //Posiciona o cursor na decima coluna(9) e na primeira linha(0) do LCD

  lcd.print((timmerOFF) / 60); // Converte para minutos inteiros e escreve no LCD
  lcd.print(":");
  if (((timmerOFF) % 60) < 10) // Se o resto da divisao por 60 for menor que 10...
  {
    lcd.print("0"); // Escreve um zero
  }
  lcd.print((timmerOFF) % 60); // Escreve o resto da divisao por 60 no LCD (segundos)

  if (((((timmerON - timmer) / 60) < 10) && (State == 1)) || ((((timmerOFF - timmer) / 60) < 10) && (State == 0)))
  // Se o contador regressivo for menor que 10 E os relays estiverem ligados
  // OU
  // e o contador regressivo for menor que 10 E os relays estiverem desligados
  // Este "if" serve para alinhar sempre o contador na coluna correta, quando minutos tem 1 ou 2 digitos
  {
    lcd.setCursor(2, 1); //Posiciona o cursor na terceira coluna(2) e na segunda linha(1) do LCD
  }
  else // Senao
  {
    lcd.setCursor(1, 1); //Posiciona o cursor na segunda coluna(1) e na segunda linha(1) do LCD
  }

  if (State == 1) // Se os relays estao ligados...
  {
    lcd.print((timmerON - timmer) / 60);
    lcd.print(":");
    if (((timmerON - timmer) % 60) < 10)
    {
      lcd.print("0");
    }
    lcd.print((timmerON - timmer) % 60);
    lcd.setCursor(13, 1);
    for (int x = 0; x < 3; x++)
    {
      if (!digitalRead(Buttons[x]) == 1)
      {
        lcd.print("*");
      }
      else
      {
        lcd.print("o");
      }
    }
  }
  else
  {
    lcd.print((timmerOFF - timmer) / 60);
    lcd.print(":");
    if (((timmerOFF - timmer) % 60) < 10)
    {
      lcd.print("0");
    }
    lcd.print(((timmerOFF - timmer) % 60));
    lcd.setCursor(13, 1);
    lcd.print("OFF");
  }

  for (int x = 0; x < 3; x++)
  {
    if (State == 1)
    {
      digitalWrite(LED[x], !(digitalRead(Buttons[x])));
    }
    else
    {
      digitalWrite(LED[x], 0);
    }
  }


  if (((timmer >= timmerON) && (State == 1)) || ((timmer >= timmerOFF) && (State == 0)))
  {
    timmer = 0;
    State = ! State;
  }

  delay(1000); //Aguarda 1 segundo
  timmer++; //Incrementa variável de contagem
}
