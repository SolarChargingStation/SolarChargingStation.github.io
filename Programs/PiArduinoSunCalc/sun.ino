// Arduino Uno script

void setup(){
  Serial.begin(9600);
}
void loop(){
    while(Serial.available()==0);          //From RPi to Arduino
    int azimuth = Serial.parseFloat();
    while(Serial.available()==0);
    int altitude= Serial.parseFloat();
  }
}

