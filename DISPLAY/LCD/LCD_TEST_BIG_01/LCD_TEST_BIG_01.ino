#include <Arduino.h>

//Programa : Relogio com numeros customizados
//Autor : Arduino e Cia

#include <LiquidCrystal.h> //Biblioteca LCD

#include "Wire.h" //Biblioteca para uso do RTC DS1307

#define DS1307_ADDRESS 0x68

byte zero = 0x00; 

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

int numero, minutoanterior1,minutoanterior2,horaanterior1,horaanterior2;
int x = 0;

//Arrays para criação dos segmentos e customização dos números
byte LT[8] = 
{
  B01111,  B11111,  B11111,  B11111,  B11111,  B11111,  B11111,  B11111
};
byte UB[8] =
{
  B11111,  B11111,  B11111,  B00000,  B00000,  B00000,  B00000,  B00000
};
byte RT[8] =
{
  B11110,  B11111,  B11111,  B11111,  B11111,  B11111,  B11111,  B11111
};
byte LL[8] =
{
  B11111,  B11111,  B11111,  B11111,  B11111,  B11111,  B11111,  B01111
};
byte LB[8] =
{
  B00000,  B00000,  B00000,  B00000,  B00000,  B11111,  B11111,  B11111
};
byte LR[8] =
{
  B11111,  B11111,  B11111,  B11111,  B11111,  B11111,  B11111,  B11110
};
byte UMB[8] =
{
  B11111,  B11111,  B11111,  B00000,  B00000,  B00000,  B11111,  B11111
};
byte LMB[8] =
{
  B11111,  B00000,  B00000,  B00000,  B00000,  B11111,  B11111,  B11111
};

void setup()
{
  Wire.begin();
  //Associa cada segmento criado, a um número
  lcd.createChar(0,LT);
  lcd.createChar(1,UB);
  lcd.createChar(2,RT);
  lcd.createChar(3,LL);
  lcd.createChar(4,LB);
  lcd.createChar(5,LR);
  lcd.createChar(6,UMB);
  lcd.createChar(7,LMB);

  lcd.begin(20, 4); //Inicializa o LCD

  //A linha abaixo pode ser retirada apos setar a data e hora
  //SelecionaDataeHora(); 
}

void loop()
{
  lcd.setCursor(8,0);
  lcd.print(".");
  lcd.setCursor(8,1);
  lcd.print(".");
  //Chama rotina que extrai as informacoes do DS1307 e mostra no LCD
  Mostrarelogio(); 
  delay(1000);
}

void SelecionaDataeHora()   //Seta a data e a hora do DS1307
{
  byte segundos = 00; //Valores de 0 a 59
  byte minutos = 44; //Valores de 0 a 59
  byte horas = 22; //Valores de 0 a 23
  byte diadasemana = 1; //Valores de 0 a 6 - 0=Domgino, 1 = Segunda, etc.
  byte diadomes = 17; //Valores de 1 a 31
  byte mes = 4; //Valores de 1 a 12
  byte ano = 13; //Valores de 0 a 99
  Wire.beginTransmission(DS1307_ADDRESS);
  Wire.write(zero); //Stop no CI para que o mesmo possa receber os dados

  // As linhas abaixo escrevem no CI os valores de data e 
  // hora que foram colocados nas variaveis acima
  Wire.write(ConverteParaBCD(segundos));
  Wire.write(ConverteParaBCD(minutos));
  Wire.write(ConverteParaBCD(horas));
  Wire.write(ConverteParaBCD(diadasemana));
  Wire.write(ConverteParaBCD(diadomes));
  Wire.write(ConverteParaBCD(mes));
  Wire.write(ConverteParaBCD(ano));
  Wire.write(zero); //Start no CI
  Wire.endTransmission(); 
}

byte ConverteParaBCD(byte val){ //Converte o número de decimal para BCD
  return ( (val/10*16) + (val%10) );
}

byte ConverteparaDecimal(byte val)  { //Converte de BCD para decimal
  return ( (val/16*10) + (val%16) );
}

void custom0()//Seleciona os segmentos para formar o numero 0
{ 
  lcd.setCursor(x, 0); //Seleciona a linha superior
  lcd.write((byte)0);  //Segmento 0 selecionado
  lcd.write(1);  //Segmento 1 selecionado
  lcd.write(2);
  lcd.setCursor(x, 1); //Seleciona a linha inferior
  lcd.write(3);  
  lcd.write(4);  
  lcd.write(5);
}

void custom1() //Seleciona os segmentos para formar o numero 1
{
  lcd.setCursor(x,0);
  lcd.write(1);
  lcd.write(2);
  lcd.setCursor(x+1,1);
  lcd.write(5);
}

