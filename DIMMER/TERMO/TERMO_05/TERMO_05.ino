#include <Arduino.h>

/*
  CLP para máquina de termoformagem a vácuo.
  Desenvolvido por https://cyberohm.com
  com apoio de www.labdegaragem.com.br
  Agradecimentos a Rui Viana, Celso Ito, Guilherme Razgriz e Rafael Maciel.
  Fique a vontade para baixar, usar, melhorar e compartilhar!
  1 de junho de 2016.
*/
#include <Thermistor.h>
#include <LiquidCrystal.h>
#include <Wire.h>
LiquidCrystal lcd(12, 8, 11, 10, 9, 7);
//LiquidCrystal lcd(RS E D4 D5 D6 D7);

//Pinos de INPUT
//Thermistor temp(0);     //Sensor de temperatura NTC - coeficiente beta=4000
byte sensorTemp = 0;
byte menu = A1;         //botao de selecao de funcoes, rolagem de menus
byte ENTER = A2;        //botao Enter (confirma selecao de menu)
byte opto = 2;          // Pino de leitura do opto 4N35
byte sobe = 3;         //Botao fim-de-linha no aquecedor
byte desce = 4;        //Botao fim-de-linha no resfriador

//Pinos de OUTPUT

byte triac = 5;       // Pino ligado ao circuito do Triac
//este pino tem que disparar em [To+T/16] para que o motor tenha 7T/8 da potencia total
byte motor = 6;          //Motor de succao de ar e resfriamento do plastico

// VARIAVEIS DO SENSOR DE TENSAO:
byte optoState;       // Estado do opto. Se estiver HIGH, tensao diferente de zero.
//Se estiver em LOW, tensao = zero. Presisamente o que queremos.
byte lastOptoState;     // O estado anterior do sensor.
//long lastMillis;     //define a contagem do tempo.

// VARIAVEIS DE CALCULO E CONVERSAO
float leitura;
float D;
float T;
float visor;
float tensao;
byte t = 100;
int duration = 500;

byte selecao;
int temperatura;

String LOGOTIPO[7] = {"C", "l", "o", "n", "e", "  ", "It !"};

String MENU[] = {"Selecao Manual      ",
                 "ABS            ",
                 "Ac de Butirato ",
                 "Ac de Celulose ",
                 "Acet de Vinila ",
                 "Metacr  Metila ",
                 "Nylon 6        ",
                 /*"Nylon 66       ",*/
                 "Nylon 6,10     ",
                 "Nylon 11       ",
                 "PET            ",
                 "Poliacetal     ",
                 "Policarbonato  ",
                 "Poliet B Dens. ",
                 "Poliet A Dens. ",
                 "Polipropileno  ",
                 "Poliuretano    ",
                 "PVC Flexivel   ",
                 "PVC Rigido     ",
                 "SAN            "
                };
byte TEMP[] = {0, 230, 230, 175, 255, 160, 215, /*260,*/ 215, 180, 180, 130, 150, 105, 130, 165, 230, 150, 127, 175};


//___________________________________________________________________________VOID BLINK()
void displayBlink(int blinks, int duration)
{
  while (blinks--)
  {
    lcd.noDisplay();
    delay(duration);
    lcd.display();
    delay(duration);
  }
}

//___________________________________________________________________________VOID SETUP()
void setup()
{
  pinMode(opto, INPUT);  // Opto 4N35 - Sensor de tensao analogico como input
  pinMode(sobe, INPUT); //
  pinMode(desce, INPUT); //
  pinMode(menu, INPUT); //
  pinMode(ENTER, INPUT); //

  pinMode(triac, OUTPUT);  //
  pinMode(motor, OUTPUT);  //

  // set up the LCD's number of columns and rows and:
  lcd.begin(20, 4);
  // Print a message to the LCD.
  lcd.clear();
  lcd.setCursor(4, 0);
  for (int x = 0; x < 8; x++)
  {
    lcd.print(LOGOTIPO[x]);
    delay(2 * t);
  }
  delay(2 * t);
  displayBlink(2, 5 * t); // blink twice
  lcd.setCursor(0, 1);
  for (int x = 0; x < 20; x++)
  {
    lcd.print(char(6));
    delay(t / 2);
  }
}

