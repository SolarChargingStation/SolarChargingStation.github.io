int target;
int reading;
int azimuth;
int altitude;

bool targetRun;

void setup() {
  // put your setup code here, to run once:
  pinMode(4, OUTPUT);   // M1 direction
  pinMode(5, OUTPUT);   // M1 direction
  pinMode(6, OUTPUT);   // M enable
  pinMode(7, OUTPUT);   // M2 direction
  pinMode(8, OUTPUT);   // M2 direction
  pinMode(9, OUTPUT);   // M1 PWM
  pinMode(10, OUTPUT);  // M2 PWM
  Serial.begin(9600);
  targetRun = true;
}

void loop(){
    //// gather information from raspberry pi
    // for dc motor
    while(Serial.available()==0);
    azimuth = Serial.parseFloat();
    // for linear actuator
    while(Serial.available()==0);
    altitude= Serial.parseFloat();

    // gather reading from potentiometer of linear actuator
    reading = analogRead(A0);
    /*
    66 = actuator fully in
    980 = actuator fully out
    mapped to 0-90 because full angular rotation is 90 degrees
    */
    reading = map(reading, 66, 980, 0, 90);

    // only adjust if desired altitude is within range
    if (altitude <= 90 && altitude >= 0) {
      // adjusts if reading doesn't match target of linear actuator
      while(reading < altitude){
        in();
      }
      while(reading > altitude){
        out();
      }
    }

    // DC Motor

    // end with disabling motors
    digitalWrite(6, LOW);
  }
}

///////////////// FUNCTIONS /////////////////

void in(){
  digitalWrite(4, LOW);
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  analogWrite(9, 255);
  analogWrite(10, 0);
}

void out(){
  digitalWrite(4, HIGH);
  digitalWrite(5, LOW);
  digitalWrite(6, HIGH);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  analogWrite(9, 255);
  analogWrite(10, 0);
}

void CW(){
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, HIGH);
  digitalWrite(7, LOW);
  digitalWrite(8, HIGH);
  analogWrite(9, 0);
  analogWrite(10, 255);
}

void CCW(){
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(8, LOW);
  analogWrite(9, 0);
  analogWrite(10, 255);
}

