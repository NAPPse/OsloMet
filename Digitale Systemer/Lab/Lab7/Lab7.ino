#include <Stepper.h>

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
    if(dir == "right" || dir == "speed" || dir == "left" && 0 < steps && steps < 256){
      Serial.print("Dir/Speed:\t");
      Serial.println(dir);
      Serial.print("Steps/Value:\t");
      Serial.println(steps);
      stepper_cmd(dir[0], steps);
      loop();
    }
    else{
      Serial.println("Ugyldig kommando!");
      loop();
    }
  }
}

void stepper_cmd(char dir, int steps){
  switch(dir){
    case 's':
    Serial.println("Setter hastighet..");
      stepper.setSpeed(steps);
      break;
    default:
      Serial.println("Setter rettning..");
      switch(dir){
        case 'l':
          steps *= -1;
          break;
      } 
      stepper.step(steps);
      break;
  }
}