void custom2() //Seleciona os segmentos para formar o numero 2
{
  lcd.setCursor(x,0);
  lcd.write(6);
  lcd.write(6);
  lcd.write(2);
  lcd.setCursor(x, 1);
  lcd.write(3);
  lcd.write(7);
  lcd.write(7);
}

void custom3()  //Seleciona os segmentos para formar o numero 3
{
  lcd.setCursor(x,0);
  lcd.write(6);
  lcd.write(6);
  lcd.write(2);
  lcd.setCursor(x, 1);
  lcd.write(7);
  lcd.write(7);
  lcd.write(5); 
}

void custom4()  //Seleciona os segmentos para formar o numero 4
{
  lcd.setCursor(x,0);
  lcd.write(3);
  lcd.write(4);
  lcd.write(2);
  lcd.setCursor(x+2, 1);
  lcd.write(5);
}

void custom5()  //Seleciona os segmentos para formar o numero 5
{
  lcd.setCursor(x,0);
  lcd.write((byte)0);
  lcd.write(6);
  lcd.write(6);
  lcd.setCursor(x, 1);
  lcd.write(7);
  lcd.write(7);
  lcd.write(5);
}

void custom6()  //Seleciona os segmentos para formar o numero 6
{
  lcd.setCursor(x,0);
  lcd.write((byte)0);
  lcd.write(6);
  lcd.write(6);
  lcd.setCursor(x, 1);
  lcd.write(3);
  lcd.write(7);
  lcd.write(5);
}

void custom7() //Seleciona os segmentos para formar o numero 7
{
  lcd.setCursor(x,0);
  lcd.write(1);
  lcd.write(1);
  lcd.write(2);
  lcd.setCursor(x+1, 1);
  lcd.write((byte)0);
}

void custom8()  //Seleciona os segmentos para formar o numero 8
{
  lcd.setCursor(x,0);
  lcd.write((byte)0);
  lcd.write((byte)6);
  lcd.write(2);
  lcd.setCursor(x, 1);
  lcd.write(3);
  lcd.write(7);
  lcd.write(5);
}

void custom9()  //Seleciona os segmentos para formar o numero 9
{
  lcd.setCursor(x,0);
  lcd.write((byte)0);
  lcd.write((byte)6);
  lcd.write((byte)2);
  lcd.setCursor(x+2, 1);
  lcd.write((byte)5);
}

void Mostrarelogio()
{
  byte minut[2];
  String minutostring;
  String digitosegundos;
  char buf;
  Wire.beginTransmission(DS1307_ADDRESS);
  Wire.write(zero);
  Wire.endTransmission();
  Wire.requestFrom(DS1307_ADDRESS, 7);
  int segundos = ConverteparaDecimal(Wire.read());
  int minutos = ConverteparaDecimal(Wire.read());
  int horas = ConverteparaDecimal(Wire.read() & 0b111111); 
  int diadasemana = ConverteparaDecimal(Wire.read()); 
  int diadomes = ConverteparaDecimal(Wire.read());
  int mes = ConverteparaDecimal(Wire.read());
  int ano = ConverteparaDecimal(Wire.read());

  x = 0;
  numero = horas/10;
  
  //Condicional para evitar sobreposição de caracteres
  if (horaanterior1 != minutos %10) 
  {
    lcd.setCursor(0,0);
    lcd.print("   ");
    lcd.setCursor(0,1);
    lcd.print("   ");
    horaanterior1 = minutos %10;
  }

  //Chama rotina que mostra o numero customizado na tela
  mostranumero(); 

  x = 4;
  numero = horas % 10;
  if (horaanterior2 != minutos %10)
  {
    lcd.setCursor(4,0);
    lcd.print("   ");
    lcd.setCursor(4,1);
    lcd.print("   ");
    horaanterior2 = minutos %10;
  }
  mostranumero();
  
  x = 9;
  numero = minutos/10;

  if (minutoanterior1 != minutos %10)
  {
    lcd.setCursor(9,0);
    lcd.print("   ");
    lcd.setCursor(9,1);
    lcd.print("   ");
    minutoanterior1 = minutos %10;
  }
  mostranumero();

  x = 13;
  numero = minutos % 10;
  if (minutoanterior2 != minutos %10)
  {
    lcd.setCursor(13,0);
    lcd.print("   ");
    lcd.setCursor(13,1);
    lcd.print("   ");
    minutoanterior2 = minutos %10;
  }
  mostranumero();
}

void mostranumero() //Mostra o numero na posicao definida por "X"
{
  switch(numero)
    {
      case 0:custom0();
      break;
      case 1:custom1();
      break;
      case 2:custom2();
      break;
      case 3:custom3();
      break;
      case 4:custom4();
      break;
      case 5:custom5();
      break;
      case 6:custom6();
      break;
      case 7:custom7();
      break;
      case 8:custom8();
      break;
      case 9:custom9();
      break;
    }
}
