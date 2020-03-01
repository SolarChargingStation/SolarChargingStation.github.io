int target;
int reading;

bool targetRun;

void setup() {
  // put your setup code here, to run once:
  pinMode(4, OUTPUT);   // direction
  pinMode(5, OUTPUT);   // direction
  pinMode(6, OUTPUT);   // enable
  pinMode(9, OUTPUT);   // speed/PWM
  Serial.begin(9600);
  targetRun = true;
}

void loop() {
  target = 50;  
  digitalWrite(6, HIGH);    // enable
  
  reading = analogRead(A0);
  reading = map(reading, 66, 980, 0, 100);
  if (targetRun == true){
    while(reading < target){
      in();
    }
    while(reading > target){
      out();
    }
    targetRun = false;
  }
}

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

/*
 * Max = 980
 * Min = 66
 */
