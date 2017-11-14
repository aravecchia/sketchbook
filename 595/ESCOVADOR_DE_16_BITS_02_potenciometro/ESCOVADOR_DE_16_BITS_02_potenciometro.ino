#include <Arduino.h>

/*   Codigo de Expansao de Portas para Arduino, utilizando Shift Register 74HC-595.
 
 Desenvolvido por Alexandre (tiodocomputador@gmail.com)
 
 Apoio do Laboratorio de Gabagem (labdegaragem.com): Jonatas Freitas, Almir Bispo Filho,
 Daniel (Oraculo X), Daniel Jedi, Adriano Alcantara e Wiechert (o destruidor).
 Esqueci de alguem? Me lembre, sou meio lesado!
 
 Este codigo liga 16 leds simultaneamente e de forma independente.
 Leds -> transistores -> relays -> contatores -> motores trifasicos e
 o que mais o projeto exigir.
 
 Esta tecnica de expansao com Shift Register permite ligar centenas ou milhares
 de dispositivos com apenas 3 pinos do Arduino.
 
 Na pratica, limitacoes eletro-eletronicas e de gerenciamento de memoria merecem ser
 estudadas mais detalhadamente.
 
 Teoricamente, podem ser ligados infinitos dispositivos.
 */

// Declara o pino Latch
int LATCH = 2; 

// Declara o pino de envio de dados
int DATA = 3;

// Declara o pino de Clock
int CLOCK = 4;

// Declara o pino de leitura analogica
// (um potenciometro ou sensor com resistor de pull-up/pull-dow)
int analogPin = A0;

void setup()
{
  // Inicia a comunicacao serial
  Serial.begin(9600);

  // Define os modos de cada pino como entrada ou saida
  pinMode(LATCH, OUTPUT);
  pinMode(CLOCK, OUTPUT);
  pinMode(DATA, OUTPUT);
  pinMode(analogPin, INPUT);
}

