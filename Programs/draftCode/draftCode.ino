int EncoderA = 2;
int EncoderB = 3;
int M1C1 = 4;
int M1C2 = 5;
int M1PWM = 6;
int M1E = 7;
int M2C1 = 8;
int M2C2 = 9;
int M2PWM = 10;
int M2E = 11;
int M2Pot = A0;

volatile int encoderPos=0;
int reading,opCode,azimuth,altitude;
unsigned long time1,time2;

void setup() {
  pinMode(EncoderA, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2), doEncoderA, RISING);
  pinMode(EncoderB, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(3), doEncoderB, RISING);
  pinMode(M1C1, OUTPUT);
  pinMode(M1C2, OUTPUT);
  pinMode(M1PWM, OUTPUT);
  pinMode(M1E, OUTPUT);
  pinMode(M2C1, OUTPUT);
  pinMode(M2C2, OUTPUT);
  pinMode(M2PWM, OUTPUT);
  pinMode(M2E, OUTPUT);
  pinMode(18, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(18), adjust, HIGH);

  Serial.begin(115200);
}

void loop() {
  // gather data  
  String message(DEC);
  //Serial.println("<Arduino is ready>");
  while(Serial.available()==0) {
    Serial.println("<Arduino is ready>");
  }
  message = Serial.readString();
  Serial.println(message);
  String opCodeStr,azimuthStr,altitudeStr,encoderStr;
  opCodeStr = opCodeStr+message[0];       // opCode String
  opCodeStr = opCodeStr+message[1];
  opCodeStr = opCodeStr+message[2];
  azimuthStr = azimuthStr+message[3];     // azimuth String
  azimuthStr = azimuthStr+message[4];
  azimuthStr = azimuthStr+message[5];
  altitudeStr = altitudeStr+message[6];   // altitude String
  altitudeStr = altitudeStr+message[7];
  altitudeStr = altitudeStr+message[8];
  
  int opCode = opCodeStr.toInt();
  int azimuth = azimuthStr.toInt();
  int altitude = altitudeStr.toInt();

  if (opCode == 110) {
    while(encoderPos > 0) {
      CW();
    }
    stopAll();
  }

  if (opCode == 120) {
    //// DC MOTOR
    // reset encoderPos
    // translate azimuth into encoder marks, 79.75 encoder signals per degree
    azimuth = azimuth*79.75;
    while (encoderPos < azimuth) {
      //Serial.println("Adjusting azimuth");
      CCW();
    }
    stopAll();
    //// LINEAR ACTUATOR
    // Fully retracted (60) points up, fully extended (980) points out
    altitude = 90-altitude;
    if (altitude <= 90 && altitude >= 0) {
      reading = analogRead(M2Pot);
      altitude = map(altitude, 0, 90, 60, 980);
      // has to be within range and has 10 seconds to be completed
      time1 = millis();
      while(reading < altitude) {
        extend();
        reading = analogRead(M2Pot);
        time2 = millis();
        if(time2-time1 > 10000) {
        break;
      }
    }
      while(reading > altitude) {
        retract();
        reading = analogRead(M2Pot);
        time2 = millis();
        if(time2-time1 > 10000) {
          break;
        }
      }
    }
  }
  
  delay(10000);
}

//////// FUNCTIONS ////////
// ALL MOTORS
void stopAll() {
  digitalWrite(M1C1, LOW);
  digitalWrite(M1C2, LOW);
  digitalWrite(M1PWM, LOW);
  digitalWrite(M1E, LOW);
  digitalWrite(M2C1, LOW);
  digitalWrite(M2C2, LOW);
  digitalWrite(M2PWM, LOW);
  digitalWrite(M2E, LOW);
}
// M1 - ENCODER
void doEncoderA() {  
  encoderPos += (digitalRead(EncoderA)==digitalRead(EncoderB))?1:0;
}
void doEncoderB() {  
  encoderPos += (digitalRead(EncoderA)==digitalRead(EncoderB))?-1:0;
}
// M1 - DC MOTOR
void CW() {
  digitalWrite(M1C1, HIGH);
  digitalWrite(M1C2, LOW);
  digitalWrite(M1PWM, HIGH);
  digitalWrite(M1E, HIGH);
}
void CCW() {
  digitalWrite(M1C1, LOW);
  digitalWrite(M1C2, HIGH);
  digitalWrite(M1PWM, HIGH);
  digitalWrite(M1E, HIGH);
}
// M2 - LINEAR ACTUATOR
void extend() {
  digitalWrite(M2C1, LOW);
  digitalWrite(M2C2, HIGH);
  digitalWrite(M2PWM, HIGH);
  digitalWrite(M2E, HIGH);
}
void retract() {
  digitalWrite(M2C1, HIGH);
  digitalWrite(M2C2, LOW);
  digitalWrite(M2PWM, HIGH);
  digitalWrite(M2E, HIGH);
}
// used to aim the platform North
void adjust() {
  // active for as long as switch is flipped
  while(digitalRead(18) == HIGH) {
    while(digitalRead(22) == HIGH) {
      CW();
    }
    while(digitalRead(23) == HIGH) {
      CCW();
    }
    // this is new north
    if (digitalRead(24) == HIGH) {
      encoderPos = 0;
      azimuth = azimuth*79.75;
      while (encoderPos < azimuth) {
        //Serial.println("Adjusting azimuth");
        CCW();
        }
      stopAll();
      break;
    }
  }
}