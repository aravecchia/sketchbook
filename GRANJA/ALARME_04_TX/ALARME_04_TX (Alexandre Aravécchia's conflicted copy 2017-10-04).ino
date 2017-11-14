/*Desenvolvido por Alexandre Aravecchia
  Projetista, desenvolvedor, programador
 aravecchia@gmail.com
 www.aravecchia.weebly.com
 */
// Apoio:
//   Laboratorio de Garagem - www.labdegaragem.com
//   Labirito - www.labirito.com
//   junho/2017
#include <Arduino.h>
#include <math.h>
#include <VirtualWire.h>

#define	C0 16.35
#define	Db0	17.32
#define	D0	18.35
#define	Eb0	19.45
#define	E0	20.60
#define	F0	21.83
#define	Gb0	23.12
#define	G0	24.50
#define	Ab0	25.96
#define	LA0	27.50
#define	Bb0	29.14
#define	B0	30.87
#define	C1	32.70
#define	Db1	34.65
#define	D1	36.71
#define	Eb1	38.89
#define	E1	41.20
#define	F1	43.65
#define	Gb1	46.25
#define	G1	49.00
#define	Ab1	51.91
#define	LA1	55.00
#define	Bb1	58.27
#define	B1	61.74
#define	C2	65.41
#define	Db2	69.30
#define	D2	73.42
#define	Eb2	77.78
#define	E2	82.41
#define	F2	87.31
#define	Gb2	92.50
#define	G2	98.00
#define	Ab2	103.83
#define	LA2	110.00
#define	Bb2	116.54
#define	B2	123.47
#define	C3	130.81
#define	Db3	138.59
#define	D3	146.83
#define	Eb3	155.56
#define	E3	164.81
#define	F3	174.61
#define	Gb3	185.00
#define	G3	196.00
#define	Ab3	207.65
#define	LA3	220.00
#define	Bb3	233.08
#define	B3	246.94
#define	C4	261.63
#define	Db4	277.18
#define	D4	293.66
#define	Eb4	311.13
#define	E4	329.63
#define	F4	349.23
#define	Gb4	369.99
#define	G4	392.00
#define	Ab4	415.30
#define	LA4	440.00
#define	Bb4	466.16
#define	B4	493.88
#define	C5	523.25
#define	Db5	554.37
#define	D5	587.33
#define	Eb5	622.25
#define	E5	659.26
#define	F5	698.46
#define	Gb5	739.99
#define	G5	783.99
#define	Ab5	830.61
#define	LA5	880.00
#define	Bb5	932.33
#define	B5	987.77
#define	C6	1046.50
#define	Db6	1108.73
#define	D6	1174.66
#define	Eb6	1244.51
#define	E6	1318.51
#define	F6	1396.91
#define	Gb6	1479.98
#define	G6	1567.98
#define	Ab6	1661.22
#define	LA6	1760.00
#define	Bb6	1864.66
#define	B6	1975.53
#define	C7	2093.00
#define	Db7	2217.46
#define	D7	2349.32
#define	Eb7	2489.02
#define	E7	2637.02
#define	F7	2793.83
#define	Gb7	2959.96
#define	G7	3135.96
#define	Ab7	3322.44
#define	LA7	3520.01
#define	Bb7	3729.31
#define	B7	3951.07
#define	C8	4186.01
#define	Db8	4434.92
#define	D8	4698.64
#define	Eb8	4978.03
// DURATION OF THE NOTES 
#define BPM 120    //  you can change this value changing all the others
#define H 2*Q //half 2/4
#define Q 60000/BPM //quarter 1/4 
#define E Q/2   //eighth 1/8
#define S Q/4 // sixteenth 1/16
#define W 4*Q // whole 4/4


int t=500;
int LATCH = 4; 
int DATA = 5;
int CLK = 6;
// define os pinos de latch, data e clock do 74HC595 que controla o display da Celsius do ambiente
// ver datasheet {boa sorte!)

int botao = 7; //botao seletor-> alterna a leitura do display entre a temperatura atual e a temperatura de regulagem


// Celsius-base, notem que estou trabalhando com 10x a Celsius real
// para facilitar a codificacao dos displays de 7 segmentos, que so trabalha com numeros binarios e inteiros

byte sensor = 8;
byte trimpot = A0;
byte digito[10]= {
  B11111100,B01100000,B11011010,B11110010,B01100110,B10110110,B10111110,B11100000,B11111110,B11110110};
// matrizes de 10 termos, cada um define um Byte diferente para cada
// digito de 0 a 9 no display, ou seja, liga um conjunto especifico de portas do 74hc595
// que acende um conjunto especifico de LEDs.


//int BETA =  3870; //Calibrar este valor utilizando um termometro de precisao externo como comparacao
int BETA = 3870;
float Ro = 90000; //Resistencia tpica de um termistor de 100k
float To = 25 + 273; //Transforma Celsius de referencia do Termistor de Celsius para Kelvin

float pico; //Tempo
float vale;
float Periodo;
float Frequencia;

float Kelvin;
float Celsius = Kelvin - 273;

float R; // Resistencia do Termistor
float R2 = 10000; //Segundo resistor do NE-222
float Cap1 = 1; // Capacitor principal do NE-555 em MICROFARADAY;

const int LedAlarme=10;         // Led que avisa quando a temperatura cair
const int LedTX = 9;            // Led pisca quando a transmissao inicia
const int LedSeletor = 11;      // Led acende quando o botao seletor de temperatura minima eh acionado
const int Alarme = 2;           // Alarme sonoro
const int transmit_pin = 12;    // Transmissor RF
const int receive_pin = 2;      // Pino de recepcao, nao deveria ser necessario e esta conflitando com alarme sonoro. Verificar sua necessidade no circuito
const int transmit_en_pin = 3;  // Segundo pino de transmissao, nao deveria ser necessario. Verificar sua necessidade no circuito.

void setup()
{
  Serial.begin(9600);
  pinMode(sensor, INPUT_PULLUP);
  pinMode(trimpot, INPUT);
  pinMode(botao, INPUT);
  pinMode(LedTX, OUTPUT);
  pinMode(LedAlarme, OUTPUT);
  pinMode(LedSeletor, OUTPUT);

  pinMode(LATCH, OUTPUT);
  pinMode(CLK, OUTPUT);
  pinMode(DATA, OUTPUT);

  Serial.println("Iniciando transmissao...");
  // Initialise the IO and ISR
  vw_set_tx_pin(transmit_pin);
  vw_set_rx_pin(receive_pin);
  vw_set_ptt_pin(transmit_en_pin);
  vw_set_ptt_inverted(true); // Required for DR3100
  vw_setup(2000);       // Bits per sec

}

void loop()
{
  delay(t);
  // Funcao pulseIn para medir a frequencia do NE-555 com precisao
  pico = pulseIn(sensor, HIGH);
  vale = pulseIn(sensor, LOW);
  Periodo = (pico + vale);
  Frequencia = 1000000 / Periodo;

  // Calcula a resistencia do termistor ligado ao NE-555
  R = ((1.44 * Periodo) / Cap1) - (2 * R2);

  // Calcula a Celsius pela equacao reduzida de Steinhart-Hart para sensores NTC
  Kelvin = 1 / ( (1 / To) + ((log(R / Ro) / BETA)));

  // Converte Kelvin para Celsius e multiuplica por 10 para facilitar a leitura pelo display
  Celsius = 10*(Kelvin - 273);
  // Botao que regula a temperatura minima, acionado ao apertar o botao tipo pushbutton na variavel botao, pino 7;
  int regulagem = analogRead(trimpot);

  int tempbase=map(regulagem, 0, 1023, 400, 0); // Temperatura minima desejada, regulada pelo trimpot
  tempbase = tempbase/10;
  tempbase = 10*tempbase;

  boolean State = digitalRead(botao); // Variavel que checa o estado do botao seletor de funcao

    // Lembre-se que a temperatura esta sendo medida em deca-Celcius (Celsius * 10), para facilitar a transcricao no display utilizando int ao inves de float
  int z = Celsius/100;
  int y = (Celsius - 100*z)/10;
  int x = Celsius - 100*z - 10*y;

  int c = tempbase/100;
  int b = (tempbase - 100*c)/10;
  int a = tempbase - 100*c - 10*b;

  // Se o botao seletor nao estiver acionado, o circuito funciona normalmente transmitindo a temperatura para o display e para o RF
  if(State == 0)
  {    
    digitalWrite(LATCH, LOW); // Abre a fila de transmissao do 74HC595

    shiftOut(DATA, CLK, LSBFIRST, digito[x]); //primeiro CI recebe 1 Byte
    shiftOut(DATA, CLK, LSBFIRST, digito[y]+1);  //segundo CI recebe 1 Byte

    // Z eh o primeiro digito do valor de temperatura. Se a temperatura fica abaixo de 10 graus, nao eh necessario estrever 09.9, entao este digito nao eh transmitido.
    if (z==0)
    {
      shiftOut(DATA, CLK, LSBFIRST, 0); //terceiro CI recebe 1 Byte
    }
    // Senao escreva o primeiro digito normalmente:
    else
    {
      shiftOut(DATA, CLK, LSBFIRST, digito[z]); //terceiro CI recebe 1 Byte
    }
    digitalWrite(LATCH, HIGH); // Abre a fila de transmissao do 74HC595

    //Mensagem a ser transmitida
    char msg[12] = {
      'T','=', '#','#','#', ' ','-', ' ','T', 'b', '=', '#'                 };

    // POG Detected!!!! A ideia era transmitir a temperatura em deca-Celsius, como um int convertido em char, mas isto faz
    // com que o valor supere a pilha de memoria ao passar de 254 (1 Byte). 
    // O estranho eh que funciona para tempbase mas nao para Celsius.
    // Ciencia da Computacao nao eh uma ciencia exata, eh uma ciencia exoterica O.o
    // Tentei transmitir o valor como um float, mas nao funcionou.
    // Possivelmente, funcionara trocando a mensagem de char msg[n] para int char msg[n], melhoria a ser implementada 
    // numa versao futura do software.
    //Por enquanto, optei por transmitir os digitos separadamente, como char, e converte-los em int no receptor. 
    // Funcionou, mas uma POG eh uma POG e deve ser eliminada na proxima versao do software.
    // Que o Silvio Palmieri nao veja este comentario!
    msg[2] = z; 
    msg[3] = y;
    msg[4] = x;
    msg[11] = tempbase/10;



    digitalWrite(LedTX, HIGH); // Flash a light to show transmitting
    vw_send((uint8_t *)msg, 12);
    vw_wait_tx(); // Wait until the whole message is gone
    digitalWrite(LedTX, LOW);
    digitalWrite(LedSeletor, LOW);
  }

  else
  {
    digitalWrite(LATCH, LOW);
    shiftOut(DATA, CLK, LSBFIRST, digito[a]); //primeiro CI recebe 1 Byte
    shiftOut(DATA, CLK, LSBFIRST, digito[b]+1);  //segundo CI recebe 1 Byte
    shiftOut(DATA, CLK, LSBFIRST, digito[c]); //terceiro CI recebe 1 Byte
    digitalWrite(LATCH, HIGH);
    digitalWrite(LedSeletor, HIGH);
  }

  Serial.print("Base: ");
  Serial.print(tempbase/10);
  Serial.print(" - Celsius: ");
  Serial.print(Celsius/10);
  Serial.print(" - ");
  Serial.print(" Botao: ");
  Serial.print(State);
  Serial.print(" - tempbase-2: ");
  Serial.print((tempbase/10)-2);
  Serial.print(" - Alarme: ");

  if ((Celsius/10)<((tempbase/10)-2))
  {
    Serial.println("HIGH");
    digitalWrite(LedAlarme, HIGH);
    //   tone(Alarme, 700, 5*t); //int duration = 250;
    // how long the tone(speakerPin, frequency, duration);delay(1000);

    //tone(pin, note, duration)
    tone(Alarme,LA3,Q); 
    delay(1+Q); //delay duration should always be 1 ms more than the note in order to separate them.
    tone(Alarme,LA3,Q);
    delay(1+Q);
    tone(Alarme,LA3,Q);
    delay(1+Q);
    tone(Alarme,F3,E+S);
    delay(1+E+S);
    tone(Alarme,C4,S);
    delay(1+S);

    tone(Alarme,LA3,Q);
    delay(1+Q);
    tone(Alarme,F3,E+S);
    delay(1+E+S);
    tone(Alarme,C4,S);
    delay(1+S);
    tone(Alarme,LA3,H);
    delay(1+H);

    tone(Alarme,E4,Q); 
    delay(1+Q); 
    tone(Alarme,E4,Q);
    delay(1+Q);
    tone(Alarme,E4,Q);
    delay(1+Q);
    tone(Alarme,F4,E+S);
    delay(1+E+S);
    tone(Alarme,C4,S);
    delay(1+S);

    tone(Alarme,Ab3,Q);
    delay(1+Q);
    tone(Alarme,F3,E+S);
    delay(1+E+S);
    tone(Alarme,C4,S);
    delay(1+S);
    tone(Alarme,LA3,H);
    delay(1+H);

    tone(Alarme,LA4,Q);
    delay(1+Q);
    tone(Alarme,LA3,E+S);
    delay(1+E+S);
    tone(Alarme,LA3,S);
    delay(1+S);
    tone(Alarme,LA4,Q);
    delay(1+Q);
    tone(Alarme,Ab4,E+S);
    delay(1+E+S);
    tone(Alarme,G4,S);
    delay(1+S);

    tone(Alarme,Gb4,S);
    delay(1+S);
    tone(Alarme,E4,S);
    delay(1+S);
    tone(Alarme,F4,E);
    delay(1+E);
    delay(1+E);//PAUSE
    tone(Alarme,Bb3,E);
    delay(1+E);
    tone(Alarme,Eb4,Q);
    delay(1+Q);
    tone(Alarme,D4,E+S);
    delay(1+E+S);
    tone(Alarme,Db4,S);
    delay(1+S);

    tone(Alarme,C4,S);
    delay(1+S);
    tone(Alarme,B3,S);
    delay(1+S);
    tone(Alarme,C4,E);
    delay(1+E);
    delay(1+E);//PAUSE QUASI FINE RIGA
    tone(Alarme,F3,E);
    delay(1+E);
    tone(Alarme,Ab3,Q);
    delay(1+Q);
    tone(Alarme,F3,E+S);
    delay(1+E+S);
    tone(Alarme,LA3,S);
    delay(1+S);

    tone(Alarme,C4,Q);
    delay(1+Q);
    tone(Alarme,LA3,E+S);
    delay(1+E+S);
    tone(Alarme,C4,S);
    delay(1+S);
    tone(Alarme,E4,H);
    delay(1+H);

    tone(Alarme,LA4,Q);
    delay(1+Q);
    tone(Alarme,LA3,E+S);
    delay(1+E+S);
    tone(Alarme,LA3,S);
    delay(1+S);
    tone(Alarme,LA4,Q);
    delay(1+Q);
    tone(Alarme,Ab4,E+S);
    delay(1+E+S);
    tone(Alarme,G4,S);
    delay(1+S);

    tone(Alarme,Gb4,S);
    delay(1+S);
    tone(Alarme,E4,S);
    delay(1+S);
    tone(Alarme,F4,E);
    delay(1+E);
    delay(1+E);//PAUSE
    tone(Alarme,Bb3,E);
    delay(1+E);
    tone(Alarme,Eb4,Q);
    delay(1+Q);
    tone(Alarme,D4,E+S);
    delay(1+E+S);
    tone(Alarme,Db4,S);
    delay(1+S);

    tone(Alarme,C4,S);
    delay(1+S);
    tone(Alarme,B3,S);
    delay(1+S);
    tone(Alarme,C4,E);
    delay(1+E);
    delay(1+E);//PAUSE QUASI FINE RIGA
    tone(Alarme,F3,E);
    delay(1+E);
    tone(Alarme,Ab3,Q);
    delay(1+Q);
    tone(Alarme,F3,E+S);
    delay(1+E+S);
    tone(Alarme,C4,S);
    delay(1+S);

    tone(Alarme,LA3,Q);
    delay(1+Q);
    tone(Alarme,F3,E+S);
    delay(1+E+S);
    tone(Alarme,C4,S);
    delay(1+S);
    tone(Alarme,LA3,H);
    delay(1+H);

    delay(2*H);

    delay(t);
    digitalWrite(LedAlarme, LOW);
    noTone(Alarme);
  }
  else
  {
    Serial.println("LOW");
    digitalWrite(LedAlarme, LOW);
  }
}













