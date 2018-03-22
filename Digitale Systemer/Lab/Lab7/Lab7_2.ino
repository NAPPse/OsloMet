#include <Stepper.h>

#define STEPS_REV 200 // Steps/rev
Stepper stepper(STEPS_REV, 12, 11, 10, 9);

void setup() {
  Serial.begin(9600);
  Serial.println("Ready...");
  stepper.setSpeed(30);
}

void checkString(String command){
  const String dirs[3] = {"speed", "right", "left"}; // Array med gyldige kommandoer
  int sumOfDirs = 0; // Placeholder for antall kommandoer gitt i settnigen
  String dir = "";   // Placeholder for rettning/speed -kommando

  for(int i=0; i<3; i++){               // Plusser på 1 til antall kommandoer gitt i settningen
    if(command.indexOf(dirs[i]) >= 0){  // og setter inn siste som blir funnet i variablen dir
      sumOfDirs ++;
      dir = dirs[i];
    }
  }
  
  char* ccommand = command.c_str(); // Konverterer fra String til c_str
  char *token = strtok(ccommand, ' '); //Deler opp settningen ved bruk av mellomrom

  int steps = 0; //Placeholder for antall steps/speed-verdi
  
  while(token != NULL){ //Looper gjennom hvert ord i settningen og finner første tallverdi
    if(atoi(token) > 0){// og lagrer denne i variablen steps
      steps = atoi(token);
      break;
    }
    token = strtok(NULL, " ");
  }

  switch(sumOfDirs){//Sjekker at den om antall kommandoer gitt er akkurat lik en. 
    case 1:         //Dette er fordi bruker ikke skal kunne sende en kommando slik som:
      if(steps > 0){//"turn motor 500 steps to the right left"
        stepper_cmd(dir[0], steps);//Sjekker deretter om en tallverdi er funnet og at den er større enn null.
      }
      else{
        Serial.println("Du må skrive inn en tallverdi..");
      }
      return;
    default:
      Serial.println("Ugyldig kommando!");
      return;
  }
}


void loop() {
  while(!Serial.available()){ //Henger her til den får en seriell kommando
    delay(20);
  }
  checkString(Serial.readStringUntil('\n'));
}

void stepper_cmd(const char dir, int steps){
  switch(dir){
    case 's': //Hvis første bokstav er s var kommandoen "speed"
      Serial.println("Setter hastighet..");
      stepper.setSpeed(steps); //Setter ny hastighet
      return; //Returnerer fordi vi ikke ønsker at motoren skal gå n_steps for ny hastighetsverdi
    case 'l': //Hvis første bokstav er l var kommandoen "left"
      Serial.println("Kjører venstre..");
      steps *= -1; //Multipliserer steps med minus 1 for å få en negativ verdi
      break;
    default:
      Serial.println("Kjører høyre..");
      break;
   }
   stepper.step(steps); //Kjører valgte steps.
   Serial.println(steps);
}
