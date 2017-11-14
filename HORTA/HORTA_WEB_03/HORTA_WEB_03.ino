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

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(192, 168, 0, 111);


String readString;

// Initialize the Ethernet server library
// with the IP address and port you want to use
// (port 80 is default for HTTP):
EthernetServer server(80);

int entrada = 2;
int lulz = A0;
int LED = 6;

const int t = 100;

int BETA =  5000; //Calibrar este valor utilizando um termometro externo como comparacao
float Ro = 100000; //Resistencia tpica de um termistor de 100k
float To = 25 + 273; //Transforma temperatura de referencia do Termistor de Celsius para Kelvin

float pico; //Tempo
float picoanterior;
float vale;
float valeanterior;
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
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
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
    if ((R >= 0) && (vale > 0.9 * valeanterior) && (vale < 1.1 * valeanterior) && (pico > 0.9 * picoanterior) && (pico < 1.1 * picoanterior))
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
        if ((client) && (client.connected()) && (client.available()))
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
                client.println("h4 {font-size: 18px; font-family: verdana; color: white}");
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
                client.print(" &#176;C");
                client.print("</td>");

                client.print("<td >");
                client.print(LUZ);
                client.print(" &#37;");
                client.print("</td>");

                client.print("<td>");
                client.print(Celsius);
                client.print(" &#176;C");
                client.print("</td>");

                client.print("<td>");
                client.print(Celsius);
                client.print(" &#176; C");
                client.print("</td>");

                client.print(" </tr>");

                char c = client.read();

                if (readString.length() < 100) {
                  readString += c;
                }

                if (c == '\n') {

                  client.print("<tr>");

                  client.print("<td>");

                  client.println("<a href=\"/?ledon\"\">Ligar</a>");
                  client.print("</td>");

                  client.print("<td >");

                  client.println("<a href=\"/?ledon\"\">Ligar</a>");
                  client.print("</td>");

                  client.print("<td>");
                  client.println("<a href=\"/?ledoff\"\">Desligar</a>");
                  client.print("</td>");

                  client.print("<td>");
                  client.println("<a href=\"/?ledoff\"\">Desligar</a>");
                  client.print("</td>");

                  client.print(" </tr>");


                  if (readString.indexOf("?ledon") < 0)
                  {
                    digitalWrite(LED, LOW);
                  }
                  else {
                    if (readString.indexOf("?ledoff") < 0)
                    {
                      digitalWrite(LED, HIGH);
                    }
                    Serial.print(readString.indexOf("?ledon"));
                    Serial.print("  ");
                    Serial.println(readString.indexOf("?ledoff"));
                  }
                  readString = "";
                }
              }
            }
          }
          client.print("</table>");

          client.println(" </h1> ");
          client.println(" </html> ");
        }
      }
    }
    // give the web browser time to receive the data
    delay(10);
    client.stop();
    // close the connection:
    Serial.println("client disconnected");
    Ethernet.maintain();
  }
  picoanterior = pico;
  valeanterior = vale;
  delay(t);
}

