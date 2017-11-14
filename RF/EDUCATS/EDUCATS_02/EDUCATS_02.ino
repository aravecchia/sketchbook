#include <Arduino.h>

// Código inicial: https://meetarduino.wordpress.com/
// Desenvolvido por CYBEROHM.COM
// Apoio: Labdegaragem, CriaLivre e Revista Espirito Livre

#define ECHO_1 2
#define TRIG_1 8
#define RED 11
#define GREEN 12

void setup()
{
  Serial.begin (9600);
  pinMode(TRIG_1, OUTPUT);
  pinMode(ECHO_1, INPUT);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);

}



void loop()
{
  int valor;
  int memoria;
  for (int x = 0; x < 8; x++)
  {
    long duration, distance; //http://arduino.cc/en/Reference/Long
    digitalWrite(TRIG_1, LOW);
    //seta o pino 12 com um pulso baixo "LOW" ou desligado
    delayMicroseconds(2); // delay de 2 microssegundos
    digitalWrite(TRIG_1, HIGH); //seta o pino 12 com pulso alto "HIGH" ou ligado ou ai
    delayMicroseconds(10); //delay de 10 microssegundos
    digitalWrite(TRIG_1, LOW); //seta o pino 12 com pulso baixo novamente
    duration = pulseIn(ECHO_1, HIGH); //pulseIn lê o tempo entre a chamada e o pino e
    //Esse calculo é baseado em s = v . t, lembrando que o tempo vem dobrado
    //porque é o tempo de ida e volta do ultrassom

    distance = (duration / 2) / 29.1;
    distance = distance;

    if (memoria == 0)
    {
      digitalWrite(RED, LOW);
      digitalWrite(GREEN, HIGH);
      Serial.print("Mapeando o terreno...");
    }
    else if (distance == memoria)
    {
      digitalWrite(RED, LOW);
      digitalWrite(GREEN, HIGH);
      Serial.println("Terreno limpo.");
    }
    else
    {
      Serial.print("GATO DETECTADO ! - ");
      digitalWrite(RED, HIGH);
      digitalWrite(GREEN, LOW);
      if (distance <= 5000)
      {
        Serial.print("Alvo no setor");
        Serial.print(x);
        Serial.print(" -> Distância: ");
        Serial.print(distance);
        Serial.println(" cm");
      }
      else
      {
        Serial.println("Nada ao alcance!");
      }
    }
    memoria = distance;
        delay(10);
  }
    long duration, distance; //http://arduino.cc/en/Reference/Long
    digitalWrite(TRIG_1, LOW);
    //seta o pino 12 com um pulso baixo "LOW" ou desligado
    delayMicroseconds(2); // delay de 2 microssegundos
    digitalWrite(TRIG_1, HIGH); //seta o pino 12 com pulso alto "HIGH" ou ligado ou ai
    delayMicroseconds(10); //delay de 10 microssegundos
    digitalWrite(TRIG_1, LOW); //seta o pino 12 com pulso baixo novamente
    duration = pulseIn(ECHO_1, HIGH); //pulseIn lê o tempo entre a chamada e o pino e
    //Esse calculo é baseado em s = v . t, lembrando que o tempo vem dobrado
    //porque é o tempo de ida e volta do ultrassom

    distance = (duration / 2) / 29.1;

    if (memoria == 0)
    {
      digitalWrite(RED, LOW);
      digitalWrite(GREEN, HIGH);
      Serial.print("Mapeando o terreno...");
    }
    else if (distance == memoria)
    {
      digitalWrite(RED, LOW);
      digitalWrite(GREEN, HIGH);
      Serial.println("Terreno limpo.");
    }
    else
    {
      Serial.print("GATO DETECTADO ! - ");
      digitalWrite(RED, HIGH);
      digitalWrite(GREEN, LOW);
      if (distance <= 5000)
      {
        Serial.print("Alvo: ");
        Serial.print(distance);
        Serial.println(" cm");
      }
      else
      {
        Serial.println("Nada ao alcance!");
      }
    }
    delay(10);
  }

/*
   #include <Ultrasonic.h>
  // funcão do ultrasonic nos pinos 12 e 13
  Ultrasonic ultrasonic(12,13);
  void setup()
  {
  Serial.begin(9600); //inicia a porta serial
  pinMode(ECHO_1, INPUT); // seta pino como entrada
  pinMode(TRIG_1, OUTPUT); // seta pino saída
  }
  void loop()
  {
  digitalWrite(TRIG_1, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_1, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_1, LOW);
  // A função Ranging converte o tempo de resposta em centímetros e seta na variável int distancia = (ultrasonic.Ranging(CM));
  Serial.print("Distancia em CM: ");
  Serial.println(distancia);
  delay(1000); //espera 1 segundo para fazer a leitura novamente
  }
*/


