
/*
* Getting Started example sketch for nRF24L01+ radios
* This is an example of how to send data from one node to another using data structures
* Updated: Dec 2014 by TMRh20
*/

#include <SPI.h>
#include "RF24.h"

byte addresses[][6] = {"1Node","2Node"};


/****************** User Config ***************************/
/***      Set this radio as radio number 0 or 1         ***/
bool radioNumber = 0;

/* Hardware configuration: Set up nRF24L01 radio on SPI bus plus pins 7 & 8 */
RF24 radio(7,8);
/**********************************************************/



/**
* Create a data structure for transmitting and receiving data
* This allows many variables to be easily sent and received in a single transmission
* See http://www.cplusplus.com/doc/tutorial/structures/
*/

struct dataStruct{
  int asseX;
  int asseY;
  unsigned long temp;
}myData;


  int redFrequency = 0;
  int greenFrequency = 0;
  int blueFrequency = 0;


  int vel= 0;
  int ster = 0;
  int X = 1;
  int Y = 1;
  
void setup() {

  avviaSensoreColore();
 
  Serial.begin(115200);
 
  
  radio.begin();

  // Set the PA Level low to prevent power supply related issues since this is a
 // getting_started sketch, and the likelihood of close proximity of the devices. RF24_PA_MAX is default.
  radio.setPALevel(RF24_PA_LOW);
  
  // Open a writing and reading pipe on each radio, with opposite addresses
  if(radioNumber){
    radio.openWritingPipe(addresses[1]);
    radio.openReadingPipe(1,addresses[0]);
  }else{
    radio.openWritingPipe(addresses[0]);
    radio.openReadingPipe(1,addresses[1]);
  }
  
  // Start the radio listening for data
  radio.startListening();
  
  avviamotore();
  fermo();
  


}

//configuriamo tutto quello che serve per i motori


void loop() {
  
  
/****************** Ping Out Role ***************************/  

    
    if( radio.available()){
                                                           // Variable for the received timestamp
      while (radio.available()) {                          // While there is data ready
        radio.read( &myData, sizeof(myData) );             // Get the payload
      }

      Y = (int)myData.asseY;
      X = (int)myData.asseX;

      Serial.print(" vel e ster sono: ");
      Serial.print(Y);
      Serial.print(",");
      Serial.println(X);

          
      radio.stopListening();                               // First, stop listening so we can talk  
      char color = colore();                               // ricavo il colore ottenuto
      radio.write( &color, sizeof(color) );              // Send the final one back.      
      radio.startListening();                              // Now, resume listening so we catch the next packets.     
      Serial.print(F("Invia il colore "));
      switch (color){
        case 'R':
          Serial.println("Rosso");
          vel=1;
          break;
        case 'G':
          Serial.println("Verde");
          break;
        case 'B':
          Serial.println("Blue");
          vel = vel/2;
          break;
        case 'I':
          Serial.println("Indefinito");
          break;          
      }

      vel = map (abs(Y), 0, 512, 0, 1024);
      ster = map (abs(X), 0, 512, 0, 1024);

      //i casi in cui il joypad si muove solo in avanti, indietro o è fermo
      
      if (ster<20) {
          if(Y > 10) {
        
            avanti(vel);
            Serial.print("avanti ");
            Serial.println(vel);

          }else if (Y < -10){

            indietro(vel);
            Serial.print("indietro ");
            Serial.println(vel);
      
          }else {
            fermo();
          }
      }

// i casi in cui il joypad si muove solo verso destra o sinistra
    
      if (vel<20) {
          if(X > 10) {
        
              destra(ster);
              Serial.print("destra ");
              Serial.println(vel);

          }else if (X < -10){

              sinistra(ster);
              Serial.print("sinistra ");
              Serial.println(ster);
      
          }else {
          fermo();
          }
      }

// i casi in cui le direzioni sono miste

    if (ster>20 && vel > 20) {
        
    sterza(Y, vel, X, ster);
 }


 }

//delay(500);


} // Loop
