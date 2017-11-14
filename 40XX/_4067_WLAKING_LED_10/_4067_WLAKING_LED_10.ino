#include <Arduino.h>

	
// Programa : Painel de leds com modulo Max7219  
// Adaptacoes e comentarios : Arduino e Cia  

// Carrega a biblioteca MD_MAX72xx  
#include <MD_MAX72xx.h>  
  
// Numero de modulos utilizados  
#define     MAX_DEVICES     2  
  
// Ligacoes ao Arduino  
#define     DATA_PIN     4  
#define     CS_PIN       5  
#define     CLK_PIN      6  
   
MD_MAX72XX mx = MD_MAX72XX(DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);  
  
// Velocidade do scroll  
#define SCROLL_DELAY     2000  
// Colunas entre cada caracter  
#define     CHAR_SPACING     1  
  
#define     BUF_SIZE     75  
char curMessage[BUF_SIZE];  
char newMessage[BUF_SIZE];  
  
// int scrollDelay;  
  
uint8_t scrollDataSource(uint8_t dev, MD_MAX72XX::transformType_t t)  
{  
  static char          *p = curMessage;  
  static uint8_t     state = 0;  
  static uint8_t     curLen, showLen;  
  static uint8_t     cBuf[8];  
  uint8_t colData;  
  
  switch(state)  
  {  
  case 0:  
    showLen = mx.getChar(*p++, sizeof(cBuf)/sizeof(cBuf[0]), cBuf);  
    curLen = 0;  
    state++;  
    if (*p == '\0')  
    {  
     p = curMessage;  
    }  
  case 1:       
    colData = cBuf[curLen++];  
    if (curLen == showLen)  
    {  
     showLen = CHAR_SPACING;  
     curLen = 0;  
     state = 2;  
    }  
    break;  
  case 2:  
    colData = 0;  
    curLen++;  
    if (curLen == showLen)  
     state = 0;  
    break;  
    default:  
    state = 0;  
  }  
  return(colData);  
}  
  
void scrollText(void)  
{  
  static uint32_t     prevTime = 0;  
  if (millis()-prevTime >= SCROLL_DELAY)  
  {  
    mx.transform(MD_MAX72XX::TSR);       
    prevTime = millis();  
  }  
}  
  
int w0 = 10;
int w1 = 9;
int w2 = 11;
int w3 = 12;

const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
const int analogOutPin = 2; // Analog output pin that the LED is attached to

int sensorValue;        // value read from the pot
int outputValue;        // value output to the PWM (analog out)

int T = 1;

int matriz[16][4] = {
  {
    0,0,0,0                              }
  ,
  {
    0,0,0,1                              }
  ,
  {
    0,0,1,0                              }
  ,
  {
    0,0,1,1                              }
  ,
  {
    0,1,0,0                              }
  ,
  {
    0,1,0,1                              }
  ,
  {
    0,1,1,0                              }
  ,
  {
    0,1,1,1                              }
  ,
  {
    1,0,0,0                              }
  ,
  {
    1,0,0,1                              }
  ,
  {
    1,0,1,0                              }
  ,
  {
    1,0,1,1                              }
  ,
  {
    1,1,0,0                              }
  ,
  {
    1,1,0,1                              }
  ,
  {
    1,1,1,0                              }
  ,
  {
    1,1,1,1                              }
  ,
};


void setup()
{
 mx.begin();  
  mx.setShiftDataInCallback(scrollDataSource);  
  // Define o nivel de luminosidade  
  mx.control(MD_MAX72XX::INTENSITY, 4);  
  // Mensagem a ser exibida   
  strcpy(curMessage, " Arduino e Cia ");  
  newMessage[0] = '\0';  

  pinMode(w0, OUTPUT);
  pinMode(w1, OUTPUT);
  pinMode(w2, OUTPUT);
  pinMode(w3, OUTPUT);

  pinMode(sensorValue, INPUT);
  pinMode(outputValue, OUTPUT);
  // initialize serial communications at 9600 bps:
  Serial.begin(9600); 
}

void loop()
{
 scrollText();  
 
  for(int i = 0; i<16; i++)
  {
    seletor(matriz[i]);
    //    sensorValue=0;
    sensorValue = analogRead(analogInPin);            
    // map it to the range of the analog out:
    outputValue = map(sensorValue, 0, 1023, 0, 250);  
    // change the analog out value:
    if (outputValue>200)
    {
      outputValue=255;
    }
    else if (outputValue<100)
    {
      outputValue=0;
    }
    analogWrite(analogOutPin, outputValue);  

    escreve(i);
    Serial.print(sensorValue);
    Serial.print(" - ");
    Serial.println(outputValue);
    delay(T); 
  }
}

void seletor( int m[] )
{
  digitalWrite(w0, m[0]);
  digitalWrite(w1, m[1]);
  digitalWrite(w2, m[2]);
  digitalWrite(w3, m[3]);
}

void escreve(int led)
{
  Serial.print("Led ativo: ");
  Serial.print(led);
  Serial.print(" - ");
  Serial.print(matriz[led][0]);
  Serial.print(matriz[led][1]);
  Serial.print(matriz[led][2]);
  Serial.print(matriz[led][3]);  
  Serial.print(" - Leitura: ");  
}




