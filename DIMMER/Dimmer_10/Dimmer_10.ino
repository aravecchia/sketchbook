#include <Arduino.h>

/*
  Este codigo faz a leitura de um sensor de corrente (optoacoplador)
  no pino 2, e por meio de um potenciometro em A0
  controla um Dimmer no pino 13.
  Desenvolvido por https://cyberohm.com
  com apoio de www.labdegaragem.com.br
  Fique a vontade para baixar, usar e melhorar, mas nao esqueca de
  compartilhar!
  22 de junho de 2015.
*/
int sensor = A0;
int opto = 2;    // Pino de leitura do opto
int controle = 3;       // Pino ligado ao circuito do Triac

//este pino tem que disparar em [To+T/16] para que o motor tenha 7T/8 da potencia total

// Variables will change:
int optoState = 0;       // Estado do opto. Se estiver HIGH, tensao diferente de zero.
//Se estiver em LOW, tensao = zero. Presisamente o que queremos.
int lastOptoState = 0;     // O estado anterior do sensor.
long lastMillis;     //define a contagem do tempo.
float period;
float frequency;

void setup()
{
  pinMode(opto, INPUT);  // inicializa o pino do opto de leitura como inpput
  pinMode(sensor, INPUT); //inicializa o pino do sensor analogico como input
  pinMode(controle, OUTPUT);  // inicializa o pino do MOC-3031 como output
  Serial.begin(9600);
}


void loop()
{
  digitalWrite(controle, HIGH);
  optoState = digitalRead(opto);
  // compare the buttonState to its previous state
 Serial.println(optoState);
  if ((optoState != lastOptoState) && (optoState == HIGH))
  {
    int SENSOR = analogRead(sensor);
    int D = map(SENSOR, 0, 1023, 0, 8); // o delay de controle
    int tensao = map(SENSOR, 0, 1023, 127, 64); // Leitura da tensao resultante
    period = millis() - lastMillis;
    digitalWrite(controle, LOW);
    delay(D);
    digitalWrite(controle, HIGH);

    Serial.print(optoState);
    Serial.print(" - ");
    Serial.print(period);
    Serial.print(" ms - ");
    Serial.print(tensao);
    Serial.println(" V");

    lastMillis = millis(); // !!! coloque uma regra
    // marcando o tempo a cada vez que optoState=LOW.
    //jogue este tempo para determinar o tempo de map (tempo no lugar de 8)
    //faca uma leitura com aproximacao de 2 casas decimais
    //assim vc vai medir precisamente o periodo e a frequencia e sincronizar
    // com o controle do tempo q o triac leva para disparar (por exemplo 23%)
  }
  lastOptoState = optoState;
}
