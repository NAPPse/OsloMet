#include <Stepper.h>
#include <ctype.h>

const int STEPS_REV 648;
Stepper stepper(STEPS_REV, 8, 9, 10, 11);

void setup() {
  Serial.begin(9600);
  Serial.println("Ready...");
  stepper.setSpeed(30);
}

void loop() {
  while(!Serial.available()){
    delay(20);
  }
  for(int i=0; i<=1; i++) {
    String dir = Serial.readStringUntil(' ');
    int steps = Serial.readStringUntil('\n').toInt();
    if(dir == "right" || dir == "speed" || dir == "left" && isdigit(steps) == 1 && 0 < steps){
      Serial.print("Dir/Speed:\t");
      Serial.println(dir);
      Serial.print("Steps/Value:\t");
      Serial.println(steps);
      stepper_cmd(dir[0], steps);
      loop();
    }
    else{
      Serial.println("Ugyldig kommando!");
    }
  }
}

void stepper_cmd(const char dir, int steps){
  switch(dir){
    case 's':
      Serial.println("Setter hastighet..");
      stepper.setSpeed(steps);
      break;
    case 'l':
      Serial.println("Kjører venstre..");
      steps *= -1;
      break;
    default:
      Serial.println("Kjører høyre..");
      break;
   }
   stepper.step(steps);
}
