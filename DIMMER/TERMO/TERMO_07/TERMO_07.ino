#include <Arduino.h>

/*
  CLP para máquina de termoformagem a vácuo.
  Desenvolvido por https://cyberohm.com
  com apoio de www.labdegaragem.com.br
  Agradecimentos a Rui Viana, Wiechert, Celso Ito, Oraculo X, Guilherme Razgriz e Rafael Maciel.
  Fique a vontade para baixar, usar, melhorar e compartilhar!
  1 de junho de 2016.
*/
#include <math.h>
#include <Thermistor.h>   // Inclui a biblioteca modificada para termistor de 100K.
// No arquivo Thermistor.cpp da biblioteca, utilize os seguintes valores:
// A=-0.0011717297; B=0.0004565213; C=-0.00000047736406329569

#include <LiquidCrystal.h> //Inclui a biblioteca do LCD
//LiquidCrystal lcd(RS, EN, DB4, DB5, DB6, DB7);
//LCD 20x4
LiquidCrystal lcd(12, 8, 11, 10, 9, 7);
//LCD Keypad 16x4
//LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
//Configura os pinos do Arduino para se comunicar com o LCD

byte ENTER = A0;      // Botao Enter (confirma selecao de menu)
byte menu = A1;        // Botao de selecao de funcoes, rolagem de menus
byte sensor = A2;       // Termistor
Thermistor temp(sensor);

byte opto = 2;       // Pino de leitura do opto 4N35
byte sobe = 3;      // Botao fim-de-linha no aquecedor
byte desce = 4;    // Botao fim-de-linha no resfriador
byte triac = 5;   // Pino ligado ao circuito do Triac
byte motor = 6;  // Motor de sucção e resfriamento
//este pino tem que disparar em [To+T/16] para que o motor tenha 7T/8 da potencia total
byte led = 13;

float leitura;
float D;
float visor;
byte t = 100;
int duration = 500;
byte etapa = 0;

byte selecao;
byte copias;
int temperatura;

long R;

long A = -0.0074572623;
long B = 0.0012359611;
long C = -0.00000223888682670715;
// long T = 1/(A+(B*(logn(R)))+(C*(pow(logn(R), 3))));

String LOGOTIPO[7] = {"C", "l", "o", "n", "e", "  ", "It !"};

String MENU[] = {"Selecao Manual      ",
                 "ABS            ",
                 "Ac de Butirato ",
                 "Ac de Celulose ",
                 "Acet de Vinila ",
                 "Metacr  Metila ",
                 "Nylon 6        ",
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
byte TEMP[] = {0, 230, 230, 175, 255, 160, 215, 215, 180, 180, 130, 150, 105, 130, 165, 230, 150, 127, 175};




//_________________________________________________________________________VOID SETUP()
void setup()
{
  // pinMode(opto, INPUT);  // inicializa o pino do opto de leitura como inpput
  pinMode(sensor, INPUT); // inicializa o pino do sensor analogico como input
  pinMode(sobe, INPUT); // Botao fim-de-linha superior (forno)
  pinMode(desce, INPUT); // Botao fim-de-linha superior (sucção)
  pinMode(menu, INPUT); // Potenciometro para o menu
  pinMode(ENTER, INPUT); // Botão ENTER

  pinMode(triac, OUTPUT);  // Controle de potencia
  pinMode(motor, OUTPUT);  // Acionamento da sucção
  pinMode(led, OUTPUT);    // Led de sinalizacao

  // set up the LCD's number of columns and rows and:
  lcd.begin(20, 4);  // LCD 20 colunas e 4 linhas

  lcd.clear();
  lcd.setCursor(4, 0);
  ///////////////////////////// Escreve o Logotipo
  for (int x = 0; x < 8; x++)
  {
    lcd.print(LOGOTIPO[x]);
    delay(2 * t);
  }

  delay(2 * t);
  displayBlink(2, 5 * t); // blink twice
  lcd.setCursor(0, 1);

  for (byte x = 0; x < 20; x++)
  {
    lcd.print(".");
    delay(t / 2);
  }
  delay(5*t);
  Serial.begin(9600);

  attachInterrupt(0, cut, RISING); // Interrupção no pino 2(0) ou 3(1)
  // RISING FALLING CHANGE
}

//_________________________________________________________________________VOID BLINK()
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

//_________________________________________________________________________VOID CUT()
void cut()
{
  temperatura = temp.getTemp();
  while ((TEMP[selecao]) > temperatura)
  {
    delayMicroseconds(D);
    digitalWrite(triac, HIGH);
    delayMicroseconds(t);
    digitalWrite(triac, LOW);
  }
}


//_________________________________________________________________________VOID LOOP()


//_________________________________________________________________________VOID LOOP()
void loop()
{
  uint8_t oldSREG = SREG; //Armazena variavel para reiniciar attachInterrupt
  cli();  // Interrompe a interrupcao ;) Lembre-se: !(!0)=0

  // Maquina ligada: desliga tudo__________________________________________0
  digitalWrite(motor, LOW); //Desliga a succao
  digitalWrite(triac, HIGH); //Desliga o triac
  lcd.clear();               // Limpa o LCD

  // Maquina ligada: posicione o plastico__________________________________1
  while ((digitalRead(ENTER) == 0) && (digitalRead(desce) == 1))
  {
    {
      lcd.setCursor(0, 0);
      lcd.print("Posicione o plastico");
      lcd.setCursor(0, 3);
    }

    // Escolha o plastico__________________________________________________2
    while ((digitalRead(ENTER) == 0) && (digitalRead(sobe) == 1))
    {
      {
        lcd.setCursor(0, 0);
        lcd.print("Escolha o plastico: ");

        selecao = map(analogRead(menu), 0, 1020, 0, 18);

        lcd.setCursor(0, 1);
        lcd.print(MENU[selecao]);
        if (selecao != 0)
        {
          lcd.setCursor(16, 1);
          lcd.print(TEMP[selecao]);
          lcd.print(char(-33));
        }
      }
      selecao = map(analogRead(menu), 0, 1020, 0, 18);

      // Aperta botao ENTER________________________________________________3
      if (digitalRead(ENTER) == 1)

        // Seleciona o numero de cópias______________________________________4
      {
        delay(t);
        while (digitalRead(ENTER) == 0)
        {
          lcd.setCursor(0, 0);
          lcd.print("Quantas cópias?");

          copias = map(analogRead(menu), 0, 1020, 1, 10);

          lcd.setCursor(0, 1);
          lcd.print(copias);
        }
      }
      // Aperta botao ENTER________________________________________________5
      if (digitalRead(ENTER) == 1)

        digitalWrite(triac, LOW);
      leitura = float(analogRead(sensor));
      D = map(leitura, 0, 1023, 0, 8200); // o delay de controle

      Serial.println(D);
      SREG = oldSREG;  //Reinicia attachInterrupt
      delayMicroseconds(20000);
    }
  }
}
