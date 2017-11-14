/*
  PROTOCOLO NE-555
  v.2.0
  Leitura de sensores a distancia do Arduino
  com ligacao por meio de fios
  _____________________________
  Desenvolvido por Alexandre Aravecchia
  a.k.a. O Tio do Computador
    http://tiodocomputador.tumblr.com/

    Com a ajuda de:
  Rui Viana
  Almir Bispo Filho
  Celso Eiji Ito
  Daniel Oraculo X

  Com o apoio de
  {
  http://labdegaragem.com.br/
  http://www.labirito.com/
  http://www.blogdoembarcado.???
  GLOBALCODE
  }
  Publicado no Forum Goiano de Software Livre em 19/novembro/2016.
*/

#include <math.h>
#include <Arduino.h>
#include <SPI.h>
#include <Ethernet.h>
#include <VirtualWire.h>

const int t = 1000;

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
String readString;

int entrada = 2;
int lulz = A0;
int L1 = 4; //lampada 1
int L2 = 5; //lampada 2
int L3 = 6; //lampada 3
int AGUA = 7;
int TERRA = A1;

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


float R; // Resistencia do Termistor
float R2 = 10000; //Segundo resistor do NE-222
float C1 = 1; // Capacitor principal em MICROFARADAY;

int LUZ;
int UMIDADE;

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
  String readString;
  server.begin();
  // Serial.print("server is at ");
  // Serial.println(Ethernet.localIP());

}

void loop()
{
  digitalWrite(LED, HIGH);
  delay(t);
  LUZ = map(analogRead(lulz), 0, 1023, 0, 100);
  UMIDADE = map(analogRead(TERRA), 0, 1023, 100, 0);
  pico = pulseIn(entrada, HIGH);
  vale = pulseIn(entrada, LOW);
  Periodo = (pico + vale);
  Frequencia = 1000000 / Periodo;

  // Calcula a resistencia do termistor ligado ao NE-555
  R = ((1.44 * Periodo) / C1) - (2 * R2);

  // Calcula a temperatura pela equacao reduzida de Steinhart-Hart
  //para sensores NTC
  Kelvin = 1 / ( (1 / To) + ((log(R / Ro) / BETA)));

  // Convert Kelvin to Celsius
  Celsius = Kelvin - 273;

  //Irrigar ou nao irrigar:
  if (((LUZ < 30) && (UMIDADE < 50)) || (Celsius < 5))
  {
    digitalWrite(AGUA, HIGH);
  }
  else
  {
    digitalWrite(AGUA, LOW);
  }

  //Ligar ou nao ligar as lampadas
  if (LUZ < 30)
  {
    digitalWrite(L1, HIGH);
    digitalWrite(L2, HIGH);
    digitalWrite(L3, HIGH);
  }
  else
  {
    if ((Celsius > 0) && (Celsius <= 10))
    {
      digitalWrite(L1, LOW);
      digitalWrite(L2, LOW);
      digitalWrite(L3, LOW);
    }
    else if ((Celsius > 10) && (Celsius <= 20))
    {
      digitalWrite(L1, HIGH);
      digitalWrite(L2, LOW);
      digitalWrite(L3, LOW);
    }
    else if ((Celsius > 20) && (Celsius <= 30))
    {
      digitalWrite(L1, HIGH);
      digitalWrite(L2, HIGH);
      digitalWrite(L3, LOW);
    }
    else if ((Celsius > 30))
    {
      digitalWrite(L1, HIGH);
      digitalWrite(L2, HIGH);
      digitalWrite(L3, HIGH);
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
        if (readString.length() < 100) {
          readString += c;
        }
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
          client.println("h3 {font-size: 18px; font-family: arial; color: green}");
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

          client.print("<tr align=left border-color=white>");


          client.print("<td>");
          client.print(Celsius);
          client.print(" &#176;C");
          client.print("</td>");

          client.print("<td>");
          client.print(UMIDADE);
          client.print(" &#37;");
          client.print("</td>");

          client.print("<td>");
          client.println(LUZ);
          client.print(" &#37;");
          client.print(" </td> ");

          client.print("<td>");
          client.println("LED");
          client.print(" </td > ");
          client.print(" </tr > ");
          client.print(" </table > ");
          client.println(" </h2 > ");
          client.println(" </body > ");
          client.println(" </html > ");
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
    digitalWrite(LED, LOW);
    delay(t);
  }
}

