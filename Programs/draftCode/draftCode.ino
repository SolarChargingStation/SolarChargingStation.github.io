volatile float encoderPos;
float opCode,azimuth,altitude;
int reading;
unsigned long time1,time2;

void setup() {
  pinMode(2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2), doEncoderA, RISING);
  pinMode(3, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(3), doEncoderB, RISING);

  Serial.begin(9600);
}

void loop() {
  // gather data
  while(Serial.available()==0);
  opCode = Serial.parseFloat();
  while(Serial.available()==0);
  azimuth = Serial.parseFloat();
  while(Serial.available()==0);
  altitude = Serial.parseFloat();
  // return data
  Serial.print("opCode: ");
  Serial.println(opCode);
  Serial.print("Altitude:   ");
  Serial.println(altitude);
  Serial.print("Azimuth:  ");
  Serial.println(azimuth);
  
  // 1100 - RESET
  if (opCode == 1100) {
    // RESET FUNCTION
  }
  
  // 1200 - ADJUST
  if (opCode == 1200) {
    //// DC MOTOR
    // reset encoderPos
    encoderPos = 0;
    // translate azimuth into encoder marks, 79.75 encoder signals per degree
    azimuth = azimuth*79.75;
    while (encoderPos < azimuth) {
      CW();
    }
    //// LINEAR ACTUATOR
    altitude = 90-altitude;
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
