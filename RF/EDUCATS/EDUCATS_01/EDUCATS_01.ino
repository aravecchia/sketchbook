#include <Arduino.h>

// Código inicial: https://meetarduino.wordpress.com/
/*
Desenvolvido por Alexandre Aravecchia
aravecchia@gmail.com
www.aravecchia.weebly.com
*/
// Apoio: Labdegaragem, CriaLivre e Revista Espirito Livre

#define echoPin 2
#define trigPin 3
#define RED 4
#define GREEN 5

//Controle do motor de passo:
int A = 6;
int B = 7;
int C = 8;
int D = 9;
int matriz[16][4] = {
  {
    0, 0, 0, 1
  }
  ,
  {
    0, 0, 1, 1
  }
  ,
  {
    0, 0, 1, 0
  }
  ,
  {
    0, 1, 1, 0
  }
  ,
  {
    0, 1, 0, 0
  }
  ,
  {
    1, 1, 0, 0
  }
  ,
  {
    1, 0, 0, 0
  }
  ,
  {
    1, 0, 0, 1
  }
};

void setup()
{
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);

  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);

  digitalWrite(A, LOW);
  digitalWrite(B, LOW);
  digitalWrite(C, LOW);
  digitalWrite(D, LOW);
}


void motor(int m[])
{
  digitalWrite(A, m[0]);
  digitalWrite(B, m[1]);
  digitalWrite(C, m[2]);
  digitalWrite(D, m[3]);
}

void loop()
{
  int valor[8];
  int memoria[8];
  for (int x = 0; x < 8; x++)
  {
    motor(matriz[x]);
    long duration, distance; //http://arduino.cc/en/Reference/Long
    digitalWrite(trigPin, LOW);
    //seta o pino 12 com um pulso baixo "LOW" ou desligado
    delayMicroseconds(2); // delay de 2 microssegundos
    digitalWrite(trigPin, HIGH); //seta o pino 12 com pulso alto "HIGH" ou ligado ou ai
    delayMicroseconds(10); //delay de 10 microssegundos
    digitalWrite(trigPin, LOW); //seta o pino 12 com pulso baixo novamente
    duration = pulseIn(echoPin, HIGH); //pulseIn lê o tempo entre a chamada e o pino e
    //Esse calculo é baseado em s = v . t, lembrando que o tempo vem dobrado
    //porque é o tempo de ida e volta do ultrassom

    distance = (duration / 2) / 29.1;
    valor[x] = distance;

    if (memoria[x] == 0)
    {
      digitalWrite(RED, LOW);
      digitalWrite(GREEN, HIGH);
      Serial.print("Mapeando o terreno...");
    }
    else if (valor[x] == memoria[x])
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
        Serial.print(valor[x]);
        Serial.println(" cm");
      }
      else
      {
        Serial.println("Nada ao alcance!");
      }
    }
    memoria[x] = valor[x];
        delay(10);
  }
    for (int x = 8; x >=0; x--)
  {
    motor(matriz[x]);
    long duration, distance; //http://arduino.cc/en/Reference/Long
    digitalWrite(trigPin, LOW);
    //seta o pino 12 com um pulso baixo "LOW" ou desligado
    delayMicroseconds(2); // delay de 2 microssegundos
    digitalWrite(trigPin, HIGH); //seta o pino 12 com pulso alto "HIGH" ou ligado ou ai
    delayMicroseconds(10); //delay de 10 microssegundos
    digitalWrite(trigPin, LOW); //seta o pino 12 com pulso baixo novamente
    duration = pulseIn(echoPin, HIGH); //pulseIn lê o tempo entre a chamada e o pino e
    //Esse calculo é baseado em s = v . t, lembrando que o tempo vem dobrado
    //porque é o tempo de ida e volta do ultrassom

    distance = (duration / 2) / 29.1;
    valor[x] = distance;

    if (memoria[x] == 0)
    {
      digitalWrite(RED, LOW);
      digitalWrite(GREEN, HIGH);
      Serial.print("Mapeando o terreno...");
    }
    else if (valor[x] == memoria[x])
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
        Serial.print(valor[x]);
        Serial.println(" cm");
      }
      else
      {
        Serial.println("Nada ao alcance!");
      }
    }
    memoria[x] = valor[x];
    delay(10);
  }
}

/*
   #include <Ultrasonic.h>
  // funcão do ultrasonic nos pinos 12 e 13
  Ultrasonic ultrasonic(12,13);
  void setup()
  {
  Serial.begin(9600); //inicia a porta serial
  pinMode(echoPin, INPUT); // seta pino como entrada
  pinMode(trigPin, OUTPUT); // seta pino saída
  }
  void loop()
  {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // A função Ranging converte o tempo de resposta em centímetros e seta na variável int distancia = (ultrasonic.Ranging(CM));
  Serial.print("Distancia em CM: ");
  Serial.println(distancia);
  delay(1000); //espera 1 segundo para fazer a leitura novamente
  }
*/


