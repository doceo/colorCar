
//script modificato a partire da un algoritmo pubblicato su https://www.lombardoandrea.com/l298n-motore-dc-arduino/



//definizione dei pin
static int In1 = A2; //pin digitale per determinare gli stati logici da inviare al modulo
static int In2 = A3; //pin digitale per determinare gli stati logici da inviare al modulo
static int ENA = A1; //pin digitale tramite il quale inviare un segnale di tipo PWM tramite la funzione analgWrite()

static int In3 = 10; //pin digitale per determinare gli stati logici da inviare al modulo
static int In4 = 9; //pin digitale per determinare gli stati logici da inviare al modulo
static int ENB = A0; //pin digitale tramite il quale inviare un segnale di tipo PWM tramite la funzione analgWrite()
 
//variabili usate per gestire e mostrare i valori di operaizone
int potenza;  //valore in uscita dal pin 11
 
void avviamotore() {
 
  //inizializzo variabili
  potenza = 0;
 
  //definisco tipologia pin
  pinMode(In1, OUTPUT); //output perche' definisce lo stato logico del pin IN1 del modulo L298N
  pinMode(In2, OUTPUT); //output perche' definisce lo stato logico del pin IN2 del modulo L298N
  pinMode(ENA, OUTPUT);  //output perche' definisce il valore PWM del pin EN1 del modulo L298N

  pinMode(In3, OUTPUT); //output perche' definisce lo stato logico del pin IN3 del modulo L298N
  pinMode(In4, OUTPUT); //output perche' definisce lo stato logico del pin IN4 del modulo L298N
  pinMode(ENB, OUTPUT);  //output perche' definisce il valore PWM del pin EN2 del modulo L298N

 
}
 
 
void avanti(int potenza) {

   //Definisco il senso di marcia del motore
  /*
    mA |   mB  | Evento
  -----|-------|----------------------
  LOW  | LOW   | fermo
  LOW  | HIGH  | Movimento in un senso
  HIGH | LOW   | Movimento senso opposto
  HIGH | HIGH  | Fermo
  */
  
  digitalWrite(In1, LOW);
  digitalWrite(In2, HIGH);
  digitalWrite(In3, LOW);
  digitalWrite(In4, HIGH);
  
  //invio costantemente il valore PWM della potenza in modo da far variare la velocita' del motore in base alla posizione del potenziometro
  analogWrite(ENA, potenza);
  analogWrite(ENB, potenza);
}


void indietro(int potenza) {

   //Definisco il senso di marcia del motore
  /*
    mA |   mB  | Evento
  -----|-------|----------------------
  LOW  | LOW   | fermo
  LOW  | HIGH  | Movimento in un senso
  HIGH | LOW   | Movimento senso opposto
  HIGH | HIGH  | Fermo
  */
  
  digitalWrite(In1, HIGH);
  digitalWrite(In2, LOW);
  digitalWrite(In3, HIGH);
  digitalWrite(In4, LOW);
  
  //invio costantemente il valore PWM della potenza in modo da far variare la velocita' del motore in base alla posizione del potenziometro
  analogWrite(ENA, potenza);
  analogWrite(ENB, potenza);
}


void fermo() {
 
  analogWrite(ENA, LOW);
  analogWrite(ENB, LOW);
}

void destra(int potenza) {

   //Definisco il senso di marcia del motore
  /*
    mA |   mB  | Evento
  -----|-------|----------------------
  LOW  | LOW   | fermo
  LOW  | HIGH  | Movimento in un senso
  HIGH | LOW   | Movimento senso opposto
  HIGH | HIGH  | Fermo
  */
  
  digitalWrite(In1, LOW);
  digitalWrite(In2, HIGH);
  digitalWrite(In3, LOW);
  digitalWrite(In4, HIGH);
  
  //invio costantemente il valore PWM della potenza in modo da far variare la velocita' del motore in base alla posizione del potenziometro
  analogWrite(ENA, potenza);
  analogWrite(ENB, LOW);
}

void sinistra(int potenza) {

   //Definisco il senso di marcia del motore
  /*
    mA |   mB  | Evento
  -----|-------|----------------------
  LOW  | LOW   | fermo
  LOW  | HIGH  | Movimento in un senso
  HIGH | LOW   | Movimento senso opposto
  HIGH | HIGH  | Fermo
  */
  
  digitalWrite(In1, LOW);
  digitalWrite(In2, HIGH);
  digitalWrite(In3, LOW);
  digitalWrite(In4, HIGH);
  
  //invio costantemente il valore PWM della potenza in modo da far variare la velocita' del motore in base alla posizione del potenziometro
  analogWrite(ENA, LOW);
  analogWrite(ENB, potenza);
}


void sterza(int Y, int vel, int X, int ster){

   //Definisco il senso di marcia del motore
  /*
    mA |   mB  | Evento
  -----|-------|----------------------
  LOW  | LOW   | fermo
  LOW  | HIGH  | Movimento in un senso
  HIGH | LOW   | Movimento senso opposto
  HIGH | HIGH  | Fermo
  */
  
        if(Y > 10) {
        
            digitalWrite(In1, LOW);
            digitalWrite(In2, HIGH);
            digitalWrite(In3, LOW);
            digitalWrite(In4, HIGH);

            if(X > 10) {
                analogWrite(ENA, vel);
                analogWrite(ENB, ster);
            
            }else{
                analogWrite(ENA, ster);
                analogWrite(ENB, vel);
            
             }
        
        }else{

            digitalWrite(In1, LOW);
            digitalWrite(In2, HIGH);
            digitalWrite(In3, LOW);
            digitalWrite(In4, HIGH);


                if(X > 10) {
                    analogWrite(ENA, vel);
                    analogWrite(ENB, ster);
            
                }else{
                  analogWrite(ENA, ster);
                  analogWrite(ENB, vel);
 
            
          }
      }
  
  
  
}


