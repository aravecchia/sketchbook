#include <Arduino.h>

/*
   Project Name:     Dimmer
   FileName:        Dimmer_Pot2.ino
   Dependencies:    N/A
   Processor:       Arduino
   Compiler:        N/A
   IDE:             Arduino IDE 1.0.6
   Hardware:        Arduino UNO
   Autor:           Rui Viana
   Data:            25/06/2015
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   Description:    
 
   Rotina para dimmer. (110v ou 220v)  ajustada por um pot
   Os valores de brilho da lampada são ajustados por pot no pino A0.
   Uso didático
   Rui  24/06/2015
   
   Este code funciona assim:
   O potenciômetro plugado no pino A0, fornece o valor para o ADC.
   O ADC calcula o valor entre 0 e 1023 e guarda na variável dimming.
   Na função map() é feita a relação entre o valor lido e a escala de 0 à 7900.
   A duração do ciclo de 60Hz é de 16666 us, com um semiciclo de 8333 us,
   descontando a duração do pulso de zero cross de +- 250 us e o pulso de disparo do triac
   de +- 100 us, sobram +- 7983 us.
   Portanto o valor 7900 é o maior valor de deslocamento recomendado após o zerocross.
   O valor do pulso do zerocross vai variar em função dos resistores em serie com a ponte retificadora,
   portanto o valor de 7900, pode ser necessário modificar em função deste valor.
   
   O pulso do zerocross é detectado no pino 2.
   Após pulsar e ficar em LOW, começa-se a contar o tempo para o disparo do triac.
   Este tempo foi calculado em função do valor gerado pelo calculo do ADC.
   Se este valor for zero, o triac disparará no incio do ciclo e a lampada acende com brilho total.
   Se o valor for 7900, o triac dispara no final do ciclo, não sobrando tensão para a lampada,
   e a mesma fica apagada.
   Testei com 110v e 220v.
*/
//************  Variaveis e constantes  ************
  int Triac  = 3;                                  // Pino de disparo do Triac
  int ZCross = 2;                                  // Pino de entrada do zerocross
  unsigned int pinAnalog = 0;                      // Pino de entrada do potenciômetro (A0)
  unsigned int dimming   = 0;                      // Variável para tempo de retardo. Valor Inicial Minimo
//***********************  Setup *******************  
  void setup()                                     // Rotina de setup
  {
    pinMode(pinAnalog, INPUT);                     // Define o pino(A0) como entrada analógica                      
    pinMode(Triac, OUTPUT);                        // Define o pino(D3) Triac como saída
  }
//***********************  Loop ********************
  void loop()                                      // Rotina de loop
  {
    dimming=analogRead(pinAnalog);                 // Lê valor do potenciômetro
    dimming=map(dimming,0,1023,0,5000);            // Calcula 0 = 0 até 1023 = 7900
    if (digitalRead(ZCross))                       // Faça se detectou pulso de zerocross
    {
      delayMicroseconds(dimming);                  // Retardo calculado em relação a zerocross
      digitalWrite(Triac, HIGH);                   // Dispara o Triac  
      delayMicroseconds(100);                      // Duração do pulso de disparo                  
      digitalWrite(Triac, LOW);                    // Desliga pulso de disparo  
    }
  }
