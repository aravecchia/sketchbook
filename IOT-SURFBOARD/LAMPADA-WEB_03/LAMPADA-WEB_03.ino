#include <Arduino.h>

#include <SPI.h>
#include <Ethernet.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte ip[] = { 192, 168, 0, 111 };

EthernetServer server(80);

String readString;
int Pin = 13;


void setup()
{

  pinMode(Pin, OUTPUT);
  Ethernet.begin(mac, ip);

  Serial.begin(9600);
}

void loop()
{
  digitalWrite(Pin, LOW);
  EthernetClient client = server.available();

  if (client)
  {
    static boolean State;
    while (client.connected())
    {
      if (client.available())
      {
        Serial.print(char(client.read()));
        char c = client.read();

        Serial.print(c);

        if (readString.length() != 0)
        {
          Serial.println(readString.length());
          readString += c;
        }
        if (c == '\n')
        {
          client.println("HTTP/1.1 200 OK");
          client.println("Content­Type: text/html");
          client.println();

          client.println("<HTML>");
          client.println("<BODY>");
          client.println("<H1>Acende LED</H1>");
          client.println("<hr />");
          client.println("<br />");

          client.println("<a href=\"/LED\n\">LED</a>");
          client.println(" </BODY> ");
          client.println(" </HTML>");
          Serial.println(State);
          State = !State;
          //Serial.println(State);
          if (State == 0)
          {
            digitalWrite(Pin, LOW);
          }
          else
          {
            digitalWrite(Pin, HIGH);
          }
          delay(10);
          client.stop();
          readString = "";
        }
      }
    }
  }
}

