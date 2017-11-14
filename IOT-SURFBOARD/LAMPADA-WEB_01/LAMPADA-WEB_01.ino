#include <Arduino.h>

#include <SPI.h>
#include <Ethernet.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte ip[] = { 192, 168, 0, 111 };

EthernetServer server(80);

String readString;
int Pin = 13;
boolean State = 0;

void setup() {

  pinMode(Pin, OUTPUT);
  Ethernet.begin(mac, ip);

  Serial.begin(9600);
}

void loop()
{
  EthernetClient client = server.available();
  if (client)
  {
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();

        if (readString.length() < 100) {
          readString += c;
        }

        if (c == '\n') {
          client.println("HTTP/1.1 200 OK");
          client.println("Content­Type: text/html");
          client.println();

          client.println("<HTML>");
          client.println("<BODY>");
          client.println("<H1>Acende LED</H1>");
          client.println("<hr />");
          client.println("<br />");

          client.println("<a href=\"/?ledon\"\">LED</a>");
          // client.println("<a href=\"/?ledoff\"\">Desligar o led</a>");
          client.println(" </BODY> ");
          client.println(" </HTML>a ");
          delay(10);
          client.stop();

          if (readString.indexOf("?ledon") > 0)
          {
            digitalWrite(Pin, HIGH);
          }
          else
          {
            digitalWrite(Pin, LOW);
          }
          Serial.print(readString);
          readString = "";
        }
      }
    }
  }
  delay(10);
}

