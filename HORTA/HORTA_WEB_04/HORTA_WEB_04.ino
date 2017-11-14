/*
  PROTOCOLO NE-555
  Leitura de sensores a distancia do Arduino
  com ligacao por meio de fios
  _____________________________
  Desenvolvido por Alexandre Aravecchia
  aravecchia@gmail.com
  Projetista, desenvolvedor, programador
  www.aravecchia.weebly.com/
  Com o apoio de http://labdegaragem.com.br/
  Com o apoio de http://labdegaragem.com.br/
  Publicado no Labdegaragem em 10/outubro/2016.
*/

#include <math.h>
#include <Arduino.h>
#include <SPI.h>
#include <Ethernet.h>

const int t = 10;

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
int L1 = 4; //lampada 1
int L2 = 5; //lampada 2
int L3 = 6; //lampada 3
int AGUA = 7;

int LED = 13;

int BETA =  3870; //Calibrar este valor utilizando um termometro de precisao externo como comparacao
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
float C1 = 0.92; // Capacitor principal em MICROFARADAY;

float LUZ;


void setup()
{
  pinMode(entrada, INPUT_PULLUP);
  pinMode(lulz, INPUT);
  pinMode(LED, OUTPUT);
  pinMode(AGUA, OUTPUT);
  pinMode(L1, OUTPUT);
  pinMode(L2, OUTPUT);
  pinMode(L3, OUTPUT);


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
}

void loop()
{
  digitalWrite(LED, LOW);

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

  //Irrigar ou nao irrigar:
  if ((Celsius > 30) && (LUZ < 50))
  {
    digitalWrite(AGUA, HIGH);
  }
  else
  {
    digitalWrite(AGUA, LOW);
  }
  if (LUZ < 60)
  {
    if ((Celsius > 0) && (Celsius <= 20))
    {
      digitalWrite(L1, HIGH);
      digitalWrite(L2, LOW);
      digitalWrite(L3, LOW);
      digitalWrite(AGUA, LOW);
    }
    else if ((Celsius > 20) && (Celsius <= 25))
    {
      digitalWrite(L1, HIGH);
      digitalWrite(L2, HIGH);
      digitalWrite(L3, LOW);
      digitalWrite(AGUA, LOW);
    }
    else if ((Celsius > 25) && (Celsius <= 30))
    {
      digitalWrite(L1, HIGH);
      digitalWrite(L2, HIGH);
      digitalWrite(L3, HIGH);
      digitalWrite(AGUA, LOW);
    }
    else if ((Celsius > 30))
    {
      digitalWrite(L1, HIGH);
      digitalWrite(L2, HIGH);
      digitalWrite(L3, HIGH);
      digitalWrite(AGUA, HIGH);
    }
  }


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
          client.println("Refresh: 30");  // refresh the page automatically every 5 sec (default)
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          //_________________________________________________HEAD_________________________________________________
          client.println("<head>");
          client.println("<title> Arduino </title>");
          //_____________________________________________CSS STYLE_________________________________________________

          client.println("<style type=text/css>");

          client.println("h1 {font-size: 42px; font-family: arial; color: white; align: center}");
          client.println("h2 {font-size: 28px; font-family: arial; color: white; align: center}");
          // client.println("h3 {font-size: 18px; font-family: arial; color: green}");
          //client.println("h4 {font-size: 18px; font-family: verdana; color: white}");
          //client.println("h5 {font-size: 10px; font-family: verdana; color: red}");
          //client.println("h6 {font-size: 8px; font-family: courier; color: red}");

          client.println("</style>");
          client.println("</head>");
          //_________________________________________________BODY_________________________________________________
          client.println("<body bgcolor=black>");
          client.println("<h2 align=center>");
          client.print("<table width=700 align=center>");
          //<table cellpadding="0" cellspacing="2" border="0" align="center" width="1000" style="border-color: black; font-family: monospace; color:#FFFFFF">

          client.print("<tr align=center border-color=white>");


          client.print("<td>");
          client.print(Celsius);
          client.print(" &#176;C");
          client.print("</td>");

          client.print("<td>");
          client.print(LUZ);
          client.print(" &#37;");
          client.print("</td>");

          client.print("<td>");
          client.print(R / 1000);
          client.print(" k&#937;");
          client.print("</td>");

          client.print("<td>");
          /*
            if (distancia < 10)
            {
            client.print("garagem");
            }
            else
            {
            client.print("estrada");
            }
          */
          client.print("Carro");
          client.print("</td>");
          client.print(" </tr>");
          client.print("</table>");
          client.println(" </h2> ");
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
    // Ethernet.maintain();
  }
}

