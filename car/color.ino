void avviaSensoreColore(){

  /**
  impostiamo i parametri per il sensore TCS230 or TCS3200
**/


  #define S0 4
  #define S1 5
  #define S2 3
  #define S3 2
  #define sensorOut 6

  // inizializza le frequenze base


  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);

   // Setting the sensorOut as an input
  pinMode(sensorOut, INPUT);
  
  // Setting frequency scaling to 2%
  digitalWrite(S0, LOW);
  digitalWrite(S1,HIGH);


}



char colore (){

  int redColor = 0;
  int greenColor = 0;
  int blueColor = 0;

  char color;

  
// inizializziamo il sensore di lettura del rosso
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);

  // lettura del sensore
  redFrequency = pulseIn(sensorOut, LOW);

  Serial.print("redFrequency = ");
  Serial.println(redFrequency);
  
  // 70 e 120 sono valori campione, andrebbero ricampionati sullo
  //sketch di realizzazione
  redColor = map(redFrequency, 70, 120, 255,0);
  
  //  stampiamo sul monitor seriale
    Serial.print("R = ");
    Serial.println(redColor);
  //  delay(100);
  
  // set per acquisizione del verde
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  
  // lettura del sensore
  greenFrequency = pulseIn(sensorOut, LOW);

  Serial.print("greenFrequency = ");
  Serial.println(greenFrequency);
  
  // 100, 199 sono parametri scelti arbitrariamente
  greenColor = map(greenFrequency, 100, 199, 255, 0);
  
  // Printing the GREEN (G) value  
    Serial.print(" G = ");
    Serial.println(greenColor);
  //  delay(100);
 
  // set per acquisizione del blue
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  
  // lettura del sensore
  blueFrequency = pulseIn(sensorOut, LOW);

   Serial.print("blueFrequency = ");
  Serial.println(blueFrequency);
  
  // 38, 84 sono parametri scelti arbitrariamente
  blueColor = map(blueFrequency, 38, 84, 255, 0);
  
  // per stampare sul monitor seriale
    Serial.print(" B = ");
    Serial.println(blueColor);
  //  delay(100);

  // Checks the current detected color and prints
  // a message in the serial monitor
  if(redColor > greenColor && redColor > blueColor && (redColor < -4200 && redColor > -4900)){
      Serial.println(" - RED detected!");
      color = 'R';
  }else if(greenColor > redColor && greenColor > blueColor && (greenColor < -2100 && greenColor > -2300)){
    Serial.println(" - GREEN detected!");
      color = 'G';
  }else if(blueColor > redColor && blueColor > greenColor && (blueColor < -3100 && blueColor > -3300)){
    Serial.println(" - Blue detected!");
      color = 'B';
  } else {
     color = 'I';
  }

return color;
  
}