//___________________________________________________________________________VOID LOOP()
void loop()
{
  digitalWrite(motor, LOW);
  digitalWrite(triac, HIGH);
  while (digitalRead(sobe) == 1)
  {
    optoState = digitalRead(opto);



    /*
      switch((digitalRead(ENTER) )
      //decisão baseada leitura da porta

        {
        case (‘r’):
          digitalWrite(9, HIGH);
          //se ‘r’ acende LED vermelho
        break;

        case (‘g’):
          digitalWrite(10, HIGH);
          //se ‘g’ acende LED verde
        break;

        case (‘b’):
          digitalWrite(11, HIGH);
          //se ‘b’ acende LED azul
        break;

        default:
          Serial.println(“Escolha ‘r’, ‘g’ ou ‘b’”);
        //mensagem de erro e encerra a rotina

    */
    while ((digitalRead(ENTER) != 1) && (digitalRead(sobe) == 0))
    {
      {
        lcd.setCursor(0, 2);
        lcd.print("Escolha o plastico: ");
        lcd.setCursor(0, 3);
        selecao = map(analogRead(menu), 0, 1020, 0, 18);

        lcd.print(MENU[selecao]);
        if (selecao != 0)
        {
          lcd.setCursor(16, 3);
          lcd.print(TEMP[selecao]);
          lcd.print(char(-33));
        }
      }
      /*
        if ((digitalRead(ENTER) == 1) && (selecao == 0))
        {
        delay(2*t);
        lcd.setCursor(0, 2);
        lcd.print("Temperatura: ");
        lcd.setCursor(0, 3);
        temperatura = map(analogRead(menu), 0, 1020, 100, 250);
        lcd.print(temperatura);
        lcd.print(char(-33));
        lcd.setCursor(12, 3);
        lcd.print("Confirma?");
        }
      */





      // compare the buttonState to its previous state
      //   if ((optoState != lastOptoState) && (optoState == HIGH))
      {
        leitura = float(analogRead(sensorTemp));
        D = map(leitura, 0, 1023, 0, 8200); // o delay de controle
        T = float (map(leitura, 0, 1023, 0, 100000)) / 1000;
        tensao = 5 * leitura / 1023;
        //    Rt = R0.[1 + At + Bt2]
        //  97000 = 100 * ((3.90802/1000)*273 + 40000*(273^2))
        //    R2 = (-1000 + sqrt(-100000100000) + (4*5/float(map(analogRead(sensor)), 0, 1023, 0, 5))))/2
        //    Tk = Tc + 273
        //    Tc = Tk - 273
        //    25C = 298K (97 KOhm)
        delayMicroseconds(D);
        digitalWrite(triac, HIGH);
        delayMicroseconds(t);
        digitalWrite(triac, LOW);

        Serial.print(T);
        Serial.println(" %");

        lcd.setCursor(0, 2);
        lcd.print(T);
        lcd.print(" % - ");
        lcd.setCursor(10, 2);
        lcd.print(tensao);
        lcd.print(" Volts");
        lcd.setCursor(0, 3);
        lcd.print(char(-33));
        /*
          for (long x = -127; x < 128; x++)
          {
            lcd.setCursor(0, 3);
            lcd.print(x);
            lcd.print(" - ");
            lcd.print(char(x));
            delay(5*t);
          }
        */
      }

      lastOptoState = optoState;
      delay(2 * t);
    }
    if (digitalRead(sobe) == 0)
    {
      delay(10 * t);
      if ((digitalRead(sobe) == 0) && (digitalRead(desce) == 0))
      {
        lcd.setCursor(0, 2);
        lcd.print("Verifique o");
        lcd.setCursor(0, 3);
        lcd.print("plastico!");
      }
    }
    if ((digitalRead(sobe) == 0) && (digitalRead(desce) == 1))
    {
      digitalWrite(motor, HIGH);
      delay(100 * t);
    }
  }
}