void loop()
{
  // Tempo de espera.
  int t=10;

  // Declara a variavel sensor e mapeia a leitura do sensor num intervalo de 0 a 20,
  // se estiver usando um potenciometro comum.
  // O correto seria de 0 a 16. Isso pode ser feito dimensionando
  // corretamente o resistor de pull-up/pull-down do sensor.
  int sensor = map(analogRead(analogPin), 0, 1023, 0,20);  

  // Declara a variavel x definindo o primeiro bit como HIGH.
  // Esta linha poderia ser na forma decimal, simplesmente:
  // int x = 1;
  // mas preferi colocar na forma binaria com 16 digitos
  // para facilitar o entendimento, ja que estamos lidando com o 
  // deslocamento de bits ao longo de 2 Bytes.
  // No caso, o bit da direita sera manipulado:
  int x= 0xb0000000000000001;

  // Pense em Latch como um muro que represa os bits.
  // Se o muro abaixa, os bits fluem pelo DATA.
  // Se o muro sobe, param de fluir como se fossem represados.
  // Em LOW, inicia a transmissao de DATA. 
  digitalWrite(LATCH, LOW);

  // Se a tensao no potenciometro for proxima de 0V, o mapeamento 
  // map(analogRead(analogPin), 0, 1023, 0,20)
  // fara com que a variavel sensor seja zero. 
  // Entao, se a variavel sensor for igual a zero...
  if (sensor==0)
  {
    // Envia 2 Bytes para o DATA, um para cada HC-595, desligando todos os LEDs.
    shiftOut(DATA, CLOCK, MSBFIRST, 0);
    shiftOut(DATA, CLOCK, MSBFIRST, 0);
    // Como funciona o shiftOut:

    // DATA avisa que o Byte esta pronto para ser enviado para o 595 mestre
    // ou para o ultimo escravo.

    // CLOCK liga ou desliga 8x, alternando uma vez para cada bit enviado,
    // e avisando ao CI que o proximo bit pode ser enviado.

    // MSBFIRST (Mostly Significant Bit First)
    // envia o bit mais significante primeiro (esquerda)
    // Neste caso, ele envia o primeiro Byte para o ultimo 595,
    // sendo que o ultimo bit eh enviado primeiro, (veja a ligacoes do CI)
    // o segundo Byte vai para o penultimo CI e assim por diante,
    // ate o ultimo Byte, que vai para o 595 mestre.

    // LSBFIRST (Less Significant Bit First)
    // envia o bit menos significante primeiro (direita)
    // Neste caso, eh o contratio: ele envia o primeiro Byte para o 595 mestre,
    // sendo que o primeiro bit eh enviado primeiro, (veja a ligacoes do CI)
    // o segundo Byte para o segundo 595 e assim por diante,
    // ate o ultimo Byte, que vai para o ultimo 595.

    // O ultimo valor de shiftOut(DATA, CLOCK, MSBFIRST, x) 
    // que chamamos simplesmente de x
    // eh o DATA em si,
    // ou dado propriamente dito. Apenas um Byte.

    // Se mandarmos apenas um Byte e colocarmos LATCH em HIGH, este Byte sera transmitido
    // para o proximo 595 quando LATCH voltar a LOW. Cada vez que LATCH alternar entre HIGH
    // e LOW, o Byte sera transferido para o proximo 595 da fila, infinitamente.

    // Como queremos enviar um Byte especifico para cada 595, se tivermos 200 CIs 595,
    // temos que colocar LATCH em LOW para iniciar a transmissao, entao
    // enviar 200 Bytes especificos, que serao escritos no codigo na mesma ordem em que seus
    // respectivos CIs estiverem conectados na fila do circuito (ver pinos 9 e 14 do CI 595)

    // Cada CI vai escrever seu respectivo Byte de acordo como deve ir para a fila de CIs
    // do circuito, correspondente a ordem de cada Byte no codigo.

    // Colocando o LATCH novamente em HIGH, fechamos a transmissao.
    // Colocando em LOW, abrimos novamente, mandamos mais 200 Bytes, fechamos, e assim
    // por diante.

  }

  // Senao... agora comeca a diversao :D)
  else
  {
    // Como estamos usando MSBFIRST, mandamos o primeiro Byte para o ultimo CI:
    shiftOut(DATA, CLOCK, MSBFIRST, (x<<(sensor-8))-1);

    // E o ultimo Byte para o mestre:
    shiftOut(DATA, CLOCK, MSBFIRST, (x<<sensor)-1);

    //Para o PRIMEIRO BYTE:
    // (x<<(sensor-8))-1

      // Se a leitura do sensor for 3:
    // (x<<(sensor-8)) - 1 = 
    // (1 << (3 - 8)) -1) =
    // (1 << (-5)) -1 = 
    // (1 >> 5) -1 = 
    // O bit sai a direita do Byte e eh anulado
    // 0-1 = 0
    // Novamente o bit sai a direita do Byte e eh anulado

    // Se a leitura do sensor for 9:
    // (x<<(sensor-8)) - 1 = 
    // (1 << (9 - 8)) -1) =
    // (1 << 1) -1 = 
    // (10) -1 = 10-1 = 1

      // Se a leitura do sensor for 15:
    // (x<<(sensor-8)) - 1 = 
    // (1 << (15 - 8)) -1) =
    // (1 << 7) -1 = 
    // (1000 0000) -1 = 111 1111 Este sera o Byte da esquerda!!!

    //Para o SEGUNDO BYTE:
    // (x<<sensor)-1)

    // Se a leitura do sensor for 3:
    // (x<<sensor)-1)
    // (1 << 3) -1 =
    // 1000 - 1 = 111
    // Liga os 3 primeiros relays.

      // Se a leitura do sensor for 9:
    // (x<<sensor)-1)
    // (1 << 9) -1 =
    // 10 0000 0000 - 1 = 
    // 1 1111 1111
    // Como o 595 so envia 1 Byte, o bit da esquerda eh desprezado.

      // Se a leitura do sensor for 15:
    //(x<<sensor)-1)
    // (1 << 15) -1 =
    // 1000 0000 0000 0000 -1 =
    // 111 1111 1111 1111
    // Como o 595 so envia 1 Byte, os 7 bits restantes a esquerda sao desprezados. 
  }
  // Levanta o muro LATCH, fecha a transmissao (represam os bits)
  digitalWrite(LATCH, HIGH);
  
  // Escreve na serial o resultado e confere o codigo:
  Serial.print("sensor = ");
  Serial.print(((x<<sensor-8)-1), BIN);
  Serial.print(" - "); 
  Serial.println(((x<<sensor)-1), BIN);
  delay(t);
}


