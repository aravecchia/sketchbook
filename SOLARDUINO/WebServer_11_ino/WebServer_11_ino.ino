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
     aravecchia <arroba> gmail <ponto> com
     http://aravecchia.weebly.com
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
    int t=10;
    
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
      Serial.print("Servidor conectado no IP: ");
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
    
              client.println("Content-Type: text/html");
              client.println("Connection: close");  // the connection will be closed after completion of the response
              client.println("Refresh: 1");  // refresh the page automatically every 5 sec
              client.println();
              client.println("<!DOCTYPE html PUBLIC - //W3C//DTD XHTML 1.0 Strict//EN>");
              client.println("<http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd>");
              client.println("<html xmlns=http://www.w3.org/1999/xhtml lang=pt-br>");
    
              //_________________________________________________HTML_________________________________________________
              client.println("<html>");
    
              //_________________________________________________HEAD_________________________________________________
              client.println("<head>");
              client.println("<title> CyberOhm.com</title>");
              client.println("<! autor: tiodocomputador-arroba-gmail-com>");
              client.println("<! última atualização: 30/07/2015>");
              client.println("<meta charset=utf-8>");
    
              //_________________________________________________CSS STYLE_________________________________________________
              client.println("<style type=text/css>");
              client.println("h1 {font-size: 24px; font-family: arial; color: red}");
              client.println("h2 {font-size: 18px; font-family: arial; color: red}");
              client.println("h3 {font-size: 16px; font-family: arial; color: red}");
              client.println("h4 {font-size: 14px; font-family: verdana; color: red}");
              client.println("h5 {font-size: 12px; font-family: verdana; color: red}");
              client.println("h6 {font-size: 10px; font-family: courier; color: red}");
              client.println("</style>");
    
              client.println(" </head>");
    
              //_________________________________________________BODY_________________________________________________
              client.println("<body>");
              client.println("<body bgcolor=#151515");
              client.println("<body TEXT=#ff0000");
              client.println("<LINK=#70db93");
              client.println("<VLINK=#ff0000");
              client.println("<ALINK=#00ff00>");
    
              client.print("<h6>");
    
              client.println("<svg width=1000 height=650>"); 
              //define o tamanho do grafico escalar vetorial
    
              int x0=2; //metade largura da linha para centralizar os eixos das linhas
              int altura=100; //altura do grafico
              int largura=964; //largura do grafico
              int linha=4; //largura da linha
    
              //_____________________________________ FUNDOS DOS GRAFICOS _________________________________
    
              client.print("<rect x=");
              client.print(x0);
              client.print(" y=20 width=");
              client.print(largura);
              client.print(" height=");
              client.print(altura);
              client.print(" stroke= #4F4F4F stroke-width= ");
              client.print(linha);
              client.print(" fill= #000000 />");    
    
              client.print("<rect x=");
              client.print(x0);
              client.print(" y=200 width=");
              client.print(largura);
              client.print(" height=");
              client.print(altura);
              client.print(" stroke= #4F4F4F stroke-width= ");
              client.print(linha);
              client.print(" fill= #000000 />");
    
              client.print("<rect x=");
              client.print(x0);
              client.print(" y=380 width=");
              client.print(largura);
              client.print(" height=");
              client.print(altura);
              client.print(" stroke= #4F4F4F stroke-width= ");
              client.print(linha);
              client.print(" fill= #000000 />");
    
              //_____________________________________ TITULOS DOS GRAFICOS _____________________________________
    
    
              client.print("<text x= 10 y= 10 font-size=12pt style=fill:white;stroke:none> Sensor móvel.</text>");
              client.print("<text x= 10 y= 190 font-size=12pt style=fill:white;stroke:none> Sensor fixo: meio-dia do azimute X&#176; (Vitoria - ES).</text>");
              client.print("<text x= 10 y= 370 font-size=12pt style=fill:white;stroke:none> Percentual de ganho = (100*(movel/fixo))-100</text>");
    
              //_____________________________________ LINHAS VERTICAIS DOS GRAFICOS - MARCACAO DA HORA
              for (int dt=1; dt<12; dt++)
              {
                client.print("<line x1=");
                client.print(4+(80*dt));
                client.print(" y1=20 x2=");
                client.print(4+(80*dt));
                client.print(" y2=");
                client.print(20+altura);
                client.print(" style=stroke:#4f4f4f; stroke-width:1/>");
    
                client.print("<line x1=");
                client.print(4+(80*dt));
                client.print(" y1=200 x2=");
                client.print(4+(80*dt));
                client.print(" y2=");
                client.print(200+altura);
                client.print(" style=stroke:#4f4f4f; stroke-width:1/>");
    
                client.print("<line x1=");
                client.print(4+(80*dt));
                client.print(" y1=380 x2=");
                client.print(4+(80*dt));
                client.print(" y2=");
                client.print(380+altura);
                client.print(" style=stroke:#4f4f4f; stroke-width:1/>");
    
                //_____________________________________ LINHAS HORIZONTAIS SOB OS VALORES DE LEITURA _________________________________
    
                client.print("<line x1=2 y1="); //barra sob a leitura
                client.print(altura+40); //barra sob a leitura
                client.print(" x2="); //barra sob a leitura
                client.print(largura); //barra sob a leitura
                client.print(" y2="); //barra sob a leitura
                client.print(altura+40); //barra sob a leitura
                client.print(" style=stroke:#4f4f4f; stroke-width:1/>"); //barra sob a leitura
    
                client.print("<line x1=2 y1="); //barra sob a leitura
                client.print((2*(altura+40))+40); //barra sob a leitura
                client.print(" x2="); //barra sob a leitura
                client.print(largura); //barra sob a leitura
                client.print(" y2="); //barra sob a leitura
                client.print((2*(altura+40))+40); //barra sob a leitura
                client.print(" style=stroke:#4f4f4f; stroke-width:1/>"); //barra sob a leitura
    
                client.print("<line x1=2 y1="); //barra sob a leitura
                client.print((3*(altura+40))+80); //barra sob a leitura
                client.print(" x2="); //barra sob a leitura
                client.print(largura); //barra sob a leitura
                client.print(" y2="); //barra sob a leitura
                client.print((3*(altura+40))+80); //barra sob a leitura
                client.print(" style=stroke:#4f4f4f; stroke-width:1/>"); //barra sob a leitura
    
              }
    
              float fixo;
              float movel;
              float somaA=0;
              float somaB=0;
    
    
              for (int x=0; x<48; x++) //para cada 48 passos do motor
              {
                for (int sensor=1; sensor<3; sensor++) //para cada sensores
                {
                  int sensorReading = map(analogRead(sensor), 0, 1023, altura-4, 0); 
                  // mapeia a variavel de leitura do sensor entre 0 e 100, 
                  //para facilitar a leitura na tela
                  // int horizontal= map(analogRead(sensor), 0, 1023, 964, 0);
                  int valor = map(analogRead(sensor), 0, 1023, 100, 0); 
                  //para manipular o valor da barra horizontal, 
                  //esta deve atualizar a cada leitura do sensor
    
                  // _________________________________ BARRA VERTICAL - LEITURA _________________________________
                  client.print("<rect x=");
                  client.print(4+(20*x));
                  client.print(" y=");
                  client.print(((altura+20)*sensor)+(60*(sensor-1))-sensorReading-2); //ninja! \o/
                  client.print(" width=20 height=");
                  client.print(sensorReading);
                  client.print(" stroke=#000000 stroke-width= 1");
    
                  if (valor>50)
                  {
                    client.print(" fill=#00ff00 />");
                    digitalWrite((led+sensor), LOW);
                  }
                  else
                  {
                    client.print(" fill=#ff0000 />");
                    digitalWrite((led+sensor), HIGH);
                  }
    
                  client.print("<text x=");
                  client.print(6+(20*x));
                  client.print(" y= ");
                  client.print(((altura+35)*sensor)+(45*(sensor-1)));
                  client.print(" font-size=8pt style=fill:white;stroke:none>");
                  client.print(int(valor));
                  client.print("</text>");
    
    
                  if (sensor==1)
                  {
                    somaA=somaA+valor;
                    movel=sensorReading;
                  }
                  else if(sensor==2)
                  {
                    somaB=somaB+valor;
                    fixo=sensorReading;
                    if (fixo==0)
                    {
                      fixo=1;
                    }
                  }
                }
    
                float ganho=(100*(movel/fixo))-100;     
                int ganhografico=map(ganho, 0, 100, 0, altura-x0);
    
                // BARRA VERTICAL - GANHO ENTRE OS SENSORES          
                client.print("<text x=");
                client.print(6+(20*x));
                client.print(" y= ");
                client.print(495);
                client.print(" font-size=6pt style=fill:white;stroke:none>");
                client.print(int(ganho));
                client.print("</text>");
    
                if(ganhografico>altura-x0)
                {
                  ganhografico=altura-x0;
                }
                client.print("<rect x=");
                client.print(4+(20*x));
                client.print(" y=");
                client.print(380+altura-ganhografico-x0); //ninja! \o/
                client.print(" width=20 height=");
                client.print(ganhografico);
                client.print(" stroke=#000000 stroke-width= 1");
                if (ganho<50)
                {
                  client.print(" fill=#ff0000 />");
                }
                else if ((ganho>50)&&(ganho<100))
                {
                  client.print(" fill=#00ff00 />");
                }
                else
                {
                  client.print(" fill=#0000ff />");
                }
    
                // SAIDA DE DEPUTACAO NA SERIAL 
                Serial.print("Sensor ");
                Serial.print(x);
                Serial.print(" -> ");
                Serial.print(" Fixo = ");
                Serial.print(fixo);
    
                Serial.print(" - Movel ");
                Serial.print(x);
                Serial.print(" = ");
                Serial.print(movel);
    
                Serial.print(" - Ganho ");
                Serial.print(x);
                Serial.print(" = ");
                Serial.println(ganho);
    
                delay(10*t);
    
              }
              //_________________________________ MEDIDAS _________________________________
              client.print("<text x= 800");
              client.print(" y=");
              client.print(10);
              client.print(" font-size=12pt style=fill:white;stroke:none> Média: ");
              client.print(somaA/48);
              client.print(" %</text>");
    
              client.print("<text x= 800");
              client.print(" y=");
              client.print(2*altura-10);
              client.print(" font-size=12pt style=fill:white;stroke:none> Média: ");
              client.print(somaB/48);
              client.print(" %</text>");
    
              client.print("<text x= 720");
              client.print(" y=");
              client.print(4*altura-30);
              client.print(" font-size=14pt style=fill:yellow;stroke:none> Ganho médio = ");
              client.print((100*somaA/somaB)-100);
              client.print(" %</text>");
    
              client.print("<text x= 590");
              client.print(" y=");
              client.print(6*altura-50);
              client.print(" font-size=16pt style=fill:yellow;stroke:none> Ganho total de energia: ");
              client.print(int(somaA - somaB));
              client.print(" %</text>");
    
              client.println("<svg/>");
              client.print("</h6>");
    
              client.println("</body>");
              client.println("</html>");
    
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
        Serial.println("Cliente desconectado!!!");
      }
    }
