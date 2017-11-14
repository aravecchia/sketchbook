#include <Arduino.h>

    /*
     Louvado seja ROOT !
     Slackware é teu Linux, Bash é teu santuário e Volkerding é teu pastor!
     
     Um servidor web para Arduino Ethernet shield que lê os valores de 2 sensores analógicos,
     escreve os valores graficamente numa página web e, dependendo dos valores obtidos, acende ou apaga os Leds.
     
     created 18 Dec 2009
     by David A. Mellis
     modified 9 Apr 2012
     by Tom Igoe 
     
     Modificado, adaptado e melhorado soberbamente em Julho de 2015 por
     tiodocomputador <arroba> gmail <ponto> com
     http://cyberohm.com
     com o generoso apoio do Laboratorio de Garagem:
     http://www.labdegaragem.com
     a paciencia herculea de seus frequentadores,
     o apoio moral da minha esposa
     e o café da minha filha.
     
     Circuito:
     * Ethernet shield ligado aos pinos 10, 11, 12 e 13
     Futuramente utilizar LiquidCrystal lcd (pinos 8, 9, 4, 5, 6, 7),
     deixando livres os pinos: (2, 3, A0, A1, A2, A3, A4, A5)
     * Pinos analogicos ligados em A0 e A1.
     * LEDS nos pinos digitais 2 e 3.
     */
    
    #include <SPI.h>
    #include <Ethernet.h>
    
    // Enter a MAC address and IP address for your controller below.
    // The IP address will be dependent on your local network:
    byte mac[] = { 
      0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
    //    DE-AD-BE-EF-FE-ED
    IPAddress ip(192,168,1,100);
    
    // Initialize the Ethernet server library
    // with the IP address and port you want to use 
    // (port 80 is default for HTTP):
    EthernetServer server(80);
    int led=1;
    int t=1;
    
    //_________________________________________________SETUP_________________________________________________
    void setup() 
    {
      pinMode(led+1, OUTPUT); 
      pinMode(led+2, OUTPUT);
      //Por que nao colocar diretamente 2 ao inves de led+1? 
      //Porque eu preciso da variavel led, oras! Assim evito escrever 2x o mesmo codigo e 
      //posso usar lacos.
    
      // Open serial communications and wait for port to open:
      Serial.begin(9600);
      //  while (!Serial) {
      //    ; // wait for serial port to connect. Needed for Leonardo only
      //  }
      // start the Ethernet connection and the server:
      Ethernet.begin(mac, ip);
      server.begin();
      Serial.print("Servidor no endereço: ");
      Serial.println(Ethernet.localIP());
    }
    
    //_________________________________________________LOOP_________________________________________________
    void loop() 
    {            
    
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
            char c = client.read();
            Serial.write(c);
            // if you've gotten to the end of the line (received a newline
            // character) and the line is blank, the http request has ended,
            // so you can send a reply
            if (c == '\n' && currentLineIsBlank) 
            {
              // send a standard http response header
              client.println("HTTP/1.1 200 OK");
              client.println("Content-Type: text"); // @CHANGED: JSON
              client.println("Connection: close");  // the connection will be closed after completion of the response
              client.println("Access-Control-Allow-Origin: *");
              client.println("Refresh: 1");  // refresh the page automatically every 5 sec
              //client.println();
              //client.println('autor": "tiodocomputador-arroba-gmail-com"');
              //client.println('atualizado": "30/07/2015"');
              client.println();
    
              float fixo;
              float movel;    
    
              for (int x=0; x<48; x++) //para cada 48 passos do motor
              {
                for (int sensor=1; sensor<3; sensor++) //para cada sensores
                {
                  int valordosensor = analogRead(sensor);
                  int valor = map(valordosensor, 0, 1023, 100, 0); 
                  //para manipular o valor da barra horizontal, 
                  //esta deve atualizar a cada leitura do sensor
    
                  // _________________________________ BARRA VERTICAL - LEITURA _________________________________
                  if (valor < 1000) { 
                    client.print(valor);
                    client.print(',');
                  }
    
                  if (valor>50)
                  {
                    digitalWrite((led+sensor), LOW);
                  }
                  else
                  {
                    digitalWrite((led+sensor), HIGH);
                  }
    
                }
                client.println();

                
                delay(100*t);
    
              }
    
              delay(5000*t);
              break;
            }
            if (c == '\n') 
            {
              // you're starting a new line
              currentLineIsBlank = true;
            } 
            else if (c != '\r') {
              // you've gotten a character on the current line
              currentLineIsBlank = false;
            }
          }
        }
        // give the web browser time to receive the data
         delay(1000*t);
        // close the connection:
        client.stop();
        Serial.println("client disonnected");
      }
    }
