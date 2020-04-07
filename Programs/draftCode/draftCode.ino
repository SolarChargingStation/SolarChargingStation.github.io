volatile float encoderPos=0;
int reading,opCode,azimuth,altitude;
unsigned long time1,time2;

void setup() {
  pinMode(2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2), doEncoderA, RISING);
  pinMode(3, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(3), doEncoderB, RISING);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);

  Serial.begin(9600);
  Serial.setTimeout(2000);
}

void loop() {
  // gather data
  if (Serial.available() > 0) {
    String opCodeStr = Serial.readStringUntil('\n');
    opCode = opCodeStr.toInt();
    
    Serial.println(opCode);
    delay(1000);
    String azimuthStr = Serial.readStringUntil('\n');
    azimuth = azimuthStr.toInt();
    Serial.println(azimuth);    
    delay(1000);
    String altitudeStr = Serial.readStringUntil('\n');
    altitude = altitudeStr.toInt();    
    Serial.println(altitude);

    if (opCode == 1100) {
      while(encoderPos > 0) {
        CW();
      }
      stopAll();
    }

    if (opCode == 1200) {
      //// DC MOTOR
      // reset encoderPos
      // translate azimuth into encoder marks, 79.75 encoder signals per degree
      azimuth = azimuth*79.75;
      while (encoderPos < azimuth) {
        Serial.println("Adjusting azimuth");
        CCW();
      }
      stopAll();
      //// LINEAR ACTUATOR
      // Fully retracted (60) points up, fully extended (980) points out
      /*altitude = 90-altitude;
      if (altitude <= 90 && altitude >= 0) {
        reading = analogRead(A0);
        altitude = map(altitude, 0, 90, 60, 980);
        // has to be within range and has 10 seconds to be completed
        time1 = millis();
        while(reading < altitude) {
          extend();
          reading = analogRead(A0);
          time2 = millis();
          if(time2-time1 > 10000) {
          break;
        }
      }
        while(reading > altitude) {
          retract();
          reading = analogRead(A0);
          time2 = millis();
          if(time2-time1 > 10000) {
            break;
          }
        }
      }*/    
    }
  }
}

//////// FUNCTIONS ////////
// ALL MOTORS
void stopAll() {
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
}
// M1 - ENCODER
void doEncoderA() {  
  encoderPos += (digitalRead(2)==digitalRead(3))?1:0;
}
void doEncoderB() {  
  encoderPos += (digitalRead(2)==digitalRead(3))?-1:0;
}
// M1 - DC MOTOR
void CW() {
  digitalWrite(4, HIGH);
  digitalWrite(5, LOW);
  digitalWrite(6, HIGH);
  analogWrite(7, 255);
}
void CCW() {
  digitalWrite(4, LOW);
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  analogWrite(7, 255);
}
// M2 - LINEAR ACTUATOR
void extend() {
  digitalWrite(8, LOW);
  digitalWrite(9, HIGH);
  digitalWrite(10, HIGH);
  analogWrite(11, 255);
}
void retract() {
  digitalWrite(8, HIGH);
  digitalWrite(9, LOW);
  digitalWrite(10, HIGH);
  analogWrite(11, 255);
}
