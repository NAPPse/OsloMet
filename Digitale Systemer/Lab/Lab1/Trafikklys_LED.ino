//Lys og- bryterpin nummere
const int rb1=4,rb2=5,gu1=6,gu2=7,grb1=8,grb2=9,
          rf1=10,rf2=11,gf1=12,gf2=13,k1=2;

//Definerer stolpene {rød, gul, grønn, rød mann, grønn mann}
const int stolpe1[5] = {rb1, gu1, grb1, rf1, gf1},
          stolpe2[5] = {rb2, gu2, grb2, rf2, gf2};

//Definerer diverse delayer
const int hVeiDelay = 15000,
          sVeiDelay = 10000,
          switchDelay = 1500,
          gulDelay = 2500;

// Variabel for nåværende delay
int currentDelay;

void setup() {
  //Setter lys-pins til output
  for (int i=4; i<14; i++){
    pinMode(i, OUTPUT);
  }

  
  /*
  //Setter knapp for fotgjenger til interrupt
  attachInterrupt(digitalPinToInterrupt(k1), ISR, HIGH);
  */

  //Setter hovedvei til grønn, og sidevei til rød
  digitalWrite(grb1, HIGH); //Grønt lys hovedvei
  digitalWrite(rb2, HIGH);  //Rødt lys sidevei
  digitalWrite(gf2, HIGH);  //Grønn mann sidevei
  digitalWrite(rf1, HIGH);  //Rød mann hovedvei
  currentDelay = hVeiDelay;
}

void loop() {
  
  delay(currentDelay-5000); //Delay minus tiden det tar for grønn mann å blinke seg til rød
  
  switch(digitalRead(gf2)){ //Sjekker om grønn mann sidevei er høy/lav
    case HIGH: //Hvis høy start blinking av mann for sidevei før den gjøres rød
      blinkMann(stolpe2); 
      break;
    case LOW: //Hvis lav start blinking av mann for hovedvei før den gjøres rød
      blinkMann(stolpe1);
      break;
    default: //Hvis den kommer hit er det noe riv ruskende galt. Sett igang feil-blink.
      errorBlink();
  }
  
  switch(digitalRead(grb1)){  //Sjekker om hoved-vei har grønt lys
    case HIGH: //Hvis ja send parametere til switchLights i denne rekkefølgen
      switchLights(stolpe1, stolpe2);
      currentDelay = sVeiDelay; //Setter lengden på det grønne lyset iht. sidevei-delay
      break;
    case LOW://Hvis nei send parametere til switchLights i denne rekkefølgen
      switchLights(stolpe2, stolpe1);
      currentDelay = hVeiDelay; //Setter lengden på det grønne lyset iht. hovedvei-delay
      break;
    default: //Hvis den kommer hit er det noe riv ruskende galt. Sett igang feil-blink.
      errorBlink();
    }
}


void switchLights(int grStolpe[], int rStolpe[]){
  //Setter stolpe som var grønn til rød
  digitalWrite(grStolpe[2], LOW);   //Skrur av grønn
  digitalWrite(grStolpe[1], HIGH);  //Skrur på gul
  delay(gulDelay);                  //Er gul en stund
  digitalWrite(grStolpe[1], LOW);   //Skrur av gul
  digitalWrite(grStolpe[0], HIGH);  //Skrur på rød
  delay(switchDelay);
  
  //Setter stolpe som var rød til grønn
  digitalWrite(rStolpe[1], HIGH);   //Skrur på gul
  delay(gulDelay);                  //Er gul og rød en stund
  digitalWrite(rStolpe[0], LOW);    //Skrur av rød
  digitalWrite(rStolpe[1], LOW);    //Skrur av gul
  digitalWrite(rStolpe[2], HIGH);   //Skrur på grønn
  digitalWrite(grStolpe[3], LOW);   //Skrur av rød mann.
  digitalWrite(grStolpe[4], HIGH);  //Skrur på grønn mann
}

void blinkMann(int stolpe[]){
  
  //Blinker grønn mann 5 ganger
  for (int i=0; i<5; i++){
    digitalWrite(stolpe[4], LOW);
    delay(500);
    digitalWrite(stolpe[4], HIGH);
    delay(500);
  }
  
  digitalWrite(stolpe[4], LOW);  //Skrur av grønn mann
  digitalWrite(stolpe[3], HIGH); //Skrur på rød mann
}

void errorBlink(){
  //Skru av alle lys først
  for(int i=0; i<5; i++){
    digitalWrite(stolpe1[i], LOW);
    digitalWrite(stolpe2[i], LOW);
  }

  //Start en evig loop for gul-blink (feil-blink)
  while(true){
    digitalWrite(stolpe1[1], HIGH);
    digitalWrite(stolpe2[1], HIGH);
    delay(500);
    digitalWrite(stolpe1[1], LOW);
    digitalWrite(stolpe2[1], LOW);
    delay(500);
  }
}


//INTERRUPT KODE HER
/*
void ISR(){
  currentDelay /= 2;
}
*/
