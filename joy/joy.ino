
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
bool radioNumber = 1;

/* Hardware configuration: Set up nRF24L01 radio on SPI bus plus pins 7 & 8 */
RF24 radio(7,8);
/**********************************************************/

/*
Includiamo la libreria che permette l'utilizzo di uno schermo lcd 2x16 del tipo
Hitachi HD44780
*/

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

/**
* Create a data structure for transmitting and receiving data
* This allows many variables to be easily sent and received in a single transmission
* See http://www.cplusplus.com/doc/tutorial/structures/
*/

int X = A1;    // select the input pin for the potentiometer
int Y = A2;      // select the pin for the LED
int tap = 3;  // variable to store the value coming from the sensor

char color;

int oldX=0, oldY=0;

struct dataStruct{
  int asseX;
  int asseY;
//  bool clic;
  unsigned long temp;
}myData;

void setup() {
  
    // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);

  pinMode(X, INPUT);
  pinMode(Y, INPUT);
  pinMode(tap, INPUT);
  
  Serial.begin(115200);
  Serial.println(F("RF24/examples/GettingStarted_HandlingData"));
  Serial.println(F("*** PRESS 'T' to begin transmitting to the other node"));
  
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
  
//  myData.value = 1.22;
  // Start the radio listening for data
  radio.startListening();
  
  //uso queta variabile per mandare a monitor seriale i dati ogni TOT secondi e non  ad ogni ciclo
         

}




void loop() {
  
  
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  
/****************** Ping Out Role ***************************/  

    
    radio.stopListening();                                    // First, stop listening so we can talk.
    
    
    Serial.println(F("Now sending"));

    myData.asseX = map(analogRead(X), 0, 1024, -512, 512); 
    myData.asseY= map(analogRead(Y), 0, 1024, -512, 512);
 //   myData.clic= digitalRead(tap);
    myData.temp = micros();

        // set the cursor to column 0, line 2
        // (note: line 1 is the second row, since counting begins with 0):
    lcd.setCursor(0, 2);      
         
    lcd.print(myData.asseX);
    lcd.print(" - ");   
    lcd.print(myData.asseY);
      
    if (abs(abs(oldX)-abs(myData.asseX)>5 )){            
        
          Serial.println(myData.asseX); 
          oldX = myData.asseX;
      }      
      
     if (abs(abs(oldY)-abs(myData.asseY)>5 )){        
         Serial.println(myData.asseY);
         oldY = myData.asseY;
     }
     
     if (!radio.write( &myData, sizeof(myData) )){
       Serial.println(F("failed"));
     }
        
    radio.startListening();                                    // Now, continue listening
    
    unsigned long started_waiting_at = micros();               // Set up a timeout period, get the current microseconds
    boolean timeout = false;                                   // Set up a variable to indicate if a response was received or not
    
    while ( !radio.available() ){                             // While nothing is received
      if (micros() - started_waiting_at > 200000 ){            // If waited longer than 200ms, indicate timeout and exit while loop
          timeout = true;
          break;
      }      
    }
        
    if ( timeout ){                                             // Describe the results
        Serial.println(F("Failed, response timed out."));
    }else{
                                                                // Grab the response, compare, and send to debugging spew
        radio.read( &color, sizeof(color) );
        unsigned long time = micros();
  
  
                Serial.print("identificato il colore ");
              
                switch (color){
                  case 'R':
                    Serial.println("Rosso");
                    // set the cursor to column 0, line 1
                    // (note: line 1 is the second row, since counting begins with 0):
                    lcd.setCursor(0, 1);      
                    lcd.print("Rosso");
                    break;
                  case 'G':
                    // set the cursor to column 0, line 1
                    // (note: line 1 is the second row, since counting begins with 0):
                    lcd.setCursor(0, 1);      
                    lcd.print("Verde");
                    Serial.println("Verde");
                    break;
                  case 'B':
                    // set the cursor to column 0, line 1
                    // (note: line 1 is the second row, since counting begins with 0):
                    lcd.setCursor(0, 1);      
                    lcd.print("Blue");
                    Serial.println("Blue");
                    break;        
                }

        // Spew it
//        Serial.print(F("Sent "));
//        Serial.print(time);
//        Serial.print(F(", Got response "));
//        Serial.print(myData.temp);
//        Serial.print(F(", Round-trip delay "));
//        Serial.print(time-myData.temp);
//        Serial.print(F(" microseconds Value "));
//        Serial.println(myData.temp);
    }

    // Try again 1s later
//    delay(1000);



} // Loop
