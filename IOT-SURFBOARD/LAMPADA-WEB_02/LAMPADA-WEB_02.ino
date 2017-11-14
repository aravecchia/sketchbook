#include <Arduino.h>

#include <SPI.h>
#include <Ethernet.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte ip[] = { 192, 168, 0, 111 };

EthernetServer server(80);

String readString;
int Pin = 13;
boolean State;

void setup() {
  pinMode(Pin, OUTPUT);
  Ethernet.begin(mac, ip);
  Serial.begin(9600);
}

void loop()
{
  digitalWrite(Pin, State);
  EthernetClient client = server.available();
  if (client)
  {
    while (client.connected())
    {
      if (client.available())
      {
        char c = client.read();

        if (readString.length() < 100)
        {
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

          client.println("<a href=\"/?ledon\"\">LED</a>");
          client.println(" </BODY> ");
          client.println(" </HTML> ");
          delay(10);
          client.stop();
        }
        if (readString)
        {
          State = ! State;
          digitalWrite(Pin, State);
        }
        delay(10);
        client.stop();
      }
    }
  }
}
