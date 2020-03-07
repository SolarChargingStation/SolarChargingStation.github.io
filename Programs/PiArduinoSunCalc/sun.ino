int target;
int reading;
int azimuth;
int altitude;

bool targetRun;

void setup() {
  // put your setup code here, to run once:
  pinMode(4, OUTPUT);   // M1 direction
  pinMode(5, OUTPUT);   // M1 direction
  pinMode(6, OUTPUT);   // M1 enable
  pinMode(9, OUTPUT);   // M1 PWM
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

    // adjusts if reading doesn't match target of linear actuator
    while(reading < altitude){
      in();
    }
    while(reading > altitude){
      out();
    }

  }
}

///////////////// FUNCTIONS /////////////////

void in(){
  digitalWrite(6, HIGH);
  digitalWrite(4, LOW);
  digitalWrite(5, HIGH);
  analogWrite(9, 255);
}

void out(){
  digitalWrite(6, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(5, LOW);
  analogWrite(9, 255);
}