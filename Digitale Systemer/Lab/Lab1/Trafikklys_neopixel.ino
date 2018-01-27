#include <Adafruit_NeoPixel.h>

#define NUMPIXELS 11
#define PIN 6

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

//Lys og bryterpins
const int rb1=0,gu1=1,grb1=2,rf1=3,gf1=4,rb2=6,gu2=7,grb2=8,rf2=9,gf2=10;
          
const int stolpe1[5] = {rb1, gu1, grb1, rf1, gf1},
          stolpe2[5] = {rb2, gu2, grb2, rf2, gf2};

//Setter hvor lenge veiene skal være grønne i ms
const int hVeiDelay = 15000,
          sVeiDelay = 10000,
          switchDelay = 2000,
          gulDelay = 2500;

// Variabel for nåværende delay
int currentDelay;

//strip.setPixelColor(sUnitArray[secUnit][i], ledHigh[0], ledHigh[1], ledHigh[2]);
void setup() {
  // put your setup code here, to run once:
  
  /*Setter lysene til output*/
  /*
  for (int i=4; i<14; i++){
    pinMode(i, OUTPUT);
  }
  */
  //Serial.begin(9600);
  strip.begin();
  strip.setBrightness(255); // 0-255
  
  /*
  //Setter knapp for fotgjenger til interrupt
  attachInterrupt(digitalPinToInterrupt(k1), ISR, HIGH);
  */

  //Setter hovedvei til grønn, og sidevei til rød
  strip.setPixelColor(grb1, 0, 255, 0);
  strip.setPixelColor(rb2, 255, 0, 0);
  strip.setPixelColor(gf2, 0, 255, 0);
  strip.setPixelColor(rf1, 255, 0, 0);
  strip.show();
  currentDelay = hVeiDelay;
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(strip.getPixelColor(gf2));
  delay(currentDelay-5000);
  switch(strip.getPixelColor(gf2)){
    case 65280:
      blinkMann(stolpe2);
      break;
    case 512://0:
      blinkMann(stolpe1);
      break;
    default:
      errorBlink();
  }
  
  switch(strip.getPixelColor(grb1)){ 
    case 65280:
      switchLights(stolpe1, stolpe2);
      currentDelay = sVeiDelay;
      break;
    case 512://0:
      switchLights(stolpe2, stolpe1);
      currentDelay = hVeiDelay;
      break;
    default:
      errorBlink();
    }
}


void switchLights(int grStolpe[], int rStolpe[]){
  //Setter stolpe som var grønn til rød
  strip.setPixelColor(grStolpe[2], 0, 2, 0);        //Skrur av grønn
  strip.setPixelColor(grStolpe[1], 255, 100, 0);    //Skrur på gul
  strip.show();
  delay(gulDelay);                                  //Er gul i 1,5sek
  strip.setPixelColor(grStolpe[1], 7, 2, 0);        //Skrur av gul
  strip.setPixelColor(grStolpe[0], 255, 0, 0);      //Skrur på rød
  strip.show();
  delay(switchDelay);
  strip.setPixelColor(grStolpe[3], 2, 0, 0);        //Skrur av rød mann.
  
  //Setter stolpe som var rød til grønn
  strip.setPixelColor(rStolpe[1], 255, 100, 0);     //Skrur på gul
  strip.show();
  delay(gulDelay);                                  //Er gul og rød i 1,5sek
  strip.setPixelColor(rStolpe[0], 2, 0, 0);         //Skrur av rød
  strip.setPixelColor(rStolpe[1], 7, 2, 0);         //Skrur av gul
  strip.setPixelColor(rStolpe[2], 0, 255, 0);       //Skrur på grønn
  strip.setPixelColor(grStolpe[4], 0, 255, 0);      //Skrur på grønn mann.
  strip.show();
}

void blinkMann(int stolpe[]){
  Serial.println("Blinker..");
  //Blinker mannen 5 ganger
  for (int i=0; i<5; i++){
    strip.setPixelColor(stolpe[4], 0, 0, 0);
    strip.show();
    delay(500);
    strip.setPixelColor(stolpe[4], 0, 255, 0);
    strip.show();
    delay(500);
  }
  strip.setPixelColor(stolpe[4], 0, 2, 0); //Skrur av grønn mann
  strip.setPixelColor(stolpe[3], 255, 0, 0); //Skrur på rød mann
  strip.show();
}


void errorBlink(){
  for(int i=0; i<5; i++){ //Skrur først av alle lys
    strip.setPixelColor(stolpe1[i], 0,0,0);
    strip.setPixelColor(stolpe2[i], 0,0,0);
  }
  strip.show();
  while(true){
    strip.setPixelColor(stolpe1[1], 255,100,0);
    strip.setPixelColor(stolpe2[1], 255,100,0);
    strip.show();
    delay(500);
    strip.setPixelColor(stolpe1[1], 0,0,0);
    strip.setPixelColor(stolpe2[1], 0,0,0);
    strip.show();
    delay(500);
  }
}


//INTERRUPT KODE HER
/*
void ISR(){
  currentDelay /= 2;
}
*/
