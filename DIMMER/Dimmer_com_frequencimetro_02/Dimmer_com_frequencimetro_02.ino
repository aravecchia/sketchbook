#include <Arduino.h>

// Programa que conta os "meio­ciclos" da onda senoidal fornecida
//concessionária de energia elétrica.

// Variável que armazena os pulsos. Como será chamada dentro da roti
// ContaPulsos(), que é uma rotina de interrupção,
// tem que ter o comando volatile.

volatile unsigned int sensor = A0;

const int controle = 3;
const int led = 13;
// Variables will change:
int optoState;       // Estado do opto. Se estiver HIGH, tensao diferente de zero.
//Se estiver em LOW, tensao = zero. Presisamente o que queremos.
int lastOptoState;     // O estado anterior do sensor.
long lastMillis;     //define a contagem do tempo.

int D;
int visor;

void setup()
{
  Serial.begin(9600);
  // Essa instrução faz com que, a cada vez que o pino 2 passa muda de estado
  // (RISING), a rotina função() é chamada. O número 0 define o
  // pino 2 e o número 1 define o pino 3.
  //attachInterrupt(pino, função, modo);
  //pino = 0 para pino 2, 1 para pino 3,
  //função = função a ser chamada em void função(),
  //modo = RISING FALLING CHANGE

  attachInterrupt(0, Dimmer, RISING); //RISING FALLING CHANGE

  pinMode(led, OUTPUT);
  pinMode(controle, OUTPUT);
  pinMode(sensor, INPUT);
}

void loop()
{
 digitalWrite(controle, HIGH);
  digitalWrite(led, HIGH);
  Serial.print(D);
  Serial.println(" ms");
}
// Rotina que é chamada a cada meio ciclo, incrementando a variável
void Dimmer()
{
  D = map(analogRead(sensor), 0, 1023, 0, 16); // o delay de controle
  digitalWrite(controle, LOW);
  digitalWrite(led, LOW);
  delay(D);
  digitalWrite(controle, HIGH);
  digitalWrite(led, HIGH);
  Serial.print(D);
  Serial.println(" ms");
}





