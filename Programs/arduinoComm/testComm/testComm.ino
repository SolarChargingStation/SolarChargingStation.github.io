void setup(){
  Serial.begin(9600);
}
void loop(){
  if(Serial.available() > 0){         //From RPi to Arduino
    int data = Serial.parseFloat();
    Serial.println(data);
  }
}

