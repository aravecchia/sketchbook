#include <Arduino.h>

/*  Sergio & Adriano Prenleloup
Verificar o valor de R no circuito e no codigo,
para obter uma leitura precisa.

http://avventurarduino.blogspot.com.br/2013/05/arduino-partiamo-da-zero-n7-post.html
        12 / 05 / 2013
     Tempo di carica e scarica condensatore  v. 2.02
     Misurazione della capacità
     Misurazione della resistenza
      
 Un ringraziamento a Nicola Amatucci sul suo blog l'idea base ed in nucleo
 dello sketch.
  
   Con questo sketch s'imposta il tempo di carica nella
   variabilie tc e si rileva il tempo di scarica.
   Si leggono i tempi su monitor seriale.
    
 */
 
// pin digitali in uso carica e scarica condensatore
int Carica  = 12;
int Scarica = 11;
 
// pin analogico di controllo per verificare il raggiungimento del 
// livello di scarica impostato di C1 (Vedi Vf)
int Control = 0; // pin analo A0
 
//variabili in uso
unsigned long Carica_t0 = 0; //registra t0 inizio carica
int Carica_t1 = 0;  // progressione del tempo di carica
 
int tc = 1000;   // costante di tempo carica a cui arrivare
                // si sceglierà in relazione alla capacità di C1
                // ed al valore della resistenza di R1 in modo di avere            
                //   la certezza di raggiungere la carica completa.
                 
unsigned long Scarica_t0 = 0; // registra il t0 inizio scarica condensatore
unsigned long Scarica_t1 = 0; // contiene il tempo di scarica a partire da t0
                              // fino al raggiungimento della scarica completa
                              // che viene verificata dal pin analogico A0
 
/* Questi valori si sono utilizzati per testare i risultati teorici
confrontandoli con i risultati misurati.
    Se si cambiano i componenti dovranno essere aggiornati
    altrimenti i valori calcolati non risultano giusti.
*/
 
//parametri circuito
double prec = 1E3;   // costante milli
double R = 576.0;   //Resistenza di scarica in omm (valore misurato)
double C = 110E-6;  //Condensatore in Farad (100 micro-F)
double Vi = 4.78;   //Vo = tensione iniziale (condensatore carico) 5 volt
double Vf = 0.025 ; //Vs = tensione finale (condensatore scarico) 25 millivolt
                    // non porre a 0 questo valore altrimenti avremo errore 
                    // divisione per "0"
                      
int sogliaADC = floor(Vf * 1024 / Vi); // contiene il valore numerico 
                                  // attribuito dal dac di arduino  ai 25 mV.
// ***********************************************************************                                  
 
/* formula e formule inverse qui sotto ho inserito queste formule per 
controlli in fase di prove di funzionamento queste funzionano solo se 
nelle variabili sopra indicate sono stati inseriti i valori presenti nel 
circuito.
calolaC funziona se è fissata la R ( logicamente anche Vi e Vf )
calcolaR funziona se è fissato C (logicamente anche Vi e Vf )
*Con le opportune modifiche è possibile eliminare quelle che non interessano *
*/
 
double tempoScaricaTeorico = (R*C*log(Vi/Vf)); 
/* formula per stabilire il tempo di scarica teorico che confronteremo
con il tempo misurato, si devono impostare R e C con valore noto. 
*/
double calcolaC(unsigned long tf) // qui si calcola il valore del condensatore
{                                 // se C è incognito dovremo fissare R
  double t = tf;
  return (t/prec) / (R * log(Vi/Vf));    
}
 
double calcolaR(unsigned long tf)  // qui si calcola il valore della resistenza
                                   // di scarica.
{                                  //  se R è incognito dovremo fissare C
  double t = tf;
  return (t/prec) / (C * log(Vi/Vf));
}
 
double calcolaV(unsigned long tf) // qui si valcola la Vf 
                                  //(controllo teorico con R e C conosciuti
{                                 
  double t = tf;
  return Vi * exp(-(t/prec)/(R*C));
}
 
void setup()
{
   
  Serial.begin(9600);
  pinMode (Control, INPUT); 
  pinMode (Carica, OUTPUT); //pronto per la carica
  pinMode (Scarica, INPUT); // (INPUT) blocca la scarica
 
  Serial.print("Soglia ADC: "); // valore scelto vicino allo zero.
  Serial.println( sogliaADC);
  Serial.print("Tempo di scarica teorico: ");
  Serial.println( tempoScaricaTeorico, 3);
}
   
double Rcalc = 0.0;
double Ccalc = 0.0;
double Vcalc = 0.0;
double Tcalc = 0.0;
  void loop()
  {
        //inizio carica
        pinMode (Carica, OUTPUT);  //abilita il pin alla carica
        Carica_t0 = millis();     // si registra il tempo di partenza
        digitalWrite (Carica, HIGH);  // si avvia la carica
        delay (tc);                  // tempo di carica (tc)
         
        Carica_t1 = ( millis()- Carica_t0 ); //si conteggia il tempo di
                                             // carica 
        digitalWrite (Carica, LOW);
        pinMode (Carica, INPUT);  // con questa si blocca l'eventuale scarica
                                  // anche da questo pin. 
        //fine carica ********************************************
            
       // inizio scarica 
        pinMode (Scarica, OUTPUT); // si abilita alla scarica
        Scarica_t0 = millis();   // si registra il tempo  inizio scarica
        digitalWrite( Scarica, LOW);  // inizia la scarica
         
        while ( analogRead (Control) > sogliaADC){} 
        /*  attende fino a quando il pin A0 non raggiuge
               il valore scelto di scarica ( Vf)*/
                                                     
        Scarica_t1 = ( millis () - Scarica_t0); 
        // conteggia il tempo di scarica
         
        pinMode (Scarica, INPUT);  //blocca la scarica   
        // fine scarica *******************************************
        
        Rcalc = calcolaR(Scarica_t1);  // si fanno i calcoli
        Ccalc = calcolaC(Scarica_t1);
        Vcalc = calcolaV(Scarica_t1);
         
         // stampa i dati   lettura sul monitor
         Serial.println(" ");                
         Serial.print("Tempo Carica secondi: ");
         Serial.println( (Carica_t1/prec), 3);
         Serial.println(" ");                
         Serial.print("Tempo Scarica secondi: ");
         Serial.println(( Scarica_t1/prec), 3);
         Serial.print("Resistenza calcolata omm : ");
         Serial.println( Rcalc, 1);
         Serial.print("Capacita' calcolata F : ");
         Serial.println( Ccalc, 6);
         Serial.print("Tensione (finale) calcolata Volt : ");
         Serial.println( Vcalc, 3);
 
          delay (2000);  //attesa
           
          //ripristino le variabili
          Carica_t0 = 0;
          Carica_t1 = 0; 
          Scarica_t0 = 0;
          Scarica_t1 = 0;      
  }
  //end
