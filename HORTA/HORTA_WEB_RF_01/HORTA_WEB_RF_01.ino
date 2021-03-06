/*
  PROTOCOLO NE-555
  Leitura de sensores a distancia do Arduino
  com ligacao por meio de fios
  _____________________________
  Desenvolvido por Alexandre Aravecchia
  aravecchia@gmail.com
  Projetista, desenvolvedor, programador
  www.aravecchia.weebly.com
  Com o apoio de http://labdegaragem.com.br/, Rui Viana, Almir Bispo Filho
  E a santa paciência da minha esposa.
  Publicado no Labdegaragem em 10/outubro/2016.


  CODIGO FAIL!!!!!

  ETHERNET SHIELD E RF COMPARTILHAM O MESMO PROTOCOLO RX-TX
  NOS PINOS 0, 1, 11 E 12

  HACKEAVEL????
*/

#include <math.h>
#include <Arduino.h>

#include <SPI.h>
#include <Ethernet.h>
#include <VirtualWire.h>

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(192, 168, 0, 111);

// Initialize the Ethernet server library
// with the IP address and port you want to use
// (port 80 is default for HTTP):
EthernetServer server(80);

int entrada = 2;
int lulz = A0;
int LED = 13;
int RF_pin = 12;
int transmit_en_pin = 3;


const int t = 10;

int BETA =  4000; //Calibrar este valor utilizando um termometro externo como comparacao
float Ro = 100000; //Resistencia tpica de um termistor de 100k
float To = 25 + 273; //Transforma temperatura de referencia do Termistor de Celsius para Kelvin

float pico; //Tempo
float vale;
float Periodo;
float Frequencia;

float Kelvin;
float Celsius = Kelvin - 273;
float media;

float R; // Resistencia do Termistor
float R2 = 10000; //Segundo resistor do NE-222
int C1 = 1; // Capacitor principal em MICROFARADAY;

float LUZ;


void setup()
{
  pinMode(entrada, INPUT_PULLUP);
  pinMode(lulz, INPUT);
  pinMode(LED, OUTPUT);

  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial)
  {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);
  server.begin();
  // Serial.print("server is at ");
  // Serial.println(Ethernet.localIP());

  //Inicializa a transmissao RF
  // Initialise the IO and ISR
  vw_set_tx_pin(RF_pin);
  //    vw_set_rx_pin(receive_pin);
  vw_set_ptt_pin(transmit_en_pin);
  vw_set_ptt_inverted(true); // Required for DR3100
  vw_setup(2000);       // Bits per sec
  pinMode(RF_pin, OUTPUT);
}

void loop()
{
  digitalWrite(LED, LOW);
  {
    LUZ = map(analogRead(lulz), 0, 1023, 0, 100);
    pico = pulseIn(entrada, HIGH);
    vale = pulseIn(entrada, LOW);
    Periodo = (pico + vale);
    Frequencia = 1000000 / Periodo;

    R = ((1.44 * Periodo) / C1) - (2 * R2);

    // Kelvin =  1 / ( (1/To) + ((log(R/Ro)/ BETA)) ); // Calcula a temperatura por Steinhart-Hart
    Kelvin = 1 / ( (1 / To) + ((log(R / Ro) / BETA))); // Sensor NTC
    //Kelvin = 1/To;

    Celsius = Kelvin - 273; // Convert Kelvin to Celsius
//    if ((R >= 0) && (vale > 0.9 * valeanterior) && (vale < 1.1 * valeanterior) && (pico > 0.9 * picoanterior) && (pico < 1.1 * picoanterior))
    {
      {
        /*
          Serial.print(vale / 1000, 3);
          Serial.print(" ms - ");
          Serial.print(pico / 1000, 3);
          Serial.print(" ms - Periodo = ");
          Serial.print(Periodo / 1000, 3);
          Serial.print(" ms - ");

          Serial.print(" Freq = ");
          Serial.print(Frequencia, 3);
          Serial.print(" Hz - ");

          Serial.print("R = ");
          Serial.print(R / 1000);
          Serial.print(" K Ohm - ");

          Serial.print("Temp = ");
          Serial.print(Celsius, 2);
          Serial.println(" *C.");
        */
        // listen for incoming clients
        EthernetClient client = server.available();
        if (client)
        {
          Serial.println("new client");
          // an http request ends with a blank line
          boolean currentLineIsBlank = true;
          while (client.connected())
          {
            if (client.available())
            {
              digitalWrite(LED, HIGH);
              char c = client.read();
              Serial.write(c);
              // if you've gotten to the end of the line (received a newline
              // character) and the line is blank, the http request has ended,
              // so you can send a reply
              if (c == '\n' && currentLineIsBlank)
              {
                // send a standard http response header
                client.println("HTTP/1.1 200 OK");
                client.println("Content-Type: text/html");
                client.println("Connection: close");  // the connection will be closed after completion of the response
                client.println("Refresh: 5");  // refresh the page automatically every 5 sec (default)
                client.println();
                client.println("<!DOCTYPE HTML>");
                client.println("<html>");
                //_________________________________________________HEAD_________________________________________________
                client.println("<head>");
                client.println("<title> Temperatura </title>");
                //_____________________________________________CSS STYLE_________________________________________________
                client.println("<style type=text/css>");

                client.println("h1 {font-size: 32px; font-family: arial; color: white}");
                //client.println("h2 {font-size: 24px; font-family: arial; color: white}");
                // client.println("h3 {font-size: 18px; font-family: arial; color: green}");
                //client.println("h4 {font-size: 18px; font-family: verdana; color: white}");
                //client.println("h5 {font-size: 10px; font-family: verdana; color: red}");
                //client.println("h6 {font-size: 8px; font-family: courier; color: red}");

                client.println("</style>");
                client.println("</head>");
                //_________________________________________________BODY_________________________________________________
                client.println("<body bgcolor=black>");
                client.println("<h1 align=center>");
                client.print("<table cellpadding=0 cellspacing=0 border=0 align=center width=800>");
                //<table cellpadding="0" cellspacing="2" border="0" align="center" width="1000" style="border-color: black; font-family: monospace; color:#FFFFFF">

                client.print("<tr>");

                client.print("<td>");
                client.print(Celsius);
                client.print("</td>");

                client.print("<td >");
                client.print(LUZ);
                client.print("</td>");

                client.print(" </tr>");
                client.print("</table>");

                client.println(" </h1> ");
                client.println(" </html> ");
                break;
              }
              if (c == '\n')
              {
                // you're starting a new line
                currentLineIsBlank = true;
              }
              else if (c != '\r')
              {
                // you've gotten a character on the current line
                currentLineIsBlank = false;
              }
            }
          }
          // give the web browser time to receive the data
          delay(t);
          // close the connection:
          client.stop();
          //Serial.println("client disconnected");
          Ethernet.maintain();
        }
      }
    }
    char CELSIUS = char(Celsius);
    char LULZ = char(LUZ);
    char msg[3] = {'C', '-', 'L'};
    msg[0] = CELSIUS;
    msg[2] = LULZ;
    vw_send((uint8_t *)msg, 3);
    vw_wait_tx(); // Wait until the whole message is gone
  }
}

