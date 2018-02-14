float temperature[20];
const int tmp_Pin = 0, readDelay=1000, hBridge = 8;
 

void setup() {
  // put your setup code here, to run once:
  pinMode(tmp_Pin, INPUT);
  pinMode(hBridge, OUTPUT);
  
  Serial.begin(9600); //Starter serial
  while(!Serial){ //Gir serial tid til å starte
    delay(200);
  }
  Serial.println("Serial startet...");  
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i=0; i<20; i++){
    float reading = analogRead(tmp_sensor);
    float v = (reading*5.0)/1024.0;
    float celsius = (v-0.5)*100;
    temperature[i] = celsius;
    Serial.print("Temperatur: ");
    Serial.print(celsius);
    Serial.println("C\223");
    delay(readDelay);
  }
  bubble_sort(temperature, 20);
  Serial.println("\t\tTemperatur\tVolt");
  Serial.print("Min:\t");
  Serial.print(temperature[0]);
  Serial.println("C\233");
  Serial.print("Max:\t");
  Serial.print(temperature[20]);
  Serial.println("C\233");
  Serial.print("Gj.snitt:\t");
  Serial.print(average(temperature, 20));
  Serial.println("C\233);
}

float average(float arr[], int len){
  int sum=0;
  for(int i=0; i<len; i++){
    sum+=arr[i];
  }
  return sum/len;
}

void bubble_sort(float arr[], int len){
    float tmp;

    for (int i=0; i<len-1; i++){
        for (int j=0; j<len-1; j++){
            if(arr[j]>arr[j+1]){
                tmp = arr[j+1];
                arr[j+1]=arr[j];
                arr[j]=tmp;
            }
        }
    }
}
