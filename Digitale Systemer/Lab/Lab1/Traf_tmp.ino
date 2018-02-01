//Lys og- bryterpin nummere
const int rb1=11,rb2=4,gu1=12,gu2=5,grb1=13,grb2=6,
          rf1=10,rf2=7,gf1=9,gf2=8,k1=2,k2=3;

const int stolpe1[5] = {rb1, gu1, grb1, rf1, gf1}, stolpe2[5] = {rb2, gu2, grb2, rf2, gf2};

bool half_toggled = false;

const int hVeiDelay = 15000,
      sVeiDelay = 10000,
      switchDelay = 1500,
      gulDelay = 2500;

// Variabel for nåværende delay
int currentDelay;

void isr(){
  Serial.println("Pressed!");
  if(half_toggled == false){
    Serial.println("Deler delay pA to..");
    currentDelay /= 2;
    half_toggled = true;
    delay(currentDelay);
    switch(digitalRead(grb1)){
      case HIGH: //Hvis ja send parametere til switchLights i denne rekkefølgen
      switchLights(stolpe1, stolpe2);
      currentDelay = sVeiDelay; //Setter lengden på det grønne lyset iht. sidevei-delay
      break;
    case LOW://Hvis nei send parametere til switchLights i denne rekkefølgen
      switchLights(stolpe2, stolpe1);
      currentDelay = hVeiDelay; //Setter lengden på det grønne lyset iht. hovedvei-delay
      break;
    }
  }
  else{
    Serial.println("Delay er allerede halvert!");
  }
}

void setup(){
  
  //Setter lys-pins til output
  for (int i=4; i<14; i++){
    pinMode(i, OUTPUT);
  }
  
  //Setter k1 til interrupt
  Serial.begin(9600);
  delay(200);
  attachInterrupt(digitalPinToInterrupt(k1), isr, FALLING);
  attachInterrupt(digitalPinToInterrupt(k2), isr, FALLING);
  
  digitalWrite(grb1, HIGH); //Grønt lys hovedvei
  digitalWrite(rb2, HIGH);  //Rødt lys sidevei
  digitalWrite(gf2, HIGH);  //Grønn mann sidevei
  digitalWrite(rf1, HIGH);  //Rød mann hovedvei
  currentDelay = hVeiDelay;
  delay(currentDelay);
  //errorBlink();
}

void loop(){
  
  delay(currentDelay-5000); //Delay minus tiden det tar for grønn mann å blinke seg til rød
  
  switch(digitalRead(gf2)){ //Sjekker om grønn mann sidevei er høy/lav
    case HIGH: //Hvis høy start blinking av mann for sidevei før den gjøres rød
      blinkMann(stolpe2); 
      break;
    case LOW: //Hvis lav start blinking av mann for hovedvei før den gjøres rød
      blinkMann(stolpe1);
      break;
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
    }
}


void switchLights(int grStolpe[], int rStolpe[]){
  half_toggled = false;
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
  for(int i=0; i<sizeof(stolpe1); i++){
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
