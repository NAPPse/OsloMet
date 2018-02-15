float temperature[20];
const int temp_Pin = A0, readDelay=500,
          motorSpeed = 6, dir1 = 5, dir2 = 4;
 

void setup() {  
  pinMode(temp_Pin, INPUT);
  pinMode(motorSpeed, OUTPUT);
  pinMode(dir1, OUTPUT);
  pinMode(dir2, OUTPUT);
  
  Serial.begin(9600); //Starter serial
  while(!Serial){ //Gir serial tid til å starte
    delay(200);
  }
  Serial.println("Serial startet...");  
  digitalWrite(dir1, HIGH);
  temperature[19] = 0.0;
}

void loop() {
  for (int i=0; i<20; i++){
    int reading = analogRead(temp_Pin);
    float v = (reading*5)/1024.0;
    float celsius = (v-0.5)*100;
    temperature[i] = celsius;

    /*
    //Konstant hastighet ved høy/lav temperatur
    if(celsius>25.0){
      analogWrite(motorSpeed, 255);
    }
    else{
      analogWrite(motorSpeed, 127);
    }
    */

    //Map ifht til antall grader
    int val = map(celsius, 20, 30, 127, 255);
    analogWrite(motorSpeed, val);   
    
    Serial.print("Måling ");
    Serial.print(i);
    Serial.print(": ");
    Serial.print(celsius);
    Serial.println("°C");
    delay(readDelay);
  }
  bubble_sort(temperature, 20);
  Serial.print("Min:\t\t");
  Serial.print(temperature[0]);
  Serial.println("°C");
  Serial.print("Max:\t\t");
  Serial.print(temperature[19]);
  Serial.println("°C");
  Serial.print("Gj.snitt:\t");
  Serial.print(average(temperature, 20));
  Serial.println("°C");
}

float average(float arr[], int len){
  float sum=0;
  for(int i=0; i<len; i++){
    sum+=arr[i];
  }
  return sum/len;
}

void bubble_sort(float arr[], int len){
  float tmp;

  for (int i=0; i<len; i++){
    for (int j=0; j<len-1; j++){
      if(arr[j]>arr[j+1]){
        tmp = arr[j+1];
        arr[j+1]=arr[j];
        arr[j]=tmp;
        }
      }
   }
}