//                                      +-----+
//          +----[PWR]-------------------| USB |--+
//         |                            +-----+  |
//         |         GND/RST2  [ ][ ]            |
//         |       MOSI2/SCK2  [ ][ ]  A5/SCL[ ] |   C5
//         |          5V/MISO2 [ ][ ]  A4/SDA[ ] |   C4
//         |                             AREF[ ] |
//         |                              GND[ ] |
//         | [ ]N/C                    SCK/13[ ] |   B5
//         | [ ]v.ref                 MISO/12[ ] |   .
//         | [ ]RST                   MOSI/11[ ]~|   .
//         | [ ]3V3    +---+               10[ ]~|   .
//         | [ ]5v     | A |                9[ ]~|   .
//         | [ ]GND   -| R |-               8[ ] |   B0
//         | [ ]GND   -| D |-                    |
//         | [ ]Vin   -| U |-               7[ ] |   D7
//         |          -| I |-               6[ ]~|   .
//         | [ ]A0    -| N |-               5[ ]~|   .
//         | [ ]A1    -| O |-               4[ ] |   .
//         | [ ]A2     +---+           INT1/3[ ]~|   .
//         | [ ]A3                     INT0/2[ ] |   .
//         | [ ]A4/SDA  RST SCK MISO     TX>1[ ] |   .
//         | [ ]A5/SCL  [ ] [ ] [ ]      RX<0[ ] |   D0
//         |            [ ] [ ] [ ]              |
//         |  UNO_R3    GND MOSI 5V  ____________/
//          \_______________________/
//
//    http://busyducks.com/ascii-art-arduinos
//
//
//
//                                      +-----+
//         +----[PWR]-------------------| USB |--+
//         |                            +-----+  |
//         |           GND/RST2  [ ] [ ]         |
//         |         MOSI2/SCK2  [ ] [ ]  SCL[ ] |   D0
//         |            5V/MISO2 [ ] [ ]  SDA[ ] |   D1
//         |                             AREF[ ] |
//         |                              GND[ ] |
//         | [ ]N/C                    SCK/13[ ]~|   B7
//         | [ ]v.ref                 MISO/12[ ]~|   B6
//         | [ ]RST                   MOSI/11[ ]~|   B5
//         | [ ]3V3      +----------+      10[ ]~|   B4
//         | [ ]5v       | ARDUINO  |       9[ ]~|   H6
//         | [ ]GND      |   MEGA   |       8[ ]~|   H5
//         | [ ]GND      +----------+            |
//         | [ ]Vin                         7[ ]~|   H4
//         |                                6[ ]~|   H3
//         | [ ]A0                          5[ ]~|   E3
//         | [ ]A1                          4[ ]~|   G5
//         | [ ]A2                     INT5/3[ ]~|   E5
//         | [ ]A3                     INT4/2[ ]~|   E4
//         | [ ]A4                       TX>1[ ]~|   E1
//         | [ ]A5                       RX<0[ ]~|   E0
//         | [ ]A6                               |
//         | [ ]A7                     TX3/14[ ] |   J1
//         |                           RX3/15[ ] |   J0
//         | [ ]A8                     TX2/16[ ] |   H1
//         | [ ]A9                     RX2/17[ ] |   H0
//         | [ ]A10               TX1/INT3/18[ ] |   D3
//         | [ ]A11               RX1/INT2/19[ ] |   D2
//         | [ ]A12           I2C-SDA/INT1/20[ ] |   D1
//         | [ ]A13           I2C-SCL/INT0/21[ ] |   D0
//         | [ ]A14                              |
//         | [ ]A15                              |   Ports:
//         |                RST SCK MISO         |    22=A0  23=A1
//         |         ICSP   [ ] [ ] [ ]          |    24=A2  25=A3
//         |                [ ] [ ] [ ]          |    26=A4  27=A5
//         |                GND MOSI 5V          |    28=A6  29=A7
//         | G                                   |    30=C7  31=C6
//         | N 5 5 4 4 4 4 4 3 3 3 3 3 2 2 2 2 5 |    32=C5  33=C4
//         | D 2 0 8 6 4 2 0 8 6 4 2 0 8 6 4 2 V |    34=C3  35=C2
//         |         ~ ~                         |    36=C1  37=C0
//         | @ # # # # # # # # # # # # # # # # @ |    38=D7  39=G2
//         | @ # # # # # # # # # # # # # # # # @ |    40=G1  41=G0
//         |           ~                         |    42=L7  43=L6
//         | G 5 5 4 4 4 4 4 3 3 3 3 3 2 2 2 2 5 |    44=L5  45=L4
//         | N 3 1 9 7 5 3 1 9 7 5 3 1 9 7 5 3 V |    46=L3  47=L2
//         | D                                   |    48=L1  49=L0    SPI:
//         |                                     |    50=B3  51=B2     50=MISO 51=MOSI
//         |     2560                ____________/    52=B1  53=B0     52=SCK  53=SS
//          \_______________________/
//
//         http://busyducks.com/ascii-art-arduinos
//
//
//
//                      +-----+
//         +------------| USB |------------+
//         |            +-----+            |
//    B5   | [ ]D13/SCK        MISO/D12[ ] |   B4
//         | [ ]3.3V           MOSI/D11[ ]~|   B3
//         | [ ]V.ref     ___    SS/D10[ ]~|   B2
//    C0   | [ ]A0       / N \       D9[ ]~|   B1
//    C1   | [ ]A1      /  A  \      D8[ ] |   B0
//    C2   | [ ]A2      \  N  /      D7[ ] |   D7
//    C3   | [ ]A3       \_0_/       D6[ ]~|   D6
//    C4   | [ ]A4/SDA               D5[ ]~|   D5
//    C5   | [ ]A5/SCL               D4[ ] |   D4
//         | [ ]A6              INT1/D3[ ]~|   D3
//         | [ ]A7              INT0/D2[ ] |   D2
//         | [ ]5V                  GND[ ] |
//    C6   | [ ]RST                 RST[ ] |   C6
//         | [ ]GND   5V MOSI GND   TX1[ ] |   D0
//         | [ ]Vin   [ ] [ ] [ ]   RX1[ ] |   D1
//         |          [ ] [ ] [ ]          |
//         |          MISO SCK RST         |
//         | NANO-V3                       |
//         +-------------------------------+
//
//         http://busyducks.com/ascii-art-arduinos




