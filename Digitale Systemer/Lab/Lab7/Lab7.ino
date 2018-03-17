#include <Stepper.h>
#include <ctype.h>

#define STEPS_REV 648 // Steps/rev
Stepper stepper(STEPS_REV, 8, 9, 10, 11);

void setup() {
  Serial.begin(9600);
  Serial.println("Ready...");
  stepper.setSpeed(30);
}

void loop() {
  while(!Serial.available()){ //Henger her til den får en seriell kommando
    delay(20);
  }
  String dir = Serial.readStringUntil(' ');
  int steps = Serial.readStringUntil('\n').toInt();
  if((dir == "right" || dir == "speed" || dir == "left") && 0 < steps){
    Serial.print("Dir/Speed:\t");
    Serial.println(dir);
    Serial.print("Steps/Value:\t");
    Serial.println(steps);
    stepper_cmd(dir[0], steps); //Sender første bokstav og N_steps/hastighetsverdi til stepper_cmd()
    loop();
  }
  else{
    Serial.println("Ugyldig kommando!");
  }
}

void stepper_cmd(const char dir, int steps){
  switch(dir){
    case 's': //Hvis første bokstav er s var kommandoen "speed"
      Serial.println("Setter hastighet..");
      if(steps > 100){
        Serial.println("Ro ned. Du kan ikke kjøre fortere enn 100%");
        steps = 100;
      }
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
